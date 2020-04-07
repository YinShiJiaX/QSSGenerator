#include "widget.h"
#include "ui_widget.h"
#include "headers/buttons.h"
#include "headers/inputwidgets.h"
#include "headers/displaywidgets.h"

#include <QStackedWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QListWidgetItem>
#include <QSplitter>
#include <QFileSystemModel>
#include <QListView>
#include <QDebug>

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

    QSplitter *splitter = new QSplitter;

    splitter->addWidget(listWidget);
    splitter->addWidget(stackedWidget);
    splitter->setStretchFactor(0, 1);
    splitter->setStretchFactor(1, 6);

    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(splitter);

    setLayout(gLayout);
    resize(800, 450);

    connect(listWidget, &QListWidget::currentRowChanged, stackedWidget, &QStackedWidget::setCurrentIndex);

}

void Widget::initStackedWidget()
{
    buttonsTabWidget = new ButtonsTabWidget;
    inputWidgetsTabWidget = new InputWidgetsTabWidget;
    displayWidgetsTabWidget = new DisplayWidgetsTabWidget;
    stackedWidget->addWidget(buttonsTabWidget);
    stackedWidget->addWidget(inputWidgetsTabWidget);
    stackedWidget->addWidget(displayWidgetsTabWidget);
}

Widget::~Widget()
{
    delete ui;
}
