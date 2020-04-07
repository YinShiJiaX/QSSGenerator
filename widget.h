#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVector>
class QStackedWidget;
class QListWidget;
class QTabWidget;
class ButtonsTabWidget;
class InputWidgetsTabWidget;

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    void initStackedWidget();

private:
    Ui::Widget *ui;
    QListWidget *listWidget;
    QStackedWidget *stackedWidget;

    QStringList widgetsTypeNameList = {"Buttons",
                                      "Input Widgets"};

    ButtonsTabWidget *buttonsTabWidget;
    InputWidgetsTabWidget *inputWidgetsTabWidget;

};

#endif // WIDGET_H
