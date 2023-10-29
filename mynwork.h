#ifndef MYNWORK_H
#define MYNWORK_H

#include <QFrame>
#include <QObject>

#include <QtNetwork>


#include "diagram.h"

class Mynwork: public QObject
{
        Q_OBJECT;

public:
    QUdpSocket * udpSocket;
    QNetworkDatagram  datagram;
    bool diagramUpdatable = true;

    Diagram* diagram;

    //QFrame* frame;

        void initSocket(QFrame* frame)
        {
            udpSocket = new QUdpSocket();
            udpSocket->bind(QHostAddress::LocalHost, 10002);
          //  connect(udpSocket, SIGANL(readPendingDatagrams()), this, SLOT(readPendingDatagrams()));

            QAbstractSocket::connect(udpSocket,&QUdpSocket::readyRead,this,&Mynwork::readPendingDatagrams);


            diagram = new Diagram(frame);




        }

        void processTheDatagram(QNetworkDatagram & datagram)
        {
            if (diagramUpdatable)
                diagram->refresh(datagram);

            // qDebug() << datagram.data();

        }

        void readPendingDatagrams()
        {
            while (udpSocket->hasPendingDatagrams()) {
                datagram = udpSocket->receiveDatagram();

                processTheDatagram(datagram);
            }
        }



};

#endif // MYNWORK_H
