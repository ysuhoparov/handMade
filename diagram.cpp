#include "diagram.h"

#include <QGraphicsTextItem>
#include <QGraphicsTextItem>

Diagram::Diagram(QFrame* frame)
{
    graphicsView = new QGraphicsView(frame);
    graphicsView->resize(gsize*1.5, gsize);
    graphicsView->move(gleft, gtop);

    graphicsScene = new QGraphicsScene();
    graphicsView->setScene(graphicsScene);

}


void Diagram::refresh(const QNetworkDatagram & datagram)
{
    auto data = datagram.data();

    grid();
    axisValues();

    // Построение графиков
    constexpr int datagramSize = 8192;
    int sum=0, i=0, indexMax=0;
    qint16 dataMax_= 0, dataMax = 0, dataMean_=0, dataMean =0, max = -30000;
    pen.setWidth(2);
    for(unsigned int j = 0; j < datagramSize; j+=2 ) {
        qint16 dt = (data.at(j) << 8) | data.at(j+1);   // byte xchg

        if(dt > max) {    // Global max
            max = dt;
            indexMax = j/2;
        }

        if(j%20) {      // Усреднение и max по 10-ти точкам
            sum+=dt;
            if(dt > dataMax)
                dataMax = dt;
        }
        else {
            dataMax /= 10;
            dataMean = sum/100;
            sum=0;

            pen.setColor(Qt::magenta);
            graphicsScene->addLine(i, ybot-dataMax_ , i+1, ybot-dataMax , pen);
            dataMax_=dataMax;

            pen.setColor(Qt::blue);
            graphicsScene->addLine(i, ybot-dataMean_ , i+1, ybot-dataMean , pen);
            dataMean_=dataMean;
            i++;   
        }
    }

    QGraphicsTextItem *maxy = new QGraphicsTextItem("Max Y = " + QString::number(max));
    int xpos = 80 +indexMax/8 ;
    if ( xpos  > 300 ) xpos = 300;
    maxy->setPos(xpos, 60);
    graphicsScene->addItem(maxy);
    QGraphicsTextItem *maxx = new QGraphicsTextItem("index = " + QString::number(indexMax));
    maxx->setPos(xpos, 80);
    graphicsScene->addItem(maxx);

    legend();

}


void Diagram::legend()
{
    pen.setWidth(2);
    pen.setColor(Qt::magenta);
    graphicsScene->addLine(250, 190 , 290, 190 , pen);

    pen.setColor(Qt::blue);
    graphicsScene->addLine(250, 210 , 290, 210 , pen);

    pen.setColor(Qt::black);

    QGraphicsTextItem *legm = new QGraphicsTextItem("Mаксимум 10 т.");
    legm->setPos(300, 178);
    graphicsScene->addItem(legm);

    QGraphicsTextItem *leg = new QGraphicsTextItem("Среднее 10 т.");
    leg->setPos(300, 198);
    graphicsScene->addItem(leg);

};

void Diagram::grid()
{
    graphicsScene->clear();

    pen.setColor(Qt::lightGray);

    for(int j=1; j <22; j++)   {  // vert line
        if(j%5)   pen.setWidth(1);
        else pen.setWidth(2);
        graphicsScene->addLine(j*gridSpacing, ytop, j*gridSpacing, ybot, pen);
    }

    for(int j=0; j <22; j++) {  // gor line
        graphicsScene->addLine(xleft, gridSpacing*j, xright, gridSpacing*j, pen);
        if((ybot/gridSpacing - j-1)%5)   pen.setWidth(1);
        else pen.setWidth(2);
    }

};


void Diagram::axisValues()
{
    pen.setWidth(2);
    pen.setColor(Qt::black);
    graphicsScene->addLine(0, ybot , xright, ybot , pen);
    graphicsScene->addLine(0, ybot , 0, 0 , pen);

    QGraphicsTextItem *axis = new QGraphicsTextItem("0");
    axis->setPos(-8, ybot+4);
    graphicsScene->addItem(axis);

    QGraphicsTextItem *axis1 = new QGraphicsTextItem("1000");
    axis1->setPos(84, ybot+4);
    graphicsScene->addItem(axis1);

    QGraphicsTextItem *axis2 = new QGraphicsTextItem("2000");
    axis2->setPos(184, ybot+4);
    graphicsScene->addItem(axis2);

    QGraphicsTextItem *axis3 = new QGraphicsTextItem("3000");
    axis3->setPos(284, ybot+4);
    graphicsScene->addItem(axis3);

    QGraphicsTextItem *axis4 = new QGraphicsTextItem("4000");
    axis4->setPos(384, ybot+4);
    graphicsScene->addItem(axis4);

    ///yaxis
    QGraphicsTextItem *axis1y = new QGraphicsTextItem("1000");
    axis1y->setPos(-32, ybot-112);
    graphicsScene->addItem(axis1y);

    QGraphicsTextItem *axis2y = new QGraphicsTextItem("2000");
    axis2y->setPos(-32, ybot-212);
    graphicsScene->addItem(axis2y);

    QGraphicsTextItem *axis3y = new QGraphicsTextItem("3000");
    axis3y->setPos(-32, ybot-312);
    graphicsScene->addItem(axis3y);

    QGraphicsTextItem *axis4y = new QGraphicsTextItem("4000");
    axis4y->setPos(-32, ybot-412);
    graphicsScene->addItem(axis4y);;
}
