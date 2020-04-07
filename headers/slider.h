#ifndef SLIDER_H
#define SLIDER_H

#include "common.h"

#include <QWidget>
#include <QSlider>
#include <QTabWidget>
#include <QVBoxLayout>

class SliderTabPage;
class SliderStyleTabWidget;
class SliderTopStyleTabPage;
class SliderGrooveStyleTabPage;
class SliderHandleStyleTabPage;
class SliderSubStyleTabPage;
class SliderAddStyleTabPage;
//slider 样式生成总页面
class SliderTabPage : public QWidget
{
    Q_OBJECT
public:
    SliderTabPage(QWidget *parent = nullptr);

private:
    QSlider *slider;
    SliderStyleTabWidget *styleTab;


};

class SliderStyleTabWidget : public QTabWidget
{
    Q_OBJECT
public:

    SliderStyleTabWidget(QWidget *parent = nullptr);
private:
    QString grooveStr;
    QString handleStr;
    QString addStr;
    QString subStr;
    QString topStr;

    SliderTopStyleTabPage *topTabPage;
    MyScrollArea *topScrollArea;
    SliderGrooveStyleTabPage *grooveTabPage;
    MyScrollArea *grooveScrollArea;
    SliderHandleStyleTabPage *handleTabPage;
    MyScrollArea *handleScrollArea;
    SliderSubStyleTabPage *subTabPage;
    MyScrollArea *subScrollArea;
    SliderAddStyleTabPage *addTabPage;
    MyScrollArea *addScrollArea;
private slots:
    void changeTopStyleStr(QString str);
    void changeGrooveStyleStr(QString str);
    void changeHandleStyleStr(QString str);
    void changeSubStyleStr(QString str);
    void changeAddStyleStr(QString str);

    void upDateStyle();
signals:
    void styleChanged(QString str);


};

class SliderTopStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    SliderTopStyleTabPage(QWidget *parent = nullptr);

private:
    QVBoxLayout *initPanel();
    QString backgroundColorStr;
    QString borderColorStr;
    QString borderWidthStr;
    QString borderRadiusStr;

    GetColor *backgroundColor;
    GetColor *borderColor;
    SliderWidthValueShow *borderWidth;
    SliderWidthValueShow *borderRadius;
private slots:
    void changeBorderColorStr(QString str);
    void changeBackgroundColorStr(QString str);
    void changeBorderWidthStr(QString str);
    void changeBorderRadiusStr(QString str);

    void upDateStyle();
signals:
    void styleChanged(QString str);
};

class SliderGrooveStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    SliderGrooveStyleTabPage(QWidget *parent = nullptr);

    QVBoxLayout *initPanel();
private:
    QString backgroundColorStr;
    QString borderColorStr;
    QString borderWidthStr;
    QString borderRadiusStr;
    QString heightStr;

    GetColor *backgroundColor;
    GetColor *borderColor;
    SliderWidthValueShow *borderWidth;
    SliderWidthValueShow *borderRadius;
    SliderWidthValueShow *height;
public slots:
    void changeBorderColorStr(QString str);
    void changeBackgroundColorStr(QString str);
    void changeBorderWidthStr(QString str);
    void changeBorderRadiusStr(QString str);
    void changeHeightStr(QString str);

    void upDateStyle();
signals:
    void styleChanged(QString);
};

class SliderHandleStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    SliderHandleStyleTabPage(QWidget *parent = nullptr);

    QVBoxLayout *initPanel();
private:
    QString backgroundColorStr;
    QString borderColorStr;
    QString borderWidthStr;
    QString borderRadiusStr;
    QString widthStr;
    QString marginTopStr;
    QString marginBottomStr;
    QString marginLeftStr;
    QString marginRightStr;

    GetColor *backgroundColor;
    GetColor *borderColor;
    SliderWidthValueShow *borderWidth;
    SliderWidthValueShow *borderRadius;
    SliderWidthValueShow *width;
    SliderWidthValueShow *marginTop;
    SliderWidthValueShow *marginBottom;
    SliderWidthValueShow *marginLeft;
    SliderWidthValueShow *marginRight;
public slots:
    void changeBorderColorStr(QString str);
    void changeBackgroundColorStr(QString str);
    void changeBorderWidthStr(QString str);
    void changeBorderRadiusStr(QString str);
    void changeWidthStr(QString str);
    void changeMarginTopStr(QString str);
    void changeMarginBottomStr(QString str);
    void changeMarginLeftStr(QString str);
    void changeMarginRightStr(QString str);

    void upDateStyle();
signals:
    void styleChanged(QString);
};

class SliderSubStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    SliderSubStyleTabPage(QWidget *parent = nullptr);

    QVBoxLayout *initPanel();
private:
    QString backgroundColorStr;

    GetColor *backgroundColor;
public slots:
    void changeBackgroundColorStr(QString str);

    void upDateStyle();
signals:
    void styleChanged(QString);
};

class SliderAddStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    SliderAddStyleTabPage(QWidget *parent = nullptr);

    QVBoxLayout *initPanel();
private:
    QString backgroundColorStr;

    GetColor *backgroundColor;
public slots:
    void changeBackgroundColorStr(QString str);

    void upDateStyle();
signals:
    void styleChanged(QString str);
};
#endif // SLIDER_H
