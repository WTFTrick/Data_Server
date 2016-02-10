#ifndef DSERVER_H
#define DSERVER_H

#include <QObject>
#include <QDebug>
#include <QDataStream>
#include <QThread>
#include <QTimer>

#include "dgenerator.h"
#include "tcpserver.h"


class DServer : public QThread
{
    Q_OBJECT

public:
    DServer(QObject *parent = 0 );

    void run();

public slots:
    void sendDataToServer();

signals:
    void sendData ( QByteArray );


private:
    DGenerator *dataGenerator;


};

#endif // DSERVER_H
