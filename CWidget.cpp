#include "CWidget.h"
#include "ui_widget.h"
#include <QtGui>
#include <QString>
#include <stdlib.h>
#include <time.h>
#include <QDebug>


CWidget::CWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    scaleFactor=1;

    numbers[0]="0";
    numbers[1]="1";
    numbers[2]="2";
    numbers[3]="3";
    numbers[4]="4";
    numbers[5]="5";
    numbers[6]="6";
    numbers[7]="7";
    numbers[8]="8";
    numbers[9]="9";



    tmp=new float[12];
    for(int i=0; i<12; i++)
        tmp[i]=0;

    lastLine=new float[4];
    for(int i=0; i<4; i++)
        lastLine[i]=0;

    vertLine=new float[8];
    for(int i=0; i<8; i++)
        vertLine[i]=-100;

    mThread=new CThreadChart*[4];
    for(int i=0;i<4;i++)
    {
        mThread[i]=new CThreadChart(this);

    }

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(pushButton_click()));
    connect(ui->pushButtonStop, SIGNAL(clicked()), this, SLOT(pushButtonStop_click()));
    connect(ui->pushButtonIn, SIGNAL(clicked()), this, SLOT(pushButtonIn_click()));
    connect(ui->pushButtonOut, SIGNAL(clicked()), this, SLOT(pushButtonOut_click()));

    connect(mThread[0], SIGNAL(valueChanged(int, float)),
            this, SLOT(onValueChanged(int, float)));
    connect(mThread[1], SIGNAL(valueChanged(int, float)),
            this, SLOT(onValueChanged2(int, float)));
    connect(mThread[2], SIGNAL(valueChanged(int, float)),
            this, SLOT(onValueChanged3(int, float)));
    connect(mThread[3], SIGNAL(valueChanged(int, float)),
            this, SLOT(onValueChanged4(int, float)));


}

CWidget::~CWidget()
{
    delete ui;
    delete[] tmp;
    delete[] lastLine;
    delete[] vertLine;
}

///4 methods to get values from threads
void CWidget::onValueChanged(int count, float timer)
{

    scene[0]->addEllipse(10.0+timer*12.0, count-3, 5, 5, QPen(), QBrush(Qt::SolidPattern));

    if(-100!=vertLine[0] && -100!=vertLine[1])
    {
        scene[0]->addLine(vertLine[0]+2.5, vertLine[1]+2.5, 10.0+timer*12.0+2.5, count-3+2.5, QPen());
    }
    vertLine[0]=10+timer*12;
    vertLine[1]=count-3;

    if(lastLine[0]-30<vertLine[0])
    {
        scene[0]->addLine(lastLine[0], 205 ,lastLine[0]+300 , 205, QPen());
        chartMaker(0, 10, 205, 5, (lastLine[0]-10)/12 +1, 300/12 -1);
        if(1>=scaleFactor)
            hideScales(chartScale1, chartTxt1);
        lastLine[0]=lastLine[0]+300;
    }

    ui->chart1->setScene(scene[0]);

}
void CWidget::onValueChanged2(int count, float timer)
{

    scene[1]->addEllipse(10+(timer*12), count*0.67-3, 5, 5, QPen(), QBrush(Qt::SolidPattern));

    if(-100!=vertLine[2] && -100!=vertLine[3])
    {
        scene[1]->addLine(vertLine[2]+2.5, vertLine[3]+2.5, 10+timer*12+2.5, count*0.67-3+2.5, QPen());
    }
    vertLine[2]=10+timer*12;
    vertLine[3]=count*0.67-3;

    if(lastLine[1]-30<vertLine[2])
    {
        scene[1]->addLine(lastLine[1], 75*0.67+5 ,lastLine[1]+300 , 75*0.67+5, QPen());
        chartMaker(1, 10, 75*0.67 +5, 5, (lastLine[1]-10)/12 +1, 300/12 -1);
        if(1>=scaleFactor)
            hideScales(chartScale1, chartTxt1);
        lastLine[1]=lastLine[1]+300;
    }

    ui->chart2->setScene(scene[1]);

}
void CWidget::onValueChanged3(int count, float timer)
{

    scene[2]->addEllipse(10+(timer*12), count-3, 5, 5, QPen(), QBrush(Qt::SolidPattern));

    if(-100!=vertLine[4] && -100!=vertLine[5])
    {
        scene[2]->addLine(vertLine[4]+2.5, vertLine[5]+2.5, 10+timer*12+2.5, count-3+2.5, QPen());
    }
    vertLine[4]=10+timer*12;
    vertLine[5]=count-3;

    if(lastLine[2]-30<vertLine[4])
    {
        scene[2]->addLine(lastLine[2], 105 ,lastLine[2]+300 , 105, QPen());
        chartMaker(2, 10, 105, 5, (lastLine[2]-10)/12 +1, 300/12 -1);
        if(1>=scaleFactor)
            hideScales(chartScale1, chartTxt1);
        lastLine[2]=lastLine[2]+300;
    }

    ui->chart3->setScene(scene[2]);

}
void CWidget::onValueChanged4(int count, float timer)
{

    scene[3]->addEllipse(10+(timer*12), count*30-3, 5, 5, QPen(), QBrush(Qt::SolidPattern));

    if(-100!=vertLine[6] && -100!=vertLine[7])
    {
        scene[3]->addLine(vertLine[6]+2.5, vertLine[7]+2.5, 10+timer*12+2.5, count*30-3+2.5, QPen());
    }
    vertLine[6]=10+timer*12;
    vertLine[7]=count*30-3;

    if(lastLine[3]-30<vertLine[6])
    {
        scene[3]->addLine(lastLine[3], 35 ,lastLine[3]+300 , 35, QPen());
        chartMaker(3, 10, 35, 5, (lastLine[3]-10)/12 +1, 300/12 -1);
        if(1>=scaleFactor)
            hideScales(chartScale1, chartTxt1);

        lastLine[3]=lastLine[3]+300;
    }

    ui->chart4->setScene(scene[3]);

}

///zoom in action
void CWidget::pushButtonIn_click()
{
    if(2>scaleFactor)
    {
        scaleFactor+=0.5;
        ui->chart1->scale(2,2);
        ui->chart2->scale(2,2);
        ui->chart3->scale(2,2);
        ui->chart4->scale(2,2);
        if(1<scaleFactor)
            showScales(chartScale1, chartTxt1);
    }
}

///zoom out action
void CWidget::pushButtonOut_click()
{
    if(0.5<scaleFactor)
    {
        scaleFactor-=0.5;
        ui->chart1->scale(0.5,0.5);
        ui->chart2->scale(0.5,0.5);
        ui->chart3->scale(0.5,0.5);
        ui->chart4->scale(0.5,0.5);
        if(1>=scaleFactor)
            hideScales(chartScale1, chartTxt1);
    }
}

///action when clicking start button
void CWidget::pushButton_click()
{

    if(NULL==scene)
    {
        scene=new QGraphicsScene*[4];
        for(int i=0; i<4; i++)
        {
            if(0==i)
            {
                scene[i]= new QGraphicsScene(ui->chart1);

                scene[i]->addLine(0, 95 ,0 , 205, QPen());
                scene[i]->addLine(0, 205 ,600 , 205, QPen());
                lastLine[i]=600;

                scene[i]->addLine(-5, 100, 0, 100, QPen());
                QGraphicsTextItem *txt = scene[i]->addText("200");
                txt->scale(0.6, 0.6);
                txt->setPos(-25, 91);

                scene[i]->addLine(-5, 200, 0, 200, QPen());
                QGraphicsTextItem *txt2 = scene[i]->addText("100");
                txt2->scale(0.6, 0.6);
                txt2->setPos(-25, 191);


                chartMaker(i, 10, 205, 5, 0, 590/12);
                hideScales(chartScale1, chartTxt1);


                //mThread[i]->initValues(100,101, 1, scene[0], ui->chart1);
                mThread[i]->initValues(100, 101);
                ui->chart1->setScene(scene[i]);
            }
            else if(1==i)
            {
                scene[i]= new QGraphicsScene(ui->chart2);

                scene[i]->addLine(0, 75*0.67 +5 ,0 , -75*0.67 -5, QPen());
                scene[i]->addLine(0, 75*0.67 +5 ,600 , 75*0.67 +5, QPen());
                lastLine[i]=600;

                scene[i]->addLine(-5, 75*0.67, 0, 75*0.67, QPen());
                QGraphicsTextItem *txt = scene[i]->addText("-75");
                txt->scale(0.6, 0.6);
                txt->setPos(-25, 75*0.67 - 9);

                scene[i]->addLine(-5, -75*0.67, 0, -75*0.67, QPen());
                QGraphicsTextItem *txt2 = scene[i]->addText("75");
                txt2->scale(0.6, 0.6);
                txt2->setPos(-25, -75*0.67 - 6);

                chartMaker(i, 10, 75*0.67 +5, 5, 0, 590/12);
                hideScales(chartScale1, chartTxt1);

                mThread[i]->initValues(-75,151);
                ui->chart2->setScene(scene[i]);
            }
            else if(2==i)
            {
                scene[i]= new QGraphicsScene(ui->chart3);

                scene[i]->addLine(0, -5 ,0 , 105, QPen());
                scene[i]->addLine(0, 105 ,600 , 105, QPen());
                lastLine[i]=600;

                scene[i]->addLine(-5, 100, 0, 100, QPen());
                QGraphicsTextItem *txt = scene[i]->addText("0");
                txt->scale(0.6, 0.6);
                txt->setPos(-20,  91);

                scene[i]->addLine(-5, 0, 0, 0, QPen());
                QGraphicsTextItem *txt2 = scene[i]->addText("100");
                txt2->scale(0.6, 0.6);
                txt2->setPos(-25, -9);

                chartMaker(i, 10, 105, 5, 0, 590/12);
                hideScales(chartScale1, chartTxt1);


                mThread[i]->initValues(0,101);
                ui->chart3->setScene(scene[i]);
            }
            else if(3==i)
            {
                scene[i]= new QGraphicsScene(ui->chart4);

                scene[i]->addLine(0, -5  ,0 , 35, QPen());
                scene[i]->addLine(0, 35 ,600 , 35, QPen());
                lastLine[i]=600;

                scene[i]->addLine(-5, 30, 0, 30, QPen());
                QGraphicsTextItem *txt = scene[i]->addText("0");
                txt->scale(0.6, 0.6);
                txt->setPos(-20,  21);

                scene[i]->addLine(-5, 0, 0, 0, QPen());
                QGraphicsTextItem *txt2 = scene[i]->addText("1");
                txt2->scale(0.6, 0.6);
                txt2->setPos(-20, -9);

                //scene[i]->addLine(10+2.5, 35, 10+2.5, 40, QPen());
                //scene[i]->addLine(22+2.5, 35, 22+2.5, 40, QPen());

                chartMaker(i, 10, 35, 5, 0, 590/12);
                hideScales(chartScale1, chartTxt1);

                mThread[i]->initValues(0,2);
                ui->chart4->setScene(scene[i]);
            }
        }
    }

    //mThread[0]->Stop=false;
    mThread[0]->start();
    //mThread[1]->Stop=false;
    mThread[1]->start();
    //mThread[2]->Stop=false;
    mThread[2]->start();
    //mThread[3]->Stop=false;
    mThread[3]->start();
}
///reaction to pressing stop button
void CWidget::pushButtonStop_click()
{
    mThread[0]->Stop=true;
    mThread[1]->Stop=true;
    mThread[2]->Stop=true;
    mThread[3]->Stop=true;
}

///This method creates measurement bars(vertical) with txt for them
void CWidget::chartVerticalBar(int sceneNumber, int posX, int posY1, int posY2, QString number, int type)
{
    QGraphicsTextItem *txt;
    if(1==type)
    {
        chartScale10.append(scene[sceneNumber]->addLine(posX+2.5, posY1, posX+2.5, posY2, QPen()));
        txt=scene[sceneNumber]->addText(number);
        chartTxt10.append(txt);
    }
    else if(2==type)
    {
        chartScale1.append(scene[sceneNumber]->addLine(posX+2.5, posY1, posX+2.5, posY2, QPen()));
        txt=scene[sceneNumber]->addText(number);
        chartTxt1.append(txt);

    }
    else
    {
        //TODO: Error handling
    }

    if(0==((posX-10)/12)%2)
    {
        txt->scale(0.6, 0.6);
        txt->setPos(posX-2.5, posY2);
    }
    else
    {
        txt->scale(0.6, 0.6);
        txt->setPos(posX-2.5, posY2+10);
    }
    if(0==sceneNumber)
        ui->chart1->setScene(scene[sceneNumber]);
    else if(1==sceneNumber)
        ui->chart2->setScene(scene[sceneNumber]);
    else if(2==sceneNumber)
        ui->chart3->setScene(scene[sceneNumber]);
    else if(3==sceneNumber)
        ui->chart4->setScene(scene[sceneNumber]);


}

///method to show hiden scale marks and texts
void CWidget::showScales(QList<QGraphicsLineItem*> scales, QList<QGraphicsTextItem *> txt)
{
    for(int it=0; it<scales.size(); it++)
    {
        scales.at(it)->show();
        txt.at(it)->show();
    }
}

///method to hide visible scale marks and texts
void CWidget::hideScales(QList<QGraphicsLineItem*> scales, QList<QGraphicsTextItem *> txt)
{
    for(int it=0; it<scales.size(); it++)
    {
        scales.at(it)->hide();
        txt.at(it)->hide();
    }
}

///method to convert int numbers to string
QString CWidget::numberVisulizer(int number)
{
    QString txt;
    //int i=10;
    int tmp=0;
    while(1)
    {
        tmp=number%10;
        txt.push_front(numbers[tmp]);
        number=number/10;
        if(0==number)
        {
            break;
        }

    }
    return txt;

}

///Method that make creating scale markers easyer to automate
void CWidget::chartMaker(int sceneNumber, int xStart, int markStart, int lenght, int firstPoint, int numberOfPoints)
{
    for(int i=firstPoint; i<=(firstPoint+numberOfPoints); i++)
    {
        if(0==i%10)
            chartVerticalBar(sceneNumber, xStart+(i*12), markStart, markStart+lenght, numberVisulizer(i), 1);
        else
            chartVerticalBar(sceneNumber, xStart+(i*12), markStart, markStart+lenght, numberVisulizer(i), 2);
    }
}


