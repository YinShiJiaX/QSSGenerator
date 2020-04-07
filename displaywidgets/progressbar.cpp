#include "headers/progressbar.h"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QDebug>

ProgressBarTabPage::ProgressBarTabPage(QWidget *parent) : QWidget (parent)
{
    progressBar = new QProgressBar;
    progressBar->setOrientation(Qt::Horizontal);
    progressBar->setValue(50);

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(progressBar);

    styleTab = new ProgressBarStyleTabWidget;

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addLayout(hLayout);
    vLayout->addStretch(1);
    vLayout->addWidget(styleTab);

    setLayout(vLayout);

    connect(styleTab, &ProgressBarStyleTabWidget::styleChanged, progressBar, &QSlider::setStyleSheet);

}

ProgressBarStyleTabWidget::ProgressBarStyleTabWidget(QWidget *parent)
    : QTabWidget (parent)
{
    topTabPage = new ProgressBarTopStyleTabPage;
    topScrollArea = new MyScrollArea;
    topScrollArea->setWidget(topTabPage);

    chunkTabPage = new ProgressBarChunkStyleTabPage;
    chunkScrollArea = new MyScrollArea;
    chunkScrollArea->setWidget(chunkTabPage);

    addTab(topScrollArea, "Top");
    addTab(chunkScrollArea, "Chunk");
    setTabPosition(QTabWidget::West);
    setTabShape(QTabWidget::Triangular);

    connect(topTabPage, &ProgressBarTopStyleTabPage::styleChanged,
            this, &ProgressBarStyleTabWidget::changeTopStyleStr);
    connect(chunkTabPage, &ProgressBarChunkStyleTabPage::styleChanged,
            this, &ProgressBarStyleTabWidget::changeChunkStyleStr);

}

void ProgressBarStyleTabWidget::changeTopStyleStr(QString str)
{
    topStr = str;
    upDateStyle();
}

void ProgressBarStyleTabWidget::changeChunkStyleStr(QString str)
{
    chunkStr = str;
    upDateStyle();
}

void ProgressBarStyleTabWidget::upDateStyle()
{
    QString styleStr = topStr + chunkStr;
    qDebug() << styleStr;
    emit styleChanged(styleStr);
}

ProgressBarTopStyleTabPage::ProgressBarTopStyleTabPage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(borderColor, &GetColor::colorChanged, this, &ProgressBarTopStyleTabPage::changeBorderColorStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &ProgressBarTopStyleTabPage::changeBorderWidthStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &ProgressBarTopStyleTabPage::changeBackgroundColorStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &ProgressBarTopStyleTabPage::changeBorderRadiusStr);
    connect(textAlign, &AlignChooseComboBox::alignChanged, this, &ProgressBarTopStyleTabPage::changeTextAlignStr);
    connect(vSize, &SliderWidthValueShow::valueChanged, this, &ProgressBarTopStyleTabPage::changevSizeStr);
    connect(hSize, &SliderWidthValueShow::valueChanged, this, &ProgressBarTopStyleTabPage::changehSizeStr);
}
void ProgressBarTopStyleTabPage::changehSizeStr(QString str)
{
    hSizeStr = "min-width:" + str + "max-width:" + str ;
    upDateStyle();
}

void ProgressBarTopStyleTabPage::changevSizeStr(QString str)
{
    vSizeStr = "min-height:" + str + "max-height:" + str;
    upDateStyle();
}
void ProgressBarTopStyleTabPage::changeTextAlignStr(QString str)
{
    textAlignStr = "text-align: " + str + ";";
    upDateStyle();
}

void ProgressBarTopStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void ProgressBarTopStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}
void ProgressBarTopStyleTabPage::changeBorderWidthStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: solid;" ;
    upDateStyle();
}
void ProgressBarTopStyleTabPage::changeBorderRadiusStr(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateStyle();
}


void ProgressBarTopStyleTabPage::upDateStyle()
{
    QString str;
    str =  borderColorStr + backgroundColorStr
            + borderWidthStr + borderRadiusStr
            + textAlignStr + vSizeStr + hSizeStr;
    str = "QProgressBar {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *ProgressBarTopStyleTabPage::initPanel()
{
    backgroundColor = new GetColor("背景颜色");
    borderColor = new GetColor("边界颜色");
    borderWidth = new SliderWidthValueShow("边界宽度", 0, 5);
    borderRadius = new SliderWidthValueShow("圆角半径", 0, 10);
    textAlign = new AlignChooseComboBox;
    vSize = new SliderWidthValueShow("整体高度", 0, 20);
    hSize = new SliderWidthValueShow("整体宽度", 100, 900);

    QVBoxLayout *vLayout = new QVBoxLayout;
    vLayout->addWidget(vSize);
    vLayout->addWidget(hSize);
    vLayout->addWidget(textAlign);
    vLayout->addWidget(backgroundColor);
    vLayout->addWidget(borderColor);
    vLayout->addWidget(borderWidth);
    vLayout->addWidget(borderRadius);

    return vLayout;
}

ProgressBarChunkStyleTabPage::ProgressBarChunkStyleTabPage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout *vLayout = initPanel();

    setLayout(vLayout);

    connect(borderColor, &GetColor::colorChanged, this, &ProgressBarChunkStyleTabPage::changeBorderColorStr);
    connect(borderWidth, &SliderWidthValueShow::valueChanged, this, &ProgressBarChunkStyleTabPage::changeBorderWidthStr);
    connect(backgroundColor, &GetColor::colorChanged, this, &ProgressBarChunkStyleTabPage::changeBackgroundColorStr);
    connect(borderRadius, &SliderWidthValueShow::valueChanged, this, &ProgressBarChunkStyleTabPage::changeBorderRadiusStr);
    connect(width, &SliderWidthValueShow::valueChanged, this, &ProgressBarChunkStyleTabPage::changeWidthStr);
    connect(margin, &SliderWidthValueShow::valueChanged, this, &ProgressBarChunkStyleTabPage::changeMarginStr);
}

void ProgressBarChunkStyleTabPage::changeWidthStr(QString str)
{
    widthStr = "width: " + str + ";";
    upDateStyle();
}

void ProgressBarChunkStyleTabPage::changeMarginStr(QString str)
{
    marginStr = "margin: " + str;
    upDateStyle();
}

void ProgressBarChunkStyleTabPage::changeBorderColorStr(QString str)
{
    borderColorStr = "border-color: rgba" + str;
    upDateStyle();
}

void ProgressBarChunkStyleTabPage::changeBackgroundColorStr(QString str)
{
    backgroundColorStr = "background-color: rgba" + str;
    upDateStyle();
}
void ProgressBarChunkStyleTabPage::changeBorderWidthStr(QString str)
{
    borderWidthStr = "border-width: " + str + "border-style: solid;" ;
    upDateStyle();
}
void ProgressBarChunkStyleTabPage::changeBorderRadiusStr(QString str)
{
    borderRadiusStr = "border-radius: " + str;
    upDateStyle();
}


void ProgressBarChunkStyleTabPage::upDateStyle()
{
    QString str;
    str =  borderColorStr + backgroundColorStr
            + borderWidthStr + borderRadiusStr
            + widthStr + marginStr;
    str = "QProgressBar::chunk {" + str + "}";
    emit styleChanged(str);
}

QVBoxLayout *ProgressBarChunkStyleTabPage::initPanel()
{
    backgroundColor = new GetColor("背景颜色");
    borderColor = new GetColor("边界颜色");
    borderWidth = new SliderWidthValueShow("边界宽度", 0, 5);
    borderRadius = new SliderWidthValueShow("圆角半径", 0, 10);
    width = new SliderWidthValueShow("片段宽度", 5, 20);
    margin = new SliderWidthValueShow("片段间距", 0, 10);

    QVBoxLayout *vLayout = new QVBoxLayout;

    vLayout->addWidget(backgroundColor);
    vLayout->addWidget(borderColor);
    vLayout->addWidget(borderWidth);
    vLayout->addWidget(borderRadius);
    vLayout->addWidget(width);
    vLayout->addWidget(margin);

    return vLayout;
}
