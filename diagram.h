#ifndef DIAGRAM_H
#define DIAGRAM_H

#include <QFrame>
#include <QLabel>
#include <QPushButton>
#include <QProgressBar>
#include <QGraphicsView>
#include <QGraphicsScene>

#include <QtNetwork>


// Отрисовка диаграмм тока и напряжения электрофильтра
class Diagram
{

public:
    Diagram(QFrame* frame);
    ~Diagram();

    void refresh(const QNetworkDatagram & datagram);
    void axisValues();
    void grid();
    void legend();

private:
    QGraphicsView* graphicsView;
    QGraphicsScene* graphicsScene;

    const int gsize = 500;          // размеры области диаграмм

    const int gleft = 5;            // отступы диаграмм
    const int gtop = 4;

    const int gridSpacing = 20;     // Сетка

    const int ytop = 0;             // координаты графика
    const int ybot = 440;
    const int xleft = 0;
    const int xright = 420;


    QPen pen;
};

#endif // DIAGRAM_H
