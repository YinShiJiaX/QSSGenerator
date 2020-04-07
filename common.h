#ifndef COMMON_H
#define COMMON_H


#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QGraphicsDropShadowEffect>
#include <QColorDialog>
#include <QFileDialog>
#include <QScrollArea>
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
        vlayout->setContentsMargins(0, 0, 0, 0);
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

class GetColor : public QPushButton
{
    Q_OBJECT
public:
    explicit GetColor(const QString str, QWidget *parent = nullptr) : QPushButton(parent)
    {
        colorDialog = new QColorDialog;
        colorDialog->setOption(QColorDialog::ShowAlphaChannel);
        setText(str);

        connect(this, &QPushButton::clicked, colorDialog, &QColorDialog::show);
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
    QColorDialog *colorDialog;
};

class MyScrollArea : public QScrollArea
{
    Q_OBJECT

public:
    MyScrollArea(QWidget *parent = nullptr) : QScrollArea (parent)
    {
    }
};

class ButtonForImageAccess : public QPushButton
{
    Q_OBJECT
public:
    explicit ButtonForImageAccess(QString str, QWidget *parent = nullptr) : QPushButton(parent)
    {
        setText(str);
        connect(this, &QPushButton::clicked, this, &ButtonForImageAccess::changeimage);
    }
signals:
    void imageChanged(QString str);
private slots:
    void changeimage()
    {
        QString path=QFileDialog::getOpenFileName(this,tr("选择图片"),"C:/Users/jiage/Desktop/folder/QT/QSSGenerator/picture","Images (*.png *.xpm *.jpg)");
        emit imageChanged(path);
    }
};
#endif // COMMON_H
