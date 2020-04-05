#ifndef PUSHBUTTON_H
#define PUSHBUTTON_H

#include <QWidget>
#include <QScrollArea>
#include <QLabel>
#include <QTabWidget>
#include <QCheckBox>
#include <QHBoxLayout>
#include <QComboBox>
#include <QGraphicsDropShadowEffect>
#include <QPushButton>
#include <QColorDialog>
#include <QSlider>
#include <QDebug>
#include <QVBoxLayout>
#include <QColor>

class QColorDialog;
class GetColor;
class QLineEdit;
class QGroupBox;
class QSpinBox;
class SliderWidthValueShow;
class QFontComboBox;
class PushBtnStyleTabWidget;
class NormalStyleArea;
class NormalStyleTabPage;
class QFont;
class ItalicAndBoldWidget;
class ShadowEffectWidget;
class AlignAndDecorationWidget;
class HoverStyleTabPage;
class HoverStyleArea;
class PressedStyleTabPage;
class PressedStyleArea;
class CheckedStyleTabPage;
class CheckedStyleArea;
class MyPushButton;
#define WMIN 0
#define WMAX 200
#define HMIN 0
#define HMAX 100

//pushButton 样式生成总页面
class PushButtonTabPage : public QWidget
{
    Q_OBJECT
public:
    PushButtonTabPage(QWidget *parent = nullptr);

    QString normalString;
    QString hoverString;
    QString pressedString;
    QString checkedString;
public slots:

private:
    MyPushButton *pushBtn;
    QLineEdit *lineEdit;
    NormalStyleTabPage *normalWidget;
    NormalStyleArea *normalArea;
    PushBtnStyleTabWidget *styleTab;

};

class GetColor : public QWidget
{
    Q_OBJECT
public:
    explicit GetColor(const QString str, QWidget *parent = nullptr) : QWidget(parent)
    {
        pushBtn = new QPushButton;
        colorDialog = new QColorDialog;
        colorDialog->setOption(QColorDialog::ShowAlphaChannel);
        pushBtn->setText(str);

        QGridLayout *gLayout = new QGridLayout;
        gLayout->addWidget(pushBtn);

        setLayout(gLayout);

        connect(pushBtn, &QPushButton::clicked, colorDialog, &QColorDialog::show);
        connect(colorDialog, &QColorDialog::currentColorChanged, this, &GetColor::causeColorChanged);
    }

private slots:
    void causeColorChanged(const QColor &color)
    {
        int r, g, b, a;
        color.getRgb(&r, &g, &b, &a);
        QString str;
        str = "(" + QString::number(r) + ", " + QString::number(g) +
            + ", " + QString::number(b) + ", " + QString::number(a) + ");";

        emit colorChanged(str);
    }

signals:
    void colorChanged(QString colorStr);

private:
    QPushButton *pushBtn;
    QColorDialog *colorDialog;
};


//带数值显示的滑块
class SliderWidthValueShow : public QWidget
{
    Q_OBJECT
public:
    explicit SliderWidthValueShow(const QString str,  int min, int max, QWidget *parent = nullptr) : QWidget(parent)
    {
        indicateStr = str + ":";
        label = new QLabel;
        label->setText(str);
        slider = new QSlider;
        slider->setOrientation(Qt::Horizontal);
        slider->setRange(min, max);

        QVBoxLayout *vlayout = new QVBoxLayout;
        vlayout->addWidget(label);
        vlayout->addWidget(slider);

        setLayout(vlayout);

        connect(slider , &QSlider::valueChanged, this, &SliderWidthValueShow::causeChangeValue);

    }
    void setValue(int value)
    {
        slider->setValue(value);
    }


signals:
    void valueChanged(QString str);

public slots:
    void causeChangeValue(int value)
    {
        QString str;
        str = QString::number(value) + "px;";
        label->setText(indicateStr + str);
        emit valueChanged(str);
    }

private:
    QLabel *label;
    QSlider *slider;
    QString indicateStr;
    QString valueStr;
};

//pushButton 样式控制面板
class PushBtnStyleTabWidget : public QTabWidget
{
    Q_OBJECT

public:
    PushBtnStyleTabWidget(QWidget *parent = nullptr);

public slots:
    void changeNormalStyleStr(QString str);
    void changeHoverStyleStr(QString str);
    void changePressedStyleStr(QString str);
    void changeCheckedStyleStr(QString str);
private:
    void changeStyleStr();
signals:
    void styleChanged(QString styleStr);

private:
    QString normalStyleStr;
    QString pressedStyleStr;
    QString checkedStyleStr;
    QString hoverStyleStr;
    QString styleStr;

    NormalStyleTabPage *normalTabPage;
    NormalStyleArea *normalScrollArea;
    HoverStyleTabPage *hoverTabPage;
    HoverStyleArea *hoverScrollArea;
    PressedStyleArea *pressedScrollArea;
    PressedStyleTabPage *pressedTabPage;
    CheckedStyleTabPage *checkedTabPage;
    CheckedStyleArea *checkedStyleArea;

};


//自定义带阴影样式按钮
class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QString str, QWidget *parent = nullptr) : QPushButton(str, parent)
    {
        shadowEffect = new QGraphicsDropShadowEffect;
        btn = new QPushButton;
        setGraphicsEffect(shadowEffect);
        setCheckable(true);
    }

    void setQSS(QString str)
    {
        QString pattern = "box-shadow: (.*\\d+)px (.*\\d+)px (\\d+)px rgba\\((\\d+), (\\d+), "
                          "(\\d+), (\\d+)\\);";
        QRegExp *re = new QRegExp(pattern);
        re->indexIn(str);
        QStringList list =  re->capturedTexts();
        qreal dx = list[1].toDouble();
        qreal dy = list[2].toDouble();
        qreal blurRadius = list[3].toDouble();
        int r = list[4].toInt();
        int g = list[5].toInt();
        int b = list[6].toInt();
        int a = list[7].toInt();
        QColor color(r, g, b, a);
        drawShadowEffect(dx, dy, blurRadius, color);
        str.replace(QRegExp(pattern), "");
        setStyleSheet(str);
    }
private:
    QGraphicsDropShadowEffect *shadowEffect;
    QPushButton *btn;//该控件用于保存shadowEffect效果，除此之外别无用处
    void drawShadowEffect(qreal dx, qreal dy, qreal blurRadius, QColor color)
    {
        shadowEffect->setOffset(dx, dy);
        shadowEffect->setBlurRadius(blurRadius);
        shadowEffect->setColor(color);
    }
};

class ShadowEffectWidget : public QWidget
{
    Q_OBJECT
public:
    ShadowEffectWidget(QWidget *parent = nullptr) : QWidget (parent)
    {
        xOffset = new SliderWidthValueShow("水平偏移", -10, 10);
        xOffset->setValue(0);
        yOffset = new SliderWidthValueShow("垂直偏移", -10, 10);
        yOffset->setValue(0);
        yOffset->setValue(0);
        blurRadius = new SliderWidthValueShow("模糊半径", 0, 20);
        color = new GetColor("阴影颜色");

        QVBoxLayout *vlayout = new QVBoxLayout;
        vlayout->addWidget(color);
        vlayout->addWidget(xOffset);
        vlayout->addWidget(yOffset);
        vlayout->addWidget(blurRadius);

        setLayout(vlayout);

        connect(xOffset, &SliderWidthValueShow::valueChanged, this, &ShadowEffectWidget::changeXStr);
        connect(yOffset, &SliderWidthValueShow::valueChanged, this, &ShadowEffectWidget::changeYStr);
        connect(blurRadius, &SliderWidthValueShow::valueChanged, this, &ShadowEffectWidget::changeBlurStr);
        connect(color, &GetColor::colorChanged, this, &ShadowEffectWidget::changeColorStr);
    }
signals:
    void styleChanged(QString str);
private slots:
    void changeXStr (QString str)
    {
        str.replace(QRegExp(";"), " ");
        xStr = str;
        updateStyle();

    }

    void changeYStr(QString str)
    {
        str.replace(QRegExp(";"), " ");
        yStr = str;
        updateStyle();
    }

    void changeBlurStr(QString str)
    {
        str.replace(QRegExp(";"), " ");
        blurStr = str;
        updateStyle();
    }

    void changeColorStr(QString str)
    {
        colorStr = "rgba" + str;
        updateStyle();
    }
private:
    QString xStr = "5px ";
    QString yStr = "5px ";
    QString blurStr = "5px ";
    QString colorStr = "rgba(0, 0, 0, 0);";
    QString styleStr;

    SliderWidthValueShow *xOffset;
    SliderWidthValueShow *yOffset;
    SliderWidthValueShow *blurRadius;
    GetColor *color;

    void updateStyle()
    {
        styleStr = xStr + yStr + blurStr + colorStr;
        emit styleChanged(styleStr);
    }
};

class AlignAndDecorationWidget : public QWidget
{
    Q_OBJECT
public:
    AlignAndDecorationWidget(QWidget *parent = nullptr) : QWidget(parent)
    {
        alignBox = new QComboBox;
        QStringList alignment = {"center", "top", "bottom", "left", "right"};
        alignBox->addItems(alignment);

        decBox = new QComboBox;
        QStringList decoration = {"none", "underline", "overline", "line-through"};
        decBox->addItems(decoration);

        QHBoxLayout *hLayout = new QHBoxLayout;
        hLayout->addWidget(alignBox);
        hLayout->addWidget(decBox);
        setLayout(hLayout);
        connect(alignBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
                this, &AlignAndDecorationWidget::changeAlignStr);
        connect(decBox, QOverload<const QString &>::of(&QComboBox::currentIndexChanged),
                this, &AlignAndDecorationWidget::changeDecStr);
    }
private:
    QComboBox *alignBox;
    QComboBox *decBox;
    QString alignStr;
    QString decStr;
public slots:
    void changeAlignStr(QString str)
    {
        alignStr = "text-align: " + str + ";";
        QString str1 = alignStr + decStr;
        emit styleChanged(str1);
    }
    void changeDecStr(QString str)
    {
        decStr = "text-decoration: " + str + ";";
        QString str1 = decStr + alignStr;
        emit styleChanged(str1);
    }
signals:
    void styleChanged(QString str);
};

class ItalicAndBoldWidget : public QWidget
{
    Q_OBJECT
public:
    ItalicAndBoldWidget(QWidget *parent = nullptr) : QWidget (parent)
    {
        italicBox = new QCheckBox("斜体");
        boldBox = new QCheckBox("粗体");
        QHBoxLayout *hLayout = new QHBoxLayout;
        hLayout->setContentsMargins(0, 0, 0, 0);
        hLayout->addWidget(italicBox);
        hLayout->addWidget(boldBox);
        setLayout(hLayout);
        connect(italicBox, &QCheckBox::stateChanged, this, &ItalicAndBoldWidget::changeItalicStr);
        connect(boldBox, &QCheckBox::stateChanged, this, &ItalicAndBoldWidget::changeboldStr);
    }
private:
    QCheckBox *italicBox;
    QCheckBox *boldBox;
    QString italicStr;
    QString boldStr;
public slots:
    void changeItalicStr(int state)
    {
        if (state == 0) {
            italicStr = "";
        } else {
            italicStr = "font-style: italic;";
        }
        QString str = italicStr + boldStr;
        emit styleChanged(str);
    }

    void changeboldStr(int state)
    {
        if (state == 0) {
            boldStr = "";
        } else {
            boldStr = "font-weight: bold;";
        }
        QString str = boldStr + italicStr;
        emit styleChanged(str);
    }
signals:
    void styleChanged(QString str);

};

//pushButton Normal样式设定浏览区域
class NormalStyleArea : public QScrollArea
{
    Q_OBJECT

public:
    NormalStyleArea(QWidget *parent = nullptr) : QScrollArea (parent)
    {
    }
};

//pushButton Hover样式设定浏览区域
class HoverStyleArea : public QScrollArea
{
    Q_OBJECT
public:
    HoverStyleArea(QWidget *parent = nullptr) : QScrollArea (parent)
    {

    }
};

//pushButton Hover样式设定浏览区域
class CheckedStyleArea : public QScrollArea
{
    Q_OBJECT
public:
    CheckedStyleArea(QWidget *parent = nullptr) : QScrollArea (parent)
    {

    }
};

class PressedStyleArea : public QScrollArea
{
    Q_OBJECT
public:
    PressedStyleArea(QWidget *parent = nullptr) : QScrollArea (parent)
    {

    }
};

//pushButton Hover样式设定面板
class HoverStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    HoverStyleTabPage(QWidget *parent = nullptr);
    QVBoxLayout *initPanel();

private:
    GetColor *borderColor;
    GetColor *backGroundColor;
    GetColor *fontColor;
    SliderWidthValueShow *radiusSize;
    SliderWidthValueShow *borderSize;

    QString borderSizeStr = "border-width: 0px;";
    QString radiusSizeStr = "border-radius: 0px;";
    QString fontColorStr = "color: black;";
    QString backGroundColorStr = "background-color: gray;";
    QString borderColorStr = "border-color: red;";

private slots:
    void borderColorChange(QString str);
    void backGroundColorChange(QString str);
    void fontColorChange(QString str);
    void borderSizeChange(QString str);
    void radiusSizeChange(QString str);

    void upDateHoverStyle();
signals:
    void hoverStyleChanged(QString str);

};

//pushButton Hover样式设定面板
class CheckedStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    CheckedStyleTabPage(QWidget *parent = nullptr);
    QVBoxLayout *initPanel();

private:
    GetColor *borderColor;
    GetColor *backGroundColor;
    GetColor *fontColor;
    SliderWidthValueShow *radiusSize;
    SliderWidthValueShow *borderSize;

    QString borderSizeStr = "border-width: 0px;";
    QString radiusSizeStr = "border-radius: 0px;";
    QString fontColorStr = "color: black;";
    QString backGroundColorStr = "background-color: gray;";
    QString borderColorStr = "border-color: red;";

private slots:
    void borderColorChange(QString str);
    void backGroundColorChange(QString str);
    void fontColorChange(QString str);
    void borderSizeChange(QString str);
    void radiusSizeChange(QString str);

    void upDateCheckedStyle();
signals:
    void checkedStyleChanged(QString str);
};

//pushButton pressed样式设定面板
class PressedStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    PressedStyleTabPage(QWidget *parent = nullptr);
    QVBoxLayout *initPanel();

private:
    GetColor *borderColor;
    GetColor *backGroundColor;
    GetColor *fontColor;
    SliderWidthValueShow *radiusSize;
    SliderWidthValueShow *borderSize;

    QString borderSizeStr = "border-width: 0px;";
    QString radiusSizeStr = "border-radius: 0px;";
    QString fontColorStr = "color: black;";
    QString backGroundColorStr = "background-color: gray;";
    QString borderColorStr = "border-color: red;";

private slots:
    void borderColorChange(QString str);
    void backGroundColorChange(QString str);
    void fontColorChange(QString str);
    void borderSizeChange(QString str);
    void radiusSizeChange(QString str);

    void upDatePressedStyle();
signals:
    void pressedStyleChanged(QString str);

};

//pushButton Normal样式设定面板
class NormalStyleTabPage : public QWidget
{
    Q_OBJECT

public:
    NormalStyleTabPage(QWidget *parent = nullptr);
    QVBoxLayout *initPanel();

private:
    GetColor *borderColor;
    GetColor *backGroundColor;
    GetColor *fontColor;
    QFontComboBox *fontFamily;
    SliderWidthValueShow *hSize, *vSize, *borderSize, *fontSize;
    SliderWidthValueShow *radiusSize;
    ItalicAndBoldWidget *italicAndBold;
    AlignAndDecorationWidget *alignAndDec;
    ShadowEffectWidget *shadowEffect;

    QString shadowStyleStr = "";
    QString fontFamilyStr = "";
    QString italicAndBoldStr = "";
    QString alignAndDecStr = "";
    QString hSizeStr = "max-width:0px;min-width:0px;";
    QString vSizeStr = "max-height:0px;min-height:0px;";
    QString borderSizeStr = "border-width: 0px;";
    QString fontSizeStr = "font-size: 12px;";
    QString radiusSizeStr = "border-radius: 0px;";
    QString fontColorStr = "color: black;";
    QString backGroundColorStr = "background-color: gray;";
    QString borderColorStr = "border-color: red;";

public slots:
    void borderColorChange(QString str);
    void backGroundColorChange(QString str);
    void fontColorChange(QString str);
    void fontFamilyChange(QFont font);
    void hSizeChange(QString str);
    void vSizeChange(QString str);
    void borderSizeChange(QString str);
    void fontSizeChange(QString str);
    void radiusSizeChange(QString str);
    void italicAndBoldChange(QString str);
    void alignAndDecChange(QString str);
    void shadowChange(QString str);

    void upDateNormalStyle();

signals:
    void normalStyleChanged(QString str);
};


#endif // PUSHBUTTON_H
