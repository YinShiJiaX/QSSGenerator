#include "widget.h"
#include "ui_widget.h"
#include "buttons.h"

#include <QStackedWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QListWidgetItem>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    stackedWidget = new QStackedWidget;
    stackedWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    initStackedWidget();

    listWidget = new QListWidget;
    listWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    QString widgetsTypeName;
    foreach (widgetsTypeName, widgetsTypeNameList) {
        new QListWidgetItem(widgetsTypeName, listWidget);
    }

    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(listWidget);
    hLayout->addWidget(stackedWidget);
    hLayout->setStretchFactor(listWidget, 1);
    hLayout->setStretchFactor(stackedWidget, 6);

    setLayout(hLayout);
    resize(700, 450);

}

void Widget::initStackedWidget()
{
    buttonsTab = new ButtonsTab;
    stackedWidget->addWidget(buttonsTab);
}

Widget::~Widget()
{
    delete ui;
}
