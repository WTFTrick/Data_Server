#include <QCoreApplication>

#include "server.h"

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
    dserv.start();


    /*
    Server server(2323);
    qDebug() << "Listening.";
    */

    return a.exec();
}

