#include "dserver.h"


DServer::DServer(QObject *parent)
{
    qDebug() << "Thread dserver constructor:" << this->currentThreadId();

}

void DServer::run()
{
    qDebug() << "Thread dserver:" << this->currentThreadId();


    dataGenerator = new DGenerator( 1000 );

    QTimer timerDataGeneration;
    timerDataGeneration.start( 1000 );
    connect(&timerDataGeneration, &QTimer::timeout, this, &DServer::sendDataToServer, Qt::DirectConnection);



    exec();
}

void DServer::sendDataToServer()
{
    qDebug() << "Thread dserver::sendDataToServer()" << this->currentThreadId();


    // generate data
    QVector<InfoChannel> arrHits;
    dataGenerator->getData( &arrHits );

    // data packaging to QByteArray
    QByteArray pkgData;
    QDataStream out(&pkgData, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_5_4);

    out << quint32(0);
    foreach(InfoChannel ich, arrHits)
        out << ich.nm_channel << ich.freq;

    out.device()->seek(0);
    out << quint32(pkgData.size() - sizeof(quint32));


    // data sending to server
    emit sendData( pkgData );
}

