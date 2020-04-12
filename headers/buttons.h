#ifndef BUTTONS_H
#define BUTTONS_H

#include <QTabWidget>
class ButtonsTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    ButtonsTabWidget(QWidget *parent = nullptr);

signals:
    void styleSheetGenerated(QString str);
};

#endif // BUTTONS_H
