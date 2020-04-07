#include "headers/buttons.h"
#include "headers/pushbutton.h"

#include <QTabWidget>

ButtonsTabWidget::ButtonsTabWidget(QWidget *parent) : QTabWidget (parent)
{
    setTabShape(QTabWidget::Triangular);
    PushButtonTabPage *pushBtnTabPage = new PushButtonTabPage;
    addTab(pushBtnTabPage, "PushButton");
}
