#include "sliderwidthvalueshow.h"

#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
SliderWidthValueShow::SliderWidthValueShow(const QString str,  int min, int max, QWidget *parent) : QWidget(parent)
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

void SliderWidthValueShow::causeChangeValue(int value)
{
    QString str;
    str = QString::number(value) + "px;";
    label->setText(indicateStr + str);
    emit valueChanged(str);
}

void SliderWidthValueShow::setValue(int value)
{
    slider->setValue(value);
}
