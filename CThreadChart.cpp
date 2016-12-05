#include "CThreadChart.h"
#include <QDebug>

CThreadChart::CThreadChart(QObject *parent, bool b)
    :QThread(parent),
      Stop(b)
{

}


void CThreadChart::run()
{
    QTime myTimer;
    myTimer.start();

    while(1)
    {
    if(this->Stop)
        break;
    int i=0;
    srand(time(NULL));
    i=rand()%range + startPoint;
    if(1==chartNr)
    {
        float nTime=myTimer.elapsed()/1000.0;
        draw(i, nTime);

    }
    else
    {
        float nTime=myTimer.elapsed()/1000.0;
        emit valueChanged(i, nTime);
    }

    this->sleep(1);

    }
}

void CThreadChart::initValues(int sPoint, int rPoint, int givenChartNr, QGraphicsScene *givenScene, QGraphicsView *chart)
{
    this->startPoint=sPoint;
    this->range=rPoint;
    this->chartNr=givenChartNr;
    this->scene=givenScene;
    this->chart=chart;

}

void CThreadChart::initValues(int sPoint, int rPoint)
{
    this->startPoint=sPoint;
    this->range=rPoint;

}

void CThreadChart::draw(int i, float timer)
{
    scene->addEllipse(10+(12*timer), i-3, 5, 5, QPen(), QBrush(Qt::SolidPattern));

    chart->setScene(scene);

}
