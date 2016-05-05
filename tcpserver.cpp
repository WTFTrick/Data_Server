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

void TCPServer::ClearJSONFile()
{
    QFile file("configuration.json");
    if (file.open(QIODevice::WriteOnly | QIODevice::Truncate))
    {
        file.write("");
    }
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
    connect(pClientSocket, SIGNAL( disconnected( ) ), SLOT( disconnectedClient( ) ) );
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()) );
}

void TCPServer::slotReadClient()
{
    //qDebug() << "TSPServer::slotReadClient()";

    quint64     m_nNextBlockSize(0);

    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_5_6);
    for (;;)
    {
        if (!m_nNextBlockSize)
        {
            if (pClientSocket->bytesAvailable() < sizeof(quint64))
            {
                break;
            }
            in >> m_nNextBlockSize;
        }

        //qDebug() << "Block of data size: " << m_nNextBlockSize;

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize)
        {
            break;
        }

        quint32   d_type(0);
        QByteArray data;
        data.resize(4);

        in >> d_type;
        in >> data;

        TYPE_DATA dt = TYPE_DATA( d_type );

        /*
        qDebug() << "Server received type (quint32):" << d_type;
        qDebug() << "Server received type:" << dt;
        qDebug() << "Server received data (d_data):" << d_data;
        qDebug() << "Size of data array:" << data.size();
        qDebug() << "Client sent data in bytes:" << data;
        qDebug() << "Client sent data:" << data.toInt();
        */

        DataFromClient(dt, data);

        m_nNextBlockSize = 0;
    }

}

void TCPServer::DataFromClient(TCPServer::TYPE_DATA t_data, QByteArray data)
{
    if ( t_data == DATA_CMD )
        execCommand( data.toUInt() );

    if ( t_data == DATA_CONFIG_MUTOMO)
    {
        ClearJSONFile();

        QFile jsnFile("configuration.json");
        jsnFile.open(QFile::Append);
        QTextStream outJson(&jsnFile);
        outJson << data;
        jsnFile.close();
    }

    if ( t_data == DATA_HIST )
    {
        // Smth
    }

    if ( t_data == DATA_RAW )
    {
        // Smth
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

void TCPServer::disconnectedClient()
{
    qDebug() << "Client was disconnected!";
    execCommand(0); //Stop the server
}


