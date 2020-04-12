#include "headers/pushbutton.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFontComboBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QTabWidget>
#include <QLineEdit>
#include <QRegExp>
#include <QDebug>
#include <QLabel>
#include <QFont>
PushButtonTabPage::PushButtonTabPage(QWidget *parent) : QWidget (parent)
{
    pushBtn = new MyPushButton("test");
    pushBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);
    pushBtn->setCheckable(true);
    pushBtn->setMinimumSize(WMIN, HMIN);
    pushBtn->setMaximumSize(WMAX, HMAX);

    clearSSBtn = new QPushButton("清除当前样式");
    clearSSBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    generateSSBtn = new QPushButton("生成样式表");
    generateSSBtn->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    //为了让QSS样式清除按钮居中
    QHBoxLayout *hLayoutFunBtn = new QHBoxLayout;
    hLayoutFunBtn->addWidget(clearSSBtn);
    hLayoutFunBtn->addWidget(generateSSBtn);

    //为了让pushBtn在中间
    QHBoxLayout *hLayoutShowBtn = new QHBoxLayout;
    hLayoutShowBtn->addWidget(pushBtn);

    lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText("请输入预览字符串");
    lineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    //为了让行编辑器在中间
    QHBoxLayout *hLayoutLineEdit = new QHBoxLayout;
    hLayoutLineEdit->addWidget(lineEdit);

    styleTab = new PushBtnStyleTabWidget;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayoutShowBtn);
    vLayout->addStretch(1);
    vLayout->addLayout(hLayoutLineEdit);
    vLayout->addLayout(hLayoutFunBtn);
    vLayout->addWidget(styleTab);

    setLayout(vLayout);

    connect(styleTab, &PushBtnStyleTabWidget::styleChanged,this, [&](QString str){
        pushBtn->setQSS(str);
        styleSheetStr = str;
        styleSheetStr.replace(QRegExp("\\{"), "{\n  ");
        styleSheetStr.replace(QRegExp(";"), ";\n  ");
        styleSheetStr.replace(QRegExp("\n  \\}"), "\n}\n\n");
    });
    connect(lineEdit, &QLineEdit::editingFinished, this, [&]() {
        pushBtn->setText(lineEdit->displayText());
    });
    connect(clearSSBtn, &QPushButton::clicked, this, [&](){
        pushBtn->setStyleSheet("");
    });
    connect(generateSSBtn, &QPushButton::clicked, this, [this](){
        emit this->styleSheetGenerated(styleSheetStr);
        qDebug() << styleSheetStr;
    });
}

PushBtnStyleTabWidget::PushBtnStyleTabWidget(QWidget *parent) : QTabWidget (parent)
{
    normalTabPage = new PushButtonTopStyleTabPage;
    normalScrollArea = new MyScrollArea;
    normalScrollArea->setWidget(normalTabPage);

    hoverTabPage = new PushButtonHoverStyleTabPage;
    hoverScrollArea = new MyScrollArea;
    hoverScrollArea->setWidget(hoverTabPage);

    pressedTabPage = new PushButtonPressedStyleTabPage;
    pressedScrollArea = new MyScrollArea;
    pressedScrollArea->setWidget(pressedTabPage);

    checkedTabPage = new PushButtonCheckedStyleTabPage;
    checkedStyleArea = new MyScrollArea;
    checkedStyleArea->setWidget(checkedTabPage);

    addTab(normalScrollArea, "Normal");
    addTab(hoverScrollArea, "Hover");
    addTab(pressedScrollArea, "Pressed");
    addTab(checkedStyleArea, "Checked");
    setTabPosition(QTabWidget::West);
    setTabShape(QTabWidget::Triangular);

    connect(normalTabPage, &PushButtonTopStyleTabPage::styleChanged, this, &PushBtnStyleTabWidget::changeNormalStyleStr);
    connect(hoverTabPage, &PushButtonHoverStyleTabPage::styleChanged, this, &PushBtnStyleTabWidget::changeHoverStyleStr);
    connect(pressedTabPage, &PushButtonPressedStyleTabPage::styleChanged, this, &PushBtnStyleTabWidget::changePressedStyleStr);
    connect(checkedTabPage, &PushButtonCheckedStyleTabPage::styleChanged, this, &PushBtnStyleTabWidget::changeCheckedStyleStr);
}

void PushBtnStyleTabWidget::changeNormalStyleStr(QString str)
{
    normalStyleStr = str;
    changeStyleStr();
}

void PushBtnStyleTabWidget::changeHoverStyleStr(QString str)
{
    hoverStyleStr = str;
    changeStyleStr();
}

void PushBtnStyleTabWidget::changePressedStyleStr(QString str)
{
    pressedStyleStr = str;
    changeStyleStr();
}

void PushBtnStyleTabWidget::changeCheckedStyleStr(QString str)
{
    checkedStyleStr = str;
    changeStyleStr();
}

void PushBtnStyleTabWidget::changeStyleStr()
{
    QString styleStr = normalStyleStr + hoverStyleStr +
            pressedStyleStr + checkedStyleStr;
    qDebug() << styleStr;
    emit styleChanged(styleStr);
}

PushButtonPressedStyleTabPage::PushButtonPressedStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vlayout =  initPanel();
    setLayout(vlayout);

    connect(borderColor, &GetColor::colorChanged, this, &PushButtonPressedStyleTabPage::changeBorderColorStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &PushButtonPressedStyleTabPage::changeBackgroundColorStr);
    connect(fontColor, &GetColor::colorChanged, this, &PushButtonPressedStyleTabPage::changeFontColorStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &PushButtonPressedStyleTabPage::changeBorderWidthStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &PushButtonPressedStyleTabPage::changeBorderRadiusStr);
}

QVBoxLayout *PushButtonPressedStyleTabPage::initPanel()
{
    borderColor = new GetColor("边界颜色");
    backgroundColor = new GetColor("背景颜色");
    fontColor = new GetColor("字体颜色");
    borderWidth = new SliderWidthValueShow("边界宽度", 0, 20);
    borderRadius = new SliderWidthValueShow("圆角尺寸", 0, 42);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(borderColor);
    vLayout->addWidget(backgroundColor);
    vLayout->addWidget(fontColor);
    vLayout->addWidget(borderWidth);
    vLayout->addWidget(borderRadius);

    return vLayout;
}

void PushButtonPressedStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void PushButtonPressedStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}

void PushButtonPressedStyleTabPage::changeFontColorStr(QString str)
{
    fontColorStr = "color: rgba" + str;
    upDateStyle();
}

void PushButtonPressedStyleTabPage::changeBorderWidthStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: inset;" ;
    upDateStyle();
}

void PushButtonPressedStyleTabPage::changeBorderRadiusStr(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateStyle();
}

void PushButtonPressedStyleTabPage::upDateStyle()
{
    QString str;
    str = borderWidthStr + borderRadiusStr + fontColorStr
            + backgroundColorStr + borderColorStr;
    str = "QPushButton:pressed {" + str + "}";
    emit styleChanged(str);
}

PushButtonCheckedStyleTabPage::PushButtonCheckedStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vlayout =  initPanel();
    setLayout(vlayout);

    connect(borderColor, &GetColor::colorChanged, this, &PushButtonCheckedStyleTabPage::changeBorderColorStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &PushButtonCheckedStyleTabPage::changeBackgroundColorStr);
    connect(fontColor, &GetColor::colorChanged, this, &PushButtonCheckedStyleTabPage::changeFontColorStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &PushButtonCheckedStyleTabPage::changeBorderWidthStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &PushButtonCheckedStyleTabPage::changeBorderRadiusStr);
}

QVBoxLayout *PushButtonCheckedStyleTabPage::initPanel()
{
    borderColor = new GetColor("边界颜色");
    backgroundColor = new GetColor("背景颜色");
    fontColor = new GetColor("字体颜色");
    borderWidth = new SliderWidthValueShow("边界宽度", 0, 20);
    borderRadius = new SliderWidthValueShow("圆角尺寸", 0, 42);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(borderColor);
    vLayout->addWidget(backgroundColor);
    vLayout->addWidget(fontColor);
    vLayout->addWidget(borderWidth);
    vLayout->addWidget(borderRadius);

    return vLayout;
}

void PushButtonCheckedStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void PushButtonCheckedStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}

void PushButtonCheckedStyleTabPage::changeFontColorStr(QString str)
{
    fontColorStr = "color: rgba" + str;
    upDateStyle();
}

void PushButtonCheckedStyleTabPage::changeBorderWidthStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: inset;" ;
    upDateStyle();
}

void PushButtonCheckedStyleTabPage::changeBorderRadiusStr(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateStyle();
}

void PushButtonCheckedStyleTabPage::upDateStyle()
{
    QString str;
    str = borderWidthStr + borderRadiusStr + fontColorStr
            + backgroundColorStr + borderColorStr;
    str = "QPushButton:checked {" + str + "}";
    emit styleChanged(str);
}

PushButtonHoverStyleTabPage::PushButtonHoverStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vlayout =  initPanel();
    setLayout(vlayout);

    connect(borderColor, &GetColor::colorChanged, this, &PushButtonHoverStyleTabPage::changeBorderColorStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &PushButtonHoverStyleTabPage::changeBackgroundColorStr);
    connect(fontColor, &GetColor::colorChanged, this, &PushButtonHoverStyleTabPage::changeFontColorStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &PushButtonHoverStyleTabPage::changeBorderSizeStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &PushButtonHoverStyleTabPage::changeBorderRadiusStr);
}

QVBoxLayout *PushButtonHoverStyleTabPage::initPanel()
{
    borderColor = new GetColor("边界颜色");
    backgroundColor = new GetColor("背景颜色");
    fontColor = new GetColor("字体颜色");
    borderWidth = new SliderWidthValueShow("边界宽度", 0, 20);
    borderRadius = new SliderWidthValueShow("圆角尺寸", 0, 42);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(borderColor);
    vLayout->addWidget(backgroundColor);
    vLayout->addWidget(fontColor);
    vLayout->addWidget(borderWidth);
    vLayout->addWidget(borderRadius);

    return vLayout;
}

void PushButtonHoverStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void PushButtonHoverStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}

void PushButtonHoverStyleTabPage::changeFontColorStr(QString str)
{
    fontColorStr = "color: rgba" + str;
    upDateStyle();
}

void PushButtonHoverStyleTabPage::changeBorderSizeStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: solid;" ;
    upDateStyle();
}

void PushButtonHoverStyleTabPage::changeBorderRadiusStr(QString str)
{
    BorderRadiusStr = "border-radius: " + str;
    upDateStyle();
}

void PushButtonHoverStyleTabPage::upDateStyle()
{
    QString str;
    str = borderWidthStr + BorderRadiusStr + fontColorStr
            + backgroundColorStr + borderColorStr;
    str = "QPushButton:hover {" + str + "}";
    emit styleChanged(str);
}

PushButtonTopStyleTabPage::PushButtonTopStyleTabPage(QWidget *parent) : QWidget (parent)
{

    QVBoxLayout *vlayout =  initPanel();

    setLayout(vlayout);

    connect(borderColor, &GetColor::colorChanged, this, &PushButtonTopStyleTabPage::changeBorderColorStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &PushButtonTopStyleTabPage::changeBackgroundColorStr);
    connect(fontColor, &GetColor::colorChanged, this, &PushButtonTopStyleTabPage::changeFontColorStr);
    connect(fontFamily, &QFontComboBox::currentFontChanged, this, &PushButtonTopStyleTabPage::changeFontFamilyStr);
    connect(hSize, &SliderWidthValueShow::valueChanged, this, &PushButtonTopStyleTabPage::changehSizeStr);
    connect(vSize, &SliderWidthValueShow::valueChanged, this, &PushButtonTopStyleTabPage::changevSizeStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &PushButtonTopStyleTabPage::changeBorderWidthStr);
    connect(fontSize, &SliderWidthValueShow::valueChanged, this, &PushButtonTopStyleTabPage::changeFontSizeStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &PushButtonTopStyleTabPage::changeBorderRadiusStr);
    connect(italicAndBold, &ItalicAndBoldWidget::styleChanged, this, &PushButtonTopStyleTabPage::changeItalicAndBoldStr);
    connect(alignAndDec, &AlignAndDecorationWidget::styleChanged, this, &PushButtonTopStyleTabPage::changeAlignAndDecStr);
    connect(shadowEffect, &ShadowEffectWidget::styleChanged, this, &PushButtonTopStyleTabPage::changeShadowStr);
    connect(backgroundImage, &ButtonForImageAccess::imageChanged, this, &PushButtonTopStyleTabPage::changeBackgroundImageStr);
    connect(borderImage, &ButtonForImageAccess::imageChanged, this, &PushButtonTopStyleTabPage::changeBorderImageStr);
    connect(contentsImage, &ButtonForImageAccess::imageChanged, this, &PushButtonTopStyleTabPage::changeContentsImageStr);

}

QVBoxLayout *PushButtonTopStyleTabPage::initPanel()
{
    borderColor = new GetColor("边界颜色");
    backgroundColor = new GetColor("背景颜色");
    fontColor = new GetColor("字体颜色");
    fontFamily = new QFontComboBox;
    vSize = new SliderWidthValueShow("垂直高度", 0, 100);
    hSize = new SliderWidthValueShow("水平宽度", 0, 200);
    borderWidth = new SliderWidthValueShow("边界宽度", 0, 20);
    fontSize = new SliderWidthValueShow("字体大小", 8, 28);
    borderRadius = new SliderWidthValueShow("圆角尺寸", 0, 42);
    italicAndBold = new ItalicAndBoldWidget;
    alignAndDec = new AlignAndDecorationWidget;
    shadowEffect = new ShadowEffectWidget;
    backgroundImage = new ButtonForImageAccess("背景图片");
    borderImage = new ButtonForImageAccess("边界图片");
    contentsImage = new ButtonForImageAccess("内容图片");

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(vSize);
    vLayout->addWidget(hSize);
    vLayout->addWidget(borderRadius);
    vLayout->addWidget(backgroundImage);
    vLayout->addWidget(borderImage);
    vLayout->addWidget(contentsImage);
    vLayout->addWidget(backgroundColor);
    vLayout->addWidget(borderWidth);
    vLayout->addWidget(borderColor);
    vLayout->addWidget(fontSize);
    vLayout->addWidget(fontColor);
    vLayout->addWidget(fontFamily);
    vLayout->addWidget(italicAndBold);
    vLayout->addWidget(alignAndDec);
    vLayout->addWidget(shadowEffect);


    return vLayout;
}

void PushButtonTopStyleTabPage::changeContentsImageStr(QString str)
{
    contentsImageStr = "image: " + QString("url(") + str + ");";
    upDateStyle();
}

void PushButtonTopStyleTabPage::changeBorderImageStr(QString str)
{
    borderImageStr = "border-image: " + QString("url(") + str + ");";
    upDateStyle();
}

void PushButtonTopStyleTabPage::changeBackgroundImageStr(QString str)
{
    backgroundImageStr = "background-image: " + QString("url(") + str + ");";
    upDateStyle();
}

void PushButtonTopStyleTabPage::changeShadowStr(QString str)
{
    shadowStyleStr = "box-shadow: " + str;
    upDateStyle();
}

void PushButtonTopStyleTabPage::changeAlignAndDecStr(QString str)
{
    alignAndDecStr = str;
    upDateStyle();
}

void PushButtonTopStyleTabPage::changeItalicAndBoldStr(QString str)
{
    italicAndBoldStr = str;
    upDateStyle();
}

void PushButtonTopStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void PushButtonTopStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}

void PushButtonTopStyleTabPage::changeFontColorStr(QString str)
{
    fontColorStr = "color: rgba" + str;
    upDateStyle();
}
void PushButtonTopStyleTabPage::changeFontFamilyStr(QFont font)
{
    fontFamilyStr = "font-family: " + font.family() + ";";
    upDateStyle();
}

void PushButtonTopStyleTabPage::changehSizeStr(QString str)
{
    hSizeStr = "min-width:" + str + "max-width:" + str ;
    upDateStyle();
}

void PushButtonTopStyleTabPage::changevSizeStr(QString str)
{
    vSizeStr = "min-height:" + str + "max-height:" + str;
    upDateStyle();
}

void PushButtonTopStyleTabPage::changeBorderWidthStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: outset;" ;
    upDateStyle();
}

void PushButtonTopStyleTabPage::changeFontSizeStr(QString str)
{
    fontSizeStr = "font-size: " + str;
    upDateStyle();
}

void PushButtonTopStyleTabPage::changeBorderRadiusStr(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateStyle();
}

void PushButtonTopStyleTabPage::upDateStyle()
{
    QString str;
    str = fontFamilyStr + hSizeStr + vSizeStr + borderWidthStr
            + fontSizeStr + borderRadiusStr + fontColorStr
            + backgroundColorStr + borderColorStr + italicAndBoldStr
            + alignAndDecStr + shadowStyleStr + backgroundImageStr + borderImageStr
            + contentsImageStr;
    str = "QPushButton {" + str + "}";
    emit styleChanged(str);
}
