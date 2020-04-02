#ifndef GETCOLOR_H
#define GETCOLOR_H

#include <QWidget>

class QColorDialog;
class QPushButton;
class QColor;

class GetColor : public QWidget
{
    Q_OBJECT
public:
    explicit GetColor(const QString str, QWidget *parent = nullptr);

private slots:
    void causeColorChanged(const QColor &color);

signals:
    void colorChanged(QString colorStr);

private:
    QPushButton *pushBtn;
    QColorDialog *colorDialog;
};

#endif // GETCOLOR_H
