#include "dserver.h"

DServer::DServer(QObject *parent)
{
    qDebug() << "Thread dserver constructor:" << this->currentThreadId();

}

void DServer::run()
{
    qDebug() << "Thread dserver:" << this->currentThreadId();

    dataGenerator = new DGenerator( 2300 );

    QTimer timerDataGeneration;
    timerDataGeneration.start( 1000 );
    connect(&timerDataGeneration, &QTimer::timeout, this, &DServer::sendDataToServer, Qt::DirectConnection);
    exec();
}

void DServer::sendDataToServer()
{
    qDebug() << "Thread dserver::sendDataToServer()" << this->currentThreadId();

    // generate data
    //QVector<InfoChannel> arrHits;
    QVector<quint32> arrHits;
    dataGenerator->getData( &arrHits );

    // data packaging to QByteArray
    QByteArray pkgData;
    QDataStream out(&pkgData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    out << quint32(0);
    foreach(quint32 crChannel, arrHits)
        out << crChannel;

    out.device()->seek(0);
    out << quint32(pkgData.size() - sizeof(quint32));

    // data sending to server
    emit sendData( pkgData );
}

void DServer::execCommand(quint8 cmd)
{
    if (cmd == 1)
    {
        qDebug() << "Server turn on";
        this->start();

        return;

    }

    if (cmd == 0)
    {
        qDebug() << "Server turn off";
        this->quit();
        //this->exit(); //another way to stop QThread
        return;
    }

}

