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
    pushBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pushBtn->setCheckable(true);
    pushBtn->setMinimumSize(WMIN, HMIN);
    pushBtn->setMaximumSize(WMAX, HMAX);

    //为了让pushBtn在中间
    QHBoxLayout *hLayoutPushBtn = new QHBoxLayout;
    hLayoutPushBtn->addWidget(pushBtn);

    lineEdit = new QLineEdit;
    lineEdit->setPlaceholderText("请输入预览字符串");
    lineEdit->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Expanding);

    //为了让行编辑器在中间
    QHBoxLayout *hLayoutLineEdit = new QHBoxLayout;
    hLayoutLineEdit->addWidget(lineEdit);

    styleTab = new PushBtnStyleTabWidget;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayoutPushBtn);
    vLayout->addStretch(1);
    vLayout->addLayout(hLayoutLineEdit);
    vLayout->addWidget(styleTab);

    setLayout(vLayout);

    connect(styleTab, &PushBtnStyleTabWidget::styleChanged, pushBtn, &MyPushButton::setQSS);
    connect(lineEdit, &QLineEdit::editingFinished, this, [&]() {
        pushBtn->setText(lineEdit->displayText());
    });
}

PushBtnStyleTabWidget::PushBtnStyleTabWidget(QWidget *parent) : QTabWidget (parent)
{
    normalTabPage = new NormalStyleTabPage;
    normalScrollArea = new MyScrollArea;
    normalScrollArea->setWidget(normalTabPage);

    hoverTabPage = new HoverStyleTabPage;
    hoverScrollArea = new MyScrollArea;
    hoverScrollArea->setWidget(hoverTabPage);

    pressedTabPage = new PressedStyleTabPage;
    pressedScrollArea = new MyScrollArea;
    pressedScrollArea->setWidget(pressedTabPage);

    checkedTabPage = new CheckedStyleTabPage;
    checkedStyleArea = new MyScrollArea;
    checkedStyleArea->setWidget(checkedTabPage);

    addTab(normalScrollArea, "Normal");
    addTab(hoverScrollArea, "Hover");
    addTab(pressedScrollArea, "Pressed");
    addTab(checkedStyleArea, "Checked");
    setTabPosition(QTabWidget::West);
    setTabShape(QTabWidget::Triangular);

    connect(normalTabPage, &NormalStyleTabPage::normalStyleChanged, this, &PushBtnStyleTabWidget::changeNormalStyleStr);
    connect(hoverTabPage, &HoverStyleTabPage::hoverStyleChanged, this, &PushBtnStyleTabWidget::changeHoverStyleStr);
    connect(pressedTabPage, &PressedStyleTabPage::pressedStyleChanged, this, &PushBtnStyleTabWidget::changePressedStyleStr);
    connect(checkedTabPage, &CheckedStyleTabPage::checkedStyleChanged, this, &PushBtnStyleTabWidget::changeCheckedStyleStr);
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

PressedStyleTabPage::PressedStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vlayout =  initPanel();
    setLayout(vlayout);

    connect(borderColor, &GetColor::colorChanged, this, &PressedStyleTabPage::borderColorChange);
    connect(backGroundColor, &GetColor::colorChanged, this, &PressedStyleTabPage::backGroundColorChange);
    connect(fontColor, &GetColor::colorChanged, this, &PressedStyleTabPage::fontColorChange);
    connect(borderSize, &SliderWidthValueShow::valueChanged, this, &PressedStyleTabPage::borderSizeChange);
    connect(radiusSize, &SliderWidthValueShow::valueChanged, this, &PressedStyleTabPage::radiusSizeChange);
}

QVBoxLayout *PressedStyleTabPage::initPanel()
{
    borderColor = new GetColor("边界颜色");
    backGroundColor = new GetColor("背景颜色");
    fontColor = new GetColor("字体颜色");
    borderSize = new SliderWidthValueShow("边界宽度", 0, 20);
    radiusSize = new SliderWidthValueShow("圆角尺寸", 0, 42);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(borderColor);
    vLayout->addWidget(backGroundColor);
    vLayout->addWidget(fontColor);
    vLayout->addWidget(borderSize);
    vLayout->addWidget(radiusSize);

    return vLayout;
}

void PressedStyleTabPage::borderColorChange(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDatePressedStyle();
}
void PressedStyleTabPage::backGroundColorChange(QString str)
{
    backGroundColorStr = "background-color: rgba" + str;
    upDatePressedStyle();
}
void PressedStyleTabPage::fontColorChange(QString str)
{
    fontColorStr = "color: rgba" + str;
    upDatePressedStyle();
}
void PressedStyleTabPage::borderSizeChange(QString str)
{
    borderSizeStr = "border-width: " + str + "border-style: solid;" ;
    upDatePressedStyle();
}
void PressedStyleTabPage::radiusSizeChange(QString str)
{
    radiusSizeStr = "border-radius: " + str;
    upDatePressedStyle();
}

void PressedStyleTabPage::upDatePressedStyle()
{
    QString str;
    str = borderSizeStr + radiusSizeStr + fontColorStr
            + backGroundColorStr + borderColorStr;
    str = "QPushButton:pressed {" + str + "}";
    emit pressedStyleChanged(str);
}

CheckedStyleTabPage::CheckedStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vlayout =  initPanel();
    setLayout(vlayout);

    connect(borderColor, &GetColor::colorChanged, this, &CheckedStyleTabPage::borderColorChange);
    connect(backGroundColor, &GetColor::colorChanged, this, &CheckedStyleTabPage::backGroundColorChange);
    connect(fontColor, &GetColor::colorChanged, this, &CheckedStyleTabPage::fontColorChange);
    connect(borderSize, &SliderWidthValueShow::valueChanged, this, &CheckedStyleTabPage::borderSizeChange);
    connect(radiusSize, &SliderWidthValueShow::valueChanged, this, &CheckedStyleTabPage::radiusSizeChange);
}

QVBoxLayout *CheckedStyleTabPage::initPanel()
{
    borderColor = new GetColor("边界颜色");
    backGroundColor = new GetColor("背景颜色");
    fontColor = new GetColor("字体颜色");
    borderSize = new SliderWidthValueShow("边界宽度", 0, 20);
    radiusSize = new SliderWidthValueShow("圆角尺寸", 0, 42);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(borderColor);
    vLayout->addWidget(backGroundColor);
    vLayout->addWidget(fontColor);
    vLayout->addWidget(borderSize);
    vLayout->addWidget(radiusSize);

    return vLayout;
}

void CheckedStyleTabPage::borderColorChange(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateCheckedStyle();
}
void CheckedStyleTabPage::backGroundColorChange(QString str)
{
    backGroundColorStr = "background-color: rgba" + str;
    upDateCheckedStyle();
}
void CheckedStyleTabPage::fontColorChange(QString str)
{
    fontColorStr = "color: rgba" + str;
    upDateCheckedStyle();
}
void CheckedStyleTabPage::borderSizeChange(QString str)
{
    borderSizeStr = "border-width: " + str + "border-style: solid;" ;
    upDateCheckedStyle();
}
void CheckedStyleTabPage::radiusSizeChange(QString str)
{
    radiusSizeStr = "border-radius: " + str;
    upDateCheckedStyle();
}

void CheckedStyleTabPage::upDateCheckedStyle()
{
    QString str;
    str = borderSizeStr + radiusSizeStr + fontColorStr
            + backGroundColorStr + borderColorStr;
    str = "QPushButton:checked {" + str + "}";
    emit checkedStyleChanged(str);
}

HoverStyleTabPage::HoverStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vlayout =  initPanel();
    setLayout(vlayout);

    connect(borderColor, &GetColor::colorChanged, this, &HoverStyleTabPage::borderColorChange);
    connect(backGroundColor, &GetColor::colorChanged, this, &HoverStyleTabPage::backGroundColorChange);
    connect(fontColor, &GetColor::colorChanged, this, &HoverStyleTabPage::fontColorChange);
    connect(borderSize, &SliderWidthValueShow::valueChanged, this, &HoverStyleTabPage::borderSizeChange);
    connect(radiusSize, &SliderWidthValueShow::valueChanged, this, &HoverStyleTabPage::radiusSizeChange);
}

QVBoxLayout *HoverStyleTabPage::initPanel()
{
    borderColor = new GetColor("边界颜色");
    backGroundColor = new GetColor("背景颜色");
    fontColor = new GetColor("字体颜色");
    borderSize = new SliderWidthValueShow("边界宽度", 0, 20);
    radiusSize = new SliderWidthValueShow("圆角尺寸", 0, 42);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(borderColor);
    vLayout->addWidget(backGroundColor);
    vLayout->addWidget(fontColor);
    vLayout->addWidget(borderSize);
    vLayout->addWidget(radiusSize);

    return vLayout;
}

void HoverStyleTabPage::borderColorChange(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateHoverStyle();
}
void HoverStyleTabPage::backGroundColorChange(QString str)
{
    backGroundColorStr = "background-color: rgba" + str;
    upDateHoverStyle();
}
void HoverStyleTabPage::fontColorChange(QString str)
{
    fontColorStr = "color: rgba" + str;
    upDateHoverStyle();
}
void HoverStyleTabPage::borderSizeChange(QString str)
{
    borderSizeStr = "border-width: " + str + "border-style: solid;" ;
    upDateHoverStyle();
}
void HoverStyleTabPage::radiusSizeChange(QString str)
{
    radiusSizeStr = "border-radius: " + str;
    upDateHoverStyle();
}

void HoverStyleTabPage::upDateHoverStyle()
{
    QString str;
    str = borderSizeStr + radiusSizeStr + fontColorStr
            + backGroundColorStr + borderColorStr;
    str = "QPushButton:hover {" + str + "}";
    emit hoverStyleChanged(str);
}

NormalStyleTabPage::NormalStyleTabPage(QWidget *parent) : QWidget (parent)
{

    QVBoxLayout *vlayout =  initPanel();

    setLayout(vlayout);

    connect(borderColor, &GetColor::colorChanged, this, &NormalStyleTabPage::borderColorChange);
    connect(backGroundColor, &GetColor::colorChanged, this, &NormalStyleTabPage::backGroundColorChange);
    connect(fontColor, &GetColor::colorChanged, this, &NormalStyleTabPage::fontColorChange);
    connect(fontFamily, &QFontComboBox::currentFontChanged, this, &NormalStyleTabPage::fontFamilyChange);
    connect(hSize, &SliderWidthValueShow::valueChanged, this, &NormalStyleTabPage::hSizeChange);
    connect(vSize, &SliderWidthValueShow::valueChanged, this, &NormalStyleTabPage::vSizeChange);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &NormalStyleTabPage::borderSizeChange);
    connect(fontSize, &SliderWidthValueShow::valueChanged, this, &NormalStyleTabPage::fontSizeChange);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &NormalStyleTabPage::radiusSizeChange);
    connect(italicAndBold, &ItalicAndBoldWidget::styleChanged, this, &NormalStyleTabPage::italicAndBoldChange);
    connect(alignAndDec, &AlignAndDecorationWidget::styleChanged, this, &NormalStyleTabPage::alignAndDecChange);
    connect(shadowEffect, &ShadowEffectWidget::styleChanged, this, &NormalStyleTabPage::shadowChange);
    connect(backgroundImage, &ButtonForImageAccess::imageChanged, this, &NormalStyleTabPage::backgroundImageChange);
    connect(borderImage, &ButtonForImageAccess::imageChanged, this, &NormalStyleTabPage::borderImageChange);
    connect(contentsImage, &ButtonForImageAccess::imageChanged, this, &NormalStyleTabPage::contentsImageChange);

}

QVBoxLayout *NormalStyleTabPage::initPanel()
{
    borderColor = new GetColor("边界颜色");
    backGroundColor = new GetColor("背景颜色");
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
    vLayout->addWidget(backGroundColor);
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

void NormalStyleTabPage::contentsImageChange(QString str)
{
    contentsImageStr = "image: " + QString("url(") + str + ");";
    upDateNormalStyle();
}

void NormalStyleTabPage::borderImageChange(QString str)
{
    borderImageStr = "border-image: " + QString("url(") + str + ");";
    upDateNormalStyle();
}

void NormalStyleTabPage::backgroundImageChange(QString str)
{
    backgroundImageStr = "background-image: " + QString("url(") + str + ");";
    upDateNormalStyle();
}

void NormalStyleTabPage::shadowChange(QString str)
{
    shadowStyleStr = "box-shadow: " + str;
    upDateNormalStyle();
}

void NormalStyleTabPage::alignAndDecChange(QString str)
{
    alignAndDecStr = str;
    upDateNormalStyle();
}

void NormalStyleTabPage::italicAndBoldChange(QString str)
{
    italicAndBoldStr = str;
    upDateNormalStyle();
}
void NormalStyleTabPage::borderColorChange(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateNormalStyle();
}
void NormalStyleTabPage::backGroundColorChange(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateNormalStyle();
}
void NormalStyleTabPage::fontColorChange(QString str)
{
    fontColorStr = "color: rgba" + str;
    upDateNormalStyle();
}
void NormalStyleTabPage::fontFamilyChange(QFont font)
{
    fontFamilyStr = "font-family: " + font.family() + ";";
    upDateNormalStyle();
}
void NormalStyleTabPage::hSizeChange(QString str)
{
    hSizeStr = "min-width:" + str + "max-width:" + str ;
    upDateNormalStyle();
}

void NormalStyleTabPage::vSizeChange(QString str)
{
    vSizeStr = "min-height:" + str + "max-height:" + str;
    upDateNormalStyle();
}
void NormalStyleTabPage::borderSizeChange(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: solid;" ;
    upDateNormalStyle();
}
void NormalStyleTabPage::fontSizeChange(QString str)
{
    fontSizeStr = "font-size: " + str;
    upDateNormalStyle();
}
void NormalStyleTabPage::radiusSizeChange(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateNormalStyle();
}

void NormalStyleTabPage::upDateNormalStyle()
{
    QString str;
    str = fontFamilyStr + hSizeStr + vSizeStr + borderWidthStr
            + fontSizeStr + borderRadiusStr + fontColorStr
            + backgroundColorStr + borderColorStr + italicAndBoldStr
            + alignAndDecStr + shadowStyleStr + backgroundImageStr + borderImageStr
            + contentsImageStr;
    str = "QPushButton {" + str + "}";
    emit normalStyleChanged(str);
}
