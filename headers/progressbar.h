#ifndef PROGRESSBAR_H
#define PROGRESSBAR_H

#include "common.h"

#include <QWidget>
#include <QProgressBar>
#include <QTableWidget>
#include <QVBoxLayout>

class ProgressBarTabPage;
class ProgressBarStyleTabWidget;
class ProgressBarTopStyleTabPage;
class ProgressBarChunkStyleTabPage;

class ProgressBarTabPage : public QWidget
{
    Q_OBJECT
public:
    ProgressBarTabPage(QWidget *parent = nullptr);
private:
    QProgressBar *progressBar;
    ProgressBarStyleTabWidget *styleTab;
};

class ProgressBarStyleTabWidget : public QTabWidget
{
    Q_OBJECT
public:
    ProgressBarStyleTabWidget(QWidget *parent = nullptr);
private:
    QString topStr;
    QString chunkStr;

    ProgressBarTopStyleTabPage *topTabPage;
    MyScrollArea *topScrollArea;
    ProgressBarChunkStyleTabPage *chunkTabPage;
    MyScrollArea *chunkScrollArea;

signals:
    void styleChanged(QString str);

private slots:
    void changeTopStyleStr(QString str);
    void changeChunkStyleStr(QString str);
    void upDateStyle();
};

class ProgressBarTopStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    ProgressBarTopStyleTabPage(QWidget *parent = nullptr);

    QVBoxLayout *initPanel();
    QString backgroundColorStr = "background-color: white;";
    QString borderColorStr = "border-color: white;";
    QString borderWidthStr;
    QString borderRadiusStr;
    QString textAlignStr = "text-align: center;";
    QString hSizeStr;
    QString vSizeStr;

    GetColor *backgroundColor;
    GetColor *borderColor;
    SliderWidthValueShow *borderWidth;
    SliderWidthValueShow *borderRadius;
    AlignChooseComboBox *textAlign;
    SliderWidthValueShow *vSize;
    SliderWidthValueShow *hSize;

signals:
    void styleChanged(QString str);

private slots:
    void changeBorderColorStr(QString str);
    void changeBackgroundColorStr(QString str);
    void changeBorderWidthStr(QString str);
    void changeBorderRadiusStr(QString str);
    void changeTextAlignStr(QString str);
    void changevSizeStr(QString str);
    void changehSizeStr(QString str);

    void upDateStyle();
};

class ProgressBarChunkStyleTabPage : public QWidget
{
    Q_OBJECT
public:
    ProgressBarChunkStyleTabPage(QWidget *parent = nullptr);

    QVBoxLayout *initPanel();
    QString backgroundColorStr = "background-color: white;";
    QString borderColorStr = "border-color: white;";
    QString borderWidthStr;
    QString borderRadiusStr;
    QString widthStr;
    QString marginStr;

    GetColor *backgroundColor;
    GetColor *borderColor;
    SliderWidthValueShow *borderWidth;
    SliderWidthValueShow *borderRadius;
    SliderWidthValueShow *width;
    SliderWidthValueShow *margin;

signals:
    void styleChanged(QString str);

private slots:
    void changeBorderColorStr(QString str);
    void changeBackgroundColorStr(QString str);
    void changeBorderWidthStr(QString str);
    void changeBorderRadiusStr(QString str);
    void changeWidthStr(QString str);
    void changeMarginStr(QString str);

    void upDateStyle();
};
#endif /* PROGRESSBAR_H */
