#ifndef SLIDER_H
#define SLIDER_H

#include "common.h"

#include <QWidget>
#include <QSlider>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QScrollArea>

class SliderStyleTabWidget;
class BackgroundStyleTabPage;
class GrooveStyleTabPage;
class HandleStyleTabPage;
class SubStyleTabPage;
class AddStyleTabPage;
//pushButton 样式生成总页面
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
    QString backgroundStr;

    BackgroundStyleTabPage *backgroundTabPage;
    MyScrollArea *backgroundScrollArea;
    GrooveStyleTabPage *grooveTabPage;
    MyScrollArea *grooveScrollArea;
    HandleStyleTabPage *handleTabPage;
    MyScrollArea *handleScrollArea;
    SubStyleTabPage *subTabPage;
    MyScrollArea *subScrollArea;
    AddStyleTabPage *addTabPage;
    MyScrollArea *addScrollArea;
public slots:
    void changeBackgroundStyleStr(QString str);
    void changeGrooveStyleStr(QString str);
    void changeHandleStyleStr(QString str);
    void changeSubStyleStr(QString str);
    void changeAddStyleStr(QString str);


    void changeStyleStr();

signals:
    void styleChanged(QString styleStr);


};

class BackgroundStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    BackgroundStyleTabPage(QWidget *parent = nullptr);

    QVBoxLayout *initPanel();
private:
    QString backgroundColorStr;
    QString borderColorStr;
    QString borderWidthStr;
    QString borderRadiusStr;

    GetColor *backgroundColor;
    GetColor *borderColor;
    SliderWidthValueShow *borderWidth;
    SliderWidthValueShow *borderRadius;
public slots:
    void changeBorderColorStr(QString str);
    void changeBackgroundColorStr(QString str);
    void changeBorderWidthStr(QString str);
    void changeBorderRadiusStr(QString str);

    void upDateStyle();
signals:
    void styleChanged(QString str);
};

class GrooveStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    GrooveStyleTabPage(QWidget *parent = nullptr);

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

class HandleStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    HandleStyleTabPage(QWidget *parent = nullptr);

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

class SubStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    SubStyleTabPage(QWidget *parent = nullptr);

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

class AddStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    AddStyleTabPage(QWidget *parent = nullptr);

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
