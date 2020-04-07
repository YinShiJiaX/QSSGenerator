#include "headers/inputwidgets.h"
#include "headers/slider.h"

#include <QTabWidget>

InputWidgetsTabWidget::InputWidgetsTabWidget(QWidget *parent) : QTabWidget (parent)
{
    setTabShape(QTabWidget::Triangular);
    SliderTabPage *sliderTabPage = new SliderTabPage;
    addTab(sliderTabPage, "Slider");
}
