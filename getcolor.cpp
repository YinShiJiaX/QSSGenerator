#include "getcolor.h"

#include <QPushButton>
#include <QGridLayout>
#include <QColorDialog>
#include <QColor>
#include <QDebug>
GetColor::GetColor(const QString str, QWidget *parent) : QWidget (parent)
{
    pushBtn = new QPushButton;
    colorDialog = new QColorDialog;
    colorDialog->setOption(QColorDialog::ShowAlphaChannel);
    pushBtn->setText(str);

    QGridLayout *gLayout = new QGridLayout;
    gLayout->addWidget(pushBtn);

    setLayout(gLayout);

    connect(pushBtn, &QPushButton::clicked, colorDialog, &QColorDialog::show);
    connect(colorDialog, &QColorDialog::currentColorChanged, this, &GetColor::causeColorChanged);


}

void GetColor::causeColorChanged(const QColor &color)
{
    int r, g, b, a;
    color.getRgb(&r, &g, &b, &a);
    QString str;
    str = "(" + QString::number(r) + ", " + QString::number(g) +
        + ", " + QString::number(b) + ", " + QString::number(a) + ");";

    emit colorChanged(str);
}
