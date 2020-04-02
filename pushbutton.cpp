#include "pushbutton.h"
#include "getcolor.h"
#include "sliderwidthvalueshow.h"

#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QFontComboBox>
#include <QGroupBox>
#include <QSpinBox>
#include <QTabWidget>
#include <QRegExp>
#include <QDebug>
#include <QLabel>
#include <QFont>
PushButtonPage::PushButtonPage(QWidget *parent) : QWidget (parent)
{
    pushBtn = new MyPushButton("test");
    pushBtn->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    pushBtn->setCheckable(true);
    pushBtn->setMinimumSize(WMIN, HMIN);
    pushBtn->setMaximumSize(WMAX, HMAX);

    //为了让pushBtn在中间
    QHBoxLayout *hLayoutPushBtn = new QHBoxLayout;
    hLayoutPushBtn->addWidget(pushBtn);

    styleTab = new PushBtnStyleTab;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayoutPushBtn);
    vLayout->addStretch(1);
    vLayout->addWidget(styleTab);

    setLayout(vLayout);

    connect(styleTab, &PushBtnStyleTab::styleChanged, pushBtn, &MyPushButton::setQSS);

}

PushBtnStyleTab::PushBtnStyleTab(QWidget *parent) : QTabWidget (parent)
{
    normalWidget = new NormalStyleWidget;
    normalArea = new NormalStyleArea;
    normalArea->setWidget(normalWidget);

    addTab(normalArea, "Normal");
    setTabPosition(QTabWidget::West);
    setTabShape(QTabWidget::Triangular);

    connect(normalWidget, &NormalStyleWidget::normalStyleChanged, this, &PushBtnStyleTab::changeNormalStyleStr);
}

void PushBtnStyleTab::changeNormalStyleStr(QString str)
{
    normalStyleStr = str;
    changeStyleStr();
}

void PushBtnStyleTab::changeStyleStr()
{
    QString styleStr = normalStyleStr + pressedStyleStr
            + checkedStyleStr + hoverStyleStr;
    emit styleChanged(styleStr);
}

NormalStyleWidget::NormalStyleWidget(QWidget *parent) : QWidget (parent)
{

    QVBoxLayout *vlayout =  initPanel();

    setLayout(vlayout);
    void borderColorChange(QString str);
    void backGroundColorChange(QString str);
    void fontColorChange(QString str);
    void fontFamilyChange(QString str);
    void hSizeChange(QString str);
    void vSizeChange(QString str);
    void borderSizeChange(QString str);
    void fontSizeChange(QString str);
    void radiusSizeChange(QString str);

    connect(borderColor, &GetColor::colorChanged, this, &NormalStyleWidget::borderColorChange);
    connect(backGroundColor, &GetColor::colorChanged, this, &NormalStyleWidget::backGroundColorChange);
    connect(fontColor, &GetColor::colorChanged, this, &NormalStyleWidget::fontColorChange);
    connect(fontFamily, &QFontComboBox::currentFontChanged, this, &NormalStyleWidget::fontFamilyChange);
    connect(hSize, &SliderWidthValueShow::valueChanged, this, &NormalStyleWidget::hSizeChange);
    connect(vSize, &SliderWidthValueShow::valueChanged, this, &NormalStyleWidget::vSizeChange);
    connect(borderSize, &SliderWidthValueShow::valueChanged, this, &NormalStyleWidget::borderSizeChange);
    connect(fontSize, &SliderWidthValueShow::valueChanged, this, &NormalStyleWidget::fontSizeChange);
    connect(radiusSize, &SliderWidthValueShow::valueChanged, this, &NormalStyleWidget::radiusSizeChange);
    connect(italicAndBold, &ItalicAndBoldWidget::styleChanged, this, &NormalStyleWidget::italicAndBoldChange);
    connect(alignAndDec, &AlignAndDecorationWidget::styleChanged, this, &NormalStyleWidget::alignAndDecChange);
    connect(shadowEffect, &ShadowEffectWidget::styleChanged, this, &NormalStyleWidget::shadowChange);

}

QVBoxLayout *NormalStyleWidget::initPanel()
{
    borderColor = new GetColor("边界颜色");
    backGroundColor = new GetColor("背景颜色");
    fontColor = new GetColor("字体颜色");
    fontFamily = new QFontComboBox;
    vSize = new SliderWidthValueShow("垂直高度", 0, 100);
    hSize = new SliderWidthValueShow("水平宽度", 0, 200);
    borderSize = new SliderWidthValueShow("边界宽度", 0, 20);
    fontSize = new SliderWidthValueShow("字体大小", 8, 28);
    radiusSize = new SliderWidthValueShow("圆角尺寸", 0, 42);
    italicAndBold = new ItalicAndBoldWidget;
    alignAndDec = new AlignAndDecorationWidget;
    shadowEffect = new ShadowEffectWidget;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(borderColor);
    vLayout->addWidget(backGroundColor);
    vLayout->addWidget(fontColor);
    vLayout->addWidget(fontFamily);
    vLayout->addWidget(italicAndBold);
    vLayout->addWidget(alignAndDec);
    vLayout->addWidget(fontSize);
    vLayout->addWidget(vSize);
    vLayout->addWidget(hSize);
    vLayout->addWidget(borderSize);
    vLayout->addWidget(radiusSize);
    vLayout->addWidget(shadowEffect);

    return vLayout;
}

void NormalStyleWidget::shadowChange(QString str)
{
    shadowStyleStr = "box-shadow: " + str;
    upDateNormalStyle();
}

void NormalStyleWidget::alignAndDecChange(QString str)
{
    alignAndDecStr = str;
    upDateNormalStyle();
}

void NormalStyleWidget::italicAndBoldChange(QString str)
{
    italicAndBoldStr = str;
    upDateNormalStyle();
}
void NormalStyleWidget::borderColorChange(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateNormalStyle();
}
void NormalStyleWidget::backGroundColorChange(QString str)
{
    backGroundColorStr = "background-color: rgba" + str;
    upDateNormalStyle();
}
void NormalStyleWidget::fontColorChange(QString str)
{
    fontColorStr = "color: rgba" + str;
    upDateNormalStyle();
}
void NormalStyleWidget::fontFamilyChange(QFont font)
{
    fontFamilyStr = "font-family: " + font.family() + ";";
    upDateNormalStyle();
}
void NormalStyleWidget::hSizeChange(QString str)
{
    hSizeStr = "min-width:" + str + "max-width:" + str ;
    upDateNormalStyle();
}

void NormalStyleWidget::vSizeChange(QString str)
{
    vSizeStr = "min-height:" + str + "max-height:" + str;
    upDateNormalStyle();
}
void NormalStyleWidget::borderSizeChange(QString str)
{
    borderSizeStr = "border-width: " + str + "border-style: solid;" ;
    upDateNormalStyle();
}
void NormalStyleWidget::fontSizeChange(QString str)
{
    fontSizeStr = "font-size: " + str;
    upDateNormalStyle();
}
void NormalStyleWidget::radiusSizeChange(QString str)
{
    radiusSizeStr = "border-radius: " + str;
    upDateNormalStyle();
}

void NormalStyleWidget::upDateNormalStyle()
{
    QString str;
    str = fontFamilyStr + hSizeStr + vSizeStr + borderSizeStr
            + fontSizeStr + radiusSizeStr + fontColorStr
            + backGroundColorStr + borderColorStr + italicAndBoldStr
            + alignAndDecStr + shadowStyleStr;
    str = "QPushButton {" + str + "}";
    qDebug() << str;
    emit normalStyleChanged(str);
}
