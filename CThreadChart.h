#ifndef CTHREADCHART_H
#define CTHREADCHART_H
#include <QThread>
#include <QtGui>
#include <QWidget>



class CThreadChart :  public QThread
{
   Q_OBJECT

public:
    explicit CThreadChart(QObject *parent = 0, bool b=false);
    void run();
    bool Stop;
    void initValues(int sPoint, int rPoint, int chartNr, QGraphicsScene *scene, QGraphicsView *chart);
    void initValues(int sPoint, int rPoint);

protected:
    void draw(int, float);

private:
    QGraphicsScene *scene;
    QGraphicsView *chart;
   // int yPoint;
    int startPoint;
    int range;
    int chartNr;
signals:
    void valueChanged(int, float);


};


#endif // THREADCHART_H
