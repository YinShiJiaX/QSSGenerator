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
    QHBoxLayout *hLayoutPushBtn = new QHBoxLayout;
    hLayoutPushBtn->addWidget(slider);

    styleTab = new SliderStyleTabWidget;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayoutPushBtn);
    vLayout->addStretch(1);
    vLayout->addWidget(styleTab);

    setLayout(vLayout);

    connect(styleTab, &SliderStyleTabWidget::styleChanged, slider, &QSlider::setStyleSheet);
}

SliderStyleTabWidget::SliderStyleTabWidget(QWidget *parent) : QTabWidget (parent)
{
    backgroundTabPage = new BackgroundStyleTabPage;
    backgroundScrollArea = new MyScrollArea;
    backgroundScrollArea->setWidget(backgroundTabPage);

    grooveTabPage = new GrooveStyleTabPage;
    grooveScrollArea = new MyScrollArea;
    grooveScrollArea->setWidget(grooveTabPage);

    handleTabPage = new HandleStyleTabPage;
    handleScrollArea = new MyScrollArea;
    handleScrollArea->setWidget(handleTabPage);

    subTabPage = new SubStyleTabPage;
    subScrollArea = new MyScrollArea;
    subScrollArea->setWidget(subTabPage);

    addTabPage = new AddStyleTabPage;
    addScrollArea = new MyScrollArea;
    addScrollArea->setWidget(addTabPage);

    addTab(backgroundScrollArea, "Background");
    addTab(grooveScrollArea, "Groove");
    addTab(handleScrollArea, "Handle");
    addTab(subScrollArea, "Sub");
    addTab(addScrollArea, "Add");
    setTabPosition(QTabWidget::West);
    setTabShape(QTabWidget::Triangular);

    connect(backgroundTabPage, &BackgroundStyleTabPage::styleChanged,
            this, &SliderStyleTabWidget::changeBackgroundStyleStr);
    connect(grooveTabPage, &GrooveStyleTabPage::styleChanged,
            this, &SliderStyleTabWidget::changeGrooveStyleStr);
    connect(handleTabPage, &HandleStyleTabPage::styleChanged,
            this, &SliderStyleTabWidget::changeHandleStyleStr);
    connect(subTabPage, &SubStyleTabPage::styleChanged,
            this, &SliderStyleTabWidget::changeSubStyleStr);
    connect(addTabPage, &AddStyleTabPage::styleChanged,
            this, &SliderStyleTabWidget::changeAddStyleStr);
}

void SliderStyleTabWidget::changeSubStyleStr(QString str)
{
    subStr = str;
    changeStyleStr();
}

void SliderStyleTabWidget::changeAddStyleStr(QString str)
{
    addStr = str;
    changeStyleStr();
}

void SliderStyleTabWidget::changeHandleStyleStr(QString str)
{
    handleStr = str;
    changeStyleStr();
}

void SliderStyleTabWidget::changeGrooveStyleStr(QString str)
{
    grooveStr = str;
    changeStyleStr();
}

void SliderStyleTabWidget::changeBackgroundStyleStr(QString str)
{
    backgroundStr = str;
    changeStyleStr();
}

void SliderStyleTabWidget::changeStyleStr()
{
    QString styleStr = backgroundStr + grooveStr + handleStr + addStr
            + subStr;
    qDebug() << styleStr;
    emit styleChanged(styleStr);
}

BackgroundStyleTabPage::BackgroundStyleTabPage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(borderColor, &GetColor::colorChanged, this, &BackgroundStyleTabPage::changeBorderColorStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &BackgroundStyleTabPage::changeBorderWidthStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &BackgroundStyleTabPage::changeBackgroundColorStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &BackgroundStyleTabPage::changeBorderRadiusStr);
}

void BackgroundStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void BackgroundStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}
void BackgroundStyleTabPage::changeBorderWidthStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: solid;" ;
    upDateStyle();
}
void BackgroundStyleTabPage::changeBorderRadiusStr(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateStyle();
}


void BackgroundStyleTabPage::upDateStyle()
{
    QString str;
    str = backgroundColorStr + borderColorStr
            + borderWidthStr + borderRadiusStr;
    str = "QSlider {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *BackgroundStyleTabPage::initPanel()
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

GrooveStyleTabPage::GrooveStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(borderColor, &GetColor::colorChanged, this, &GrooveStyleTabPage::changeBorderColorStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &GrooveStyleTabPage::changeBorderWidthStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &GrooveStyleTabPage::changeBackgroundColorStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &GrooveStyleTabPage::changeBorderRadiusStr);
    connect(height, &SliderWidthValueShow::valueChanged, this, &GrooveStyleTabPage::changeHeightStr);
}

void GrooveStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void GrooveStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}
void GrooveStyleTabPage::changeBorderWidthStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: solid;" ;
    upDateStyle();
}
void GrooveStyleTabPage::changeBorderRadiusStr(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateStyle();
}

void GrooveStyleTabPage::changeHeightStr(QString str)
{
    heightStr = "height: " + str;
    upDateStyle();
}

void GrooveStyleTabPage::upDateStyle()
{
    QString str;
    str = backgroundColorStr + borderColorStr
            + borderWidthStr + borderRadiusStr +
            heightStr;
    str = "QSlider::groove:horizontal {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *GrooveStyleTabPage::initPanel()
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

HandleStyleTabPage::HandleStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(borderColor, &GetColor::colorChanged, this, &HandleStyleTabPage::changeBorderColorStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &HandleStyleTabPage::changeBorderWidthStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &HandleStyleTabPage::changeBackgroundColorStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &HandleStyleTabPage::changeBorderRadiusStr);
    connect(width, &SliderWidthValueShow::valueChanged, this, &HandleStyleTabPage::changeWidthStr);
    connect(marginTop, &SliderWidthValueShow::valueChanged,
            this, &HandleStyleTabPage::changeMarginTopStr);
    connect(marginBottom, &SliderWidthValueShow::valueChanged,
            this, &HandleStyleTabPage::changeMarginBottomStr);
    connect(marginLeft, &SliderWidthValueShow::valueChanged,
            this, &HandleStyleTabPage::changeMarginLeftStr);
    connect(marginRight, &SliderWidthValueShow::valueChanged,
            this, &HandleStyleTabPage::changeMarginRightStr);

}

void HandleStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void HandleStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}
void HandleStyleTabPage::changeBorderWidthStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: solid;" ;
    upDateStyle();
}
void HandleStyleTabPage::changeBorderRadiusStr(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateStyle();
}

void HandleStyleTabPage::changeWidthStr(QString str)
{
    widthStr = "width: " + str;
    upDateStyle();
}

void HandleStyleTabPage::changeMarginTopStr(QString str)
{
    marginTopStr = "margin-top:" + str;
    upDateStyle();
}

void HandleStyleTabPage::changeMarginBottomStr(QString str)
{
    marginBottomStr = "margin-bottom: " + str;
    upDateStyle();
}

void HandleStyleTabPage::changeMarginLeftStr(QString str)
{
    marginLeftStr = "margin-left: " + str;
    upDateStyle();
}

void HandleStyleTabPage::changeMarginRightStr(QString str)
{
    marginRightStr = "margin-right: " + str;
    upDateStyle();
}

void HandleStyleTabPage::upDateStyle()
{
    QString str;
    str = backgroundColorStr + borderColorStr +
            borderWidthStr + borderRadiusStr +
            widthStr + marginTopStr + marginBottomStr
            + marginLeftStr + marginRightStr;
    str = "QSlider::handle:horizontal {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *HandleStyleTabPage::initPanel()
{
    backgroundColor = new GetColor("背景颜色");
    borderColor = new GetColor("边界颜色");
    width = new SliderWidthValueShow("滑柄宽度", 0, 10);
    borderWidth = new SliderWidthValueShow("边界宽度", 0, 10);
    borderRadius = new SliderWidthValueShow("圆角半径", 0, 20);
    marginTop = new SliderWidthValueShow("上边界", -10, 5);
    marginBottom = new SliderWidthValueShow("下边界", -10, 5);
    marginLeft = new SliderWidthValueShow("左边界", -10, 10);
    marginRight = new SliderWidthValueShow("有边界", -10, 10);

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

SubStyleTabPage::SubStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(backgroundColor, &GetColor::colorChanged, this, &SubStyleTabPage::changeBackgroundColorStr);
}

void SubStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}

void SubStyleTabPage::upDateStyle()
{
    QString str;
    str = backgroundColorStr;
    str = "QSlider::sub-page:horizontal {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *SubStyleTabPage::initPanel()
{
    backgroundColor = new GetColor("背景颜色");

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(backgroundColor);

    return vLayout;
}

AddStyleTabPage::AddStyleTabPage(QWidget *parent) : QWidget (parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(backgroundColor, &GetColor::colorChanged, this, &AddStyleTabPage::changeBackgroundColorStr);
}

void AddStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}

void AddStyleTabPage::upDateStyle()
{
    QString str;
    str = backgroundColorStr;
    str = "QSlider::add-page:horizontal {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *AddStyleTabPage::initPanel()
{
    backgroundColor = new GetColor("背景颜色");

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(backgroundColor);

    return vLayout;
}
