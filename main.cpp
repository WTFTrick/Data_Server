#include <QCoreApplication>

#include "dserver.h"
#include "tcpserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QThread *appThread = a.thread();
    qDebug() << "Application thread ID" << appThread->currentThreadId();

    TCPServer TcpServer;
    DServer dserv;
    QObject::connect(&dserv, &DServer::sendData, &TcpServer, &TCPServer::sendToClient, Qt::QueuedConnection);
    QObject::connect(&TcpServer, &TCPServer::execCommand, &dserv, &DServer::execCommand, Qt::QueuedConnection);



    return a.exec();
}

