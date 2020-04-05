#include "buttons.h"
#include "pushbutton.h"

#include <QTabWidget>

ButtonsTabWidget::ButtonsTabWidget(QWidget *parent) : QTabWidget (parent)
{
    setTabShape(QTabWidget::Triangular);
    PushButtonTabPage *pushBtnTabPage = new PushButtonTabPage;
    addTab(pushBtnTabPage, "PushButton");
}
