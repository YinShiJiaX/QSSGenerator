#include "headers/displaywidgets.h"
#include "headers/progressbar.h"

#include <QTabWidget>

DisplayWidgetsTabWidget::DisplayWidgetsTabWidget(QWidget *parent) : QTabWidget (parent)
{
    setTabShape(QTabWidget::Triangular);
    ProgressBarTabPage *progressBarTabPage = new ProgressBarTabPage;
    addTab(progressBarTabPage, "Progress");
}
