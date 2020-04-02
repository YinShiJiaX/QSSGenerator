#include "buttons.h"
#include "pushbutton.h"

#include <QTabWidget>

ButtonsTab::ButtonsTab(QWidget *parent) : QTabWidget (parent)
{
    setTabShape(QTabWidget::Triangular);
    PushButtonPage *pushBtnPage = new PushButtonPage;
    addTab(pushBtnPage, "PushButton");
}
