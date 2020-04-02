#ifndef SLIDERWIDTHVALUESHOW_H
#define SLIDERWIDTHVALUESHOW_H

#include <QWidget>
class QLabel;
class QSlider;

class SliderWidthValueShow : public QWidget
{
    Q_OBJECT
public:
    explicit SliderWidthValueShow(const QString str,  int min, int max, QWidget *parent = nullptr);
    void setValue(int value);

signals:
    void valueChanged(QString str);

public slots:
    void causeChangeValue(int value);

private:
    QLabel *label;
    QSlider *slider;
    QString indicateStr;
    QString valueStr;
};

#endif // SLIDERWIDTHVALUESHOW_H
