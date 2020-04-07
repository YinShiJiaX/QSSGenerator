#include "headers/slider.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

SliderTabPage::SliderTabPage(QWidget *parent) : QWidget(parent)
{
    slider = new QSlider;
    slider->setOrientation(Qt::Horizontal);
    slider->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    //为了让slider在中间
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(slider);

    styleTab = new SliderStyleTabWidget;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addStretch(1);
    vLayout->addWidget(styleTab);

    setLayout(vLayout);

    connect(styleTab, &SliderStyleTabWidget::styleChanged, slider, &QSlider::setStyleSheet);
}

SliderStyleTabWidget::SliderStyleTabWidget(QWidget *parent) : QTabWidget (parent)
{
    topTabPage = new SliderTopStyleTabPage;
    topScrollArea = new MyScrollArea;
    topScrollArea->setWidget(topTabPage);

    grooveTabPage = new SliderGrooveStyleTabPage;
    grooveScrollArea = new MyScrollArea;
    grooveScrollArea->setWidget(grooveTabPage);

    handleTabPage = new SliderHandleStyleTabPage;
    handleScrollArea = new MyScrollArea;
    handleScrollArea->setWidget(handleTabPage);

    subTabPage = new SliderSubStyleTabPage;
    subScrollArea = new MyScrollArea;
    subScrollArea->setWidget(subTabPage);

    addTabPage = new SliderAddStyleTabPage;
    addScrollArea = new MyScrollArea;
    addScrollArea->setWidget(addTabPage);

    addTab(topScrollArea, "Top");
    addTab(grooveScrollArea, "Groove");
    addTab(handleScrollArea, "Handle");
    addTab(subScrollArea, "Sub");
    addTab(addScrollArea, "Add");
    setTabPosition(QTabWidget::West);
    setTabShape(QTabWidget::Triangular);

    connect(topTabPage, &SliderTopStyleTabPage::styleChanged,
            this, &SliderStyleTabWidget::changeTopStyleStr);
    connect(grooveTabPage, &SliderGrooveStyleTabPage::styleChanged,
            this, &SliderStyleTabWidget::changeGrooveStyleStr);
    connect(handleTabPage, &SliderHandleStyleTabPage::styleChanged,
            this, &SliderStyleTabWidget::changeHandleStyleStr);
    connect(subTabPage, &SliderSubStyleTabPage::styleChanged,
            this, &SliderStyleTabWidget::changeSubStyleStr);
    connect(addTabPage, &SliderAddStyleTabPage::styleChanged,
            this, &SliderStyleTabWidget::changeAddStyleStr);
}

void SliderStyleTabWidget::changeSubStyleStr(QString str)
{
    subStr = str;
    upDateStyle();
}

void SliderStyleTabWidget::changeAddStyleStr(QString str)
{
    addStr = str;
    upDateStyle();
}

void SliderStyleTabWidget::changeHandleStyleStr(QString str)
{
    handleStr = str;
    upDateStyle();
}

void SliderStyleTabWidget::changeGrooveStyleStr(QString str)
{
    grooveStr = str;
    upDateStyle();
}

void SliderStyleTabWidget::changeTopStyleStr(QString str)
{
    topStr = str;
    upDateStyle();
}

void SliderStyleTabWidget::upDateStyle()
{
    QString styleStr = topStr + grooveStr + handleStr + addStr
            + subStr;
    qDebug() << styleStr;
    emit styleChanged(styleStr);
}

SliderTopStyleTabPage::SliderTopStyleTabPage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(borderColor, &GetColor::colorChanged, this, &SliderTopStyleTabPage::changeBorderColorStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &SliderTopStyleTabPage::changeBorderWidthStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &SliderTopStyleTabPage::changeBackgroundColorStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &SliderTopStyleTabPage::changeBorderRadiusStr);
}

void SliderTopStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void SliderTopStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}
void SliderTopStyleTabPage::changeBorderWidthStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: solid;" ;
    upDateStyle();
}
void SliderTopStyleTabPage::changeBorderRadiusStr(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateStyle();
}


void SliderTopStyleTabPage::upDateStyle()
{
    QString str;
    str = backgroundColorStr + borderColorStr
            + borderWidthStr + borderRadiusStr;
    str = "QSlider {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *SliderTopStyleTabPage::initPanel()
{
    backgroundColor = new GetColor("背景颜色");
    borderColor = new GetColor("边界颜色");
    borderWidth = new SliderWidthValueShow("边界宽度", 0, 5);
    borderRadius = new SliderWidthValueShow("圆角半径", 0, 10);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(backgroundColor);
    vLayout->addWidget(borderColor);
    vLayout->addWidget(borderWidth);
    vLayout->addWidget(borderRadius);

    return vLayout;
}

SliderGrooveStyleTabPage::SliderGrooveStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(borderColor, &GetColor::colorChanged, this, &SliderGrooveStyleTabPage::changeBorderColorStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &SliderGrooveStyleTabPage::changeBorderWidthStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &SliderGrooveStyleTabPage::changeBackgroundColorStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &SliderGrooveStyleTabPage::changeBorderRadiusStr);
    connect(height, &SliderWidthValueShow::valueChanged, this, &SliderGrooveStyleTabPage::changeHeightStr);
}

void SliderGrooveStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void SliderGrooveStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}
void SliderGrooveStyleTabPage::changeBorderWidthStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: solid;" ;
    upDateStyle();
}
void SliderGrooveStyleTabPage::changeBorderRadiusStr(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateStyle();
}

void SliderGrooveStyleTabPage::changeHeightStr(QString str)
{
    heightStr = "height: " + str;
    upDateStyle();
}

void SliderGrooveStyleTabPage::upDateStyle()
{
    QString str;
    str = backgroundColorStr + borderColorStr
            + borderWidthStr + borderRadiusStr +
            heightStr;
    str = "QSlider::groove:horizontal {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *SliderGrooveStyleTabPage::initPanel()
{
    backgroundColor = new GetColor("背景颜色");
    borderColor = new GetColor("边界颜色");
    height = new SliderWidthValueShow("滑槽高度", 0, 10);
    borderWidth = new SliderWidthValueShow("边界宽度", 0, 10);
    borderRadius = new SliderWidthValueShow("圆角半径", 0, 20);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(backgroundColor);
    vLayout->addWidget(borderColor);
    vLayout->addWidget(height);
    vLayout->addWidget(borderWidth);
    vLayout->addWidget(borderRadius);

    return vLayout;
}

SliderHandleStyleTabPage::SliderHandleStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(borderColor, &GetColor::colorChanged, this, &SliderHandleStyleTabPage::changeBorderColorStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &SliderHandleStyleTabPage::changeBorderWidthStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &SliderHandleStyleTabPage::changeBackgroundColorStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &SliderHandleStyleTabPage::changeBorderRadiusStr);
    connect(width, &SliderWidthValueShow::valueChanged, this, &SliderHandleStyleTabPage::changeWidthStr);
    connect(marginTop, &SliderWidthValueShow::valueChanged,
            this, &SliderHandleStyleTabPage::changeMarginTopStr);
    connect(marginBottom, &SliderWidthValueShow::valueChanged,
            this, &SliderHandleStyleTabPage::changeMarginBottomStr);
    connect(marginLeft, &SliderWidthValueShow::valueChanged,
            this, &SliderHandleStyleTabPage::changeMarginLeftStr);
    connect(marginRight, &SliderWidthValueShow::valueChanged,
            this, &SliderHandleStyleTabPage::changeMarginRightStr);

}

void SliderHandleStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void SliderHandleStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}
void SliderHandleStyleTabPage::changeBorderWidthStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: solid;" ;
    upDateStyle();
}
void SliderHandleStyleTabPage::changeBorderRadiusStr(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateStyle();
}

void SliderHandleStyleTabPage::changeWidthStr(QString str)
{
    widthStr = "width: " + str;
    upDateStyle();
}

void SliderHandleStyleTabPage::changeMarginTopStr(QString str)
{
    marginTopStr = "margin-top:" + str;
    upDateStyle();
}

void SliderHandleStyleTabPage::changeMarginBottomStr(QString str)
{
    marginBottomStr = "margin-bottom: " + str;
    upDateStyle();
}

void SliderHandleStyleTabPage::changeMarginLeftStr(QString str)
{
    marginLeftStr = "margin-left: " + str;
    upDateStyle();
}

void SliderHandleStyleTabPage::changeMarginRightStr(QString str)
{
    marginRightStr = "margin-right: " + str;
    upDateStyle();
}

void SliderHandleStyleTabPage::upDateStyle()
{
    QString str;
    str = backgroundColorStr + borderColorStr +
            borderWidthStr + borderRadiusStr +
            widthStr + marginTopStr + marginBottomStr
            + marginLeftStr + marginRightStr;
    str = "QSlider::handle:horizontal {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *SliderHandleStyleTabPage::initPanel()
{
    backgroundColor = new GetColor("背景颜色");
    borderColor = new GetColor("边界颜色");
    width = new SliderWidthValueShow("滑柄宽度", 0, 10);
    borderWidth = new SliderWidthValueShow("边界宽度", 0, 10);
    borderRadius = new SliderWidthValueShow("圆角半径", 0, 20);
    marginTop = new SliderWidthValueShow("上边界", -10, 5);
    marginBottom = new SliderWidthValueShow("下边界", -10, 5);
    marginLeft = new SliderWidthValueShow("左边界", -10, 10);
    marginRight = new SliderWidthValueShow("右边界", -10, 10);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(backgroundColor);
    vLayout->addWidget(borderColor);
    vLayout->addWidget(width);
    vLayout->addWidget(borderWidth);
    vLayout->addWidget(borderRadius);
    vLayout->addWidget(marginTop);
    vLayout->addWidget(marginBottom);
    vLayout->addWidget(marginLeft);
    vLayout->addWidget(marginRight);

    return vLayout;
}

SliderSubStyleTabPage::SliderSubStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(backgroundColor, &GetColor::colorChanged, this, &SliderSubStyleTabPage::changeBackgroundColorStr);
}

void SliderSubStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}

void SliderSubStyleTabPage::upDateStyle()
{
    QString str;
    str = backgroundColorStr;
    str = "QSlider::sub-page:horizontal {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *SliderSubStyleTabPage::initPanel()
{
    backgroundColor = new GetColor("背景颜色");

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(backgroundColor);

    return vLayout;
}

SliderAddStyleTabPage::SliderAddStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(backgroundColor, &GetColor::colorChanged, this, &SliderAddStyleTabPage::changeBackgroundColorStr);
}

void SliderAddStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}

void SliderAddStyleTabPage::upDateStyle()
{
    QString str;
    str = backgroundColorStr;
    str = "QSlider::add-page:horizontal {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *SliderAddStyleTabPage::initPanel()
{
    backgroundColor = new GetColor("背景颜色");

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(backgroundColor);

    return vLayout;
}
