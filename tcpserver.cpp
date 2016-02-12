#include "tcpserver.h"
#include <QtNetwork>
#include "dserver.h"


TCPServer::TCPServer(QObject *parent) : QTcpServer(parent), pClientSocket (NULL)
{
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, 2323))
    {
        qDebug("Could not listen on port.");
        qDebug() << "Unable to start the server:" << m_ptcpServer->errorString();

        m_ptcpServer->close();
        return;
    }

    CreatorConnections();
}

TCPServer::~TCPServer()
{

}

void TCPServer::CreatorConnections()
{
    qDebug() << "CreatorConnections ...";

    // for Socket
    connect(m_ptcpServer, SIGNAL(newConnection()), this, SLOT(slotNewConnection()));

    pClientSocket = new QTcpSocket(this);
}

void TCPServer::slotNewConnection()
{
    pClientSocket = m_ptcpServer->nextPendingConnection();
    qDebug() << "New client from:" << pClientSocket->peerAddress().toString();
    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()) );

}

void TCPServer::slotReadClient()
{
    //qDebug() << "TSPServer::slotReadClient()";

    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_4);
    for (;;)
    {
        if (!m_nNextBlockSizeSt)
        {
            if (pClientSocket->bytesAvailable() < sizeof(quint8))
            {
                break;
            }
            in >> m_nNextBlockSizeSt;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSizeSt)
        {
            break;
        }

        quint8 cmd;
        in >> cmd;

        m_nNextBlockSizeSt = 0;
        qDebug() << "Server Received:" << cmd;


        execCommand( cmd );


    }

}

void TCPServer::sendToClient( QByteArray arrData )
{
    QThread *tcpsThread = this->thread();
    qDebug() << "TCPServer::sendToClient( QByteArray arrData )";
    qDebug() << "TCPServer | thread" << tcpsThread;


    if (pClientSocket != NULL)
    {
        qDebug() << "TCPServer |    pClientSocket->state() =" << pClientSocket->state();

        if ( pClientSocket->state() == QAbstractSocket::ConnectedState)
        {
            quint64 sizeBlock = pClientSocket->write( arrData );
            qDebug() << "Written to socket" << sizeBlock << "bytes.";
        }
    }
    else
        qDebug() << "pClientSocket != NULL";
}


