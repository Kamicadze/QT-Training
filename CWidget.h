#ifndef CWIDGET_H
#define CWIDGET_H

#include <QWidget>
#include <QtGui>
#include "CThreadChart.h"

namespace Ui {
class Widget;
}

class CWidget : public QWidget
{
    Q_OBJECT

public:
    explicit CWidget(QWidget *parent = 0);
    ~CWidget();




private:
    Ui::Widget *ui;
    CThreadChart **mThread;
    QGraphicsScene **scene=NULL;

    QList<QGraphicsLineItem *> chartScale10; //vertical scale bar for tens
    QList<QGraphicsLineItem *> chartScale1;  //vertical scale bar for ones
    //QList<QGraphicsLineItem *> chartScale05; //vertical scale bar for point fives
    QList<QGraphicsTextItem *> chartTxt10;   //text for scale for tens
    QList<QGraphicsTextItem *> chartTxt1;    //text for scale for ones
    //QList<QGraphicsTextItem *> chartTxt05;   //text for scale for point fives

    float *lastLine;
    float *vertLine;
    float *tmp;

    float scaleFactor;
    QString numbers[10];


private:
    void setingScene1();
    void setingScene2();
    void setingScene3();
    void setingScene4();

    int chartHandling(int, int);
    void paintCircle(QGraphicsScene, int, int);

    void chartVerticalBar(int sceneNumber, int posX, int posY1, int posY2, QString number, int type);
    void showScales(QList<QGraphicsLineItem*> scales, QList<QGraphicsTextItem *> txt);
    void hideScales(QList<QGraphicsLineItem*> scales, QList<QGraphicsTextItem *> txt);
    QString numberVisulizer(int number);
    void chartMaker(int sceneNumber, int xStart, int markStart, int lenght, int firstPoint, int numberOfPoints);

public slots:
    void onValueChanged(int, float);
    void onValueChanged2(int, float);
    void onValueChanged3(int, float);
    void onValueChanged4(int, float);


private slots:
    void pushButton_click();
    void pushButtonStop_click();
    void pushButtonIn_click();
    void pushButtonOut_click();
};

#endif // WIDGET_H
