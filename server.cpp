#include "server.h"
#include <QtNetwork>


Server::Server(int nPort, QObject *parent) : QTcpServer(parent), sizeArray(100)
{
    m_ptcpServer = new QTcpServer(this);
    if (!m_ptcpServer->listen(QHostAddress::Any, nPort))
    {
        qFatal("Could not listen on port.");
        m_ptcpServer->close();
        return;
    }

    CreatorConnections();

    timer.setInterval( 2000 );
    timer.start();
}

void Server::slotNewConnection()
{
    QTcpSocket* pClientSocket = m_ptcpServer->nextPendingConnection();
    qDebug() << "New client from:" << pClientSocket->peerAddress().toString();
    connect(pClientSocket, SIGNAL(disconnected()), pClientSocket, SLOT(deleteLater()));
    connect(pClientSocket, SIGNAL(readyRead()), this, SLOT(slotReadClient()) );

    //sendToClient(pClientSocket, "Server Response: Connected!");
}

void Server::slotReadClient()
{
    QTcpSocket* pClientSocket = (QTcpSocket*)sender();
    QDataStream in(pClientSocket);
    in.setVersion(QDataStream::Qt_4_5);
    for (;;) {
        if (!m_nNextBlockSize) {
            if (pClientSocket->bytesAvailable() < sizeof(quint16)) {
                break;
            }
            in >> m_nNextBlockSize;
        }

        if (pClientSocket->bytesAvailable() < m_nNextBlockSize) {
            break;
        }

        QTime   time;
        QString str;
        in >> time >> str;

        QString strMessage =
            time.toString() + " " + "Client has sent - " + str;

        qDebug() << strMessage;

        //m_ptxt->append(strMessage);

        m_nNextBlockSize = 0;

        //sendToClient(pClientSocket, "Server Response: Received \"" + str + "\"" );
    }
}

void Server::sendToClient(QTcpSocket* pSocket, QVector<double> arrX)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    //QDataStream out(pSocket);
    out.setVersion(QDataStream::Qt_4_5);

    /*
    out << quint16(0) << QTime::currentTime() << str;
    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));
    pSocket->write(arrBlock);
    qDebug() << "Send = " << arrBlock << "\n";
    */

}

void Server::DataGeneration( QVector<InfoChannel> *arrData )
{
    InfoChannel inf_chan;

    for (int i = 0; i < sizeArray; i++)
    {
        inf_chan.nm_channel = i;
        inf_chan.freq = std::rand() % 70;

        arrData->append( inf_chan );

    }
}

void Server::timerSlot()
{
    QVector<InfoChannel> arrData;
    DataGeneration( &arrData );

    if (1)
    {
        qDebug() << "our data (number of words = " << arrData.size() << ")"  ;
        const int limPrint = 3;
        for (int i = 0; i < arrData.size(); i++)
        {
            if ( i < limPrint)
            {
                qDebug() << i << ". " << arrData.at(i).nm_channel << " " << arrData.at(i).freq;
            }
        }
    }

    //sendToClient(pClientSocket, arrX);

}

void Server::CreatorConnections()
{
    connect(m_ptcpServer, SIGNAL(newConnection()),this,SLOT(slotNewConnection()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
}


/*
QDataStream & operator << ( QDataStream & out, const S & s )
{
    out<<s.count;
    for(size_t i = 0; i<s.count;++i)
    {
        out<<s.arrX[i];
    }
    out<<s.count;
}
/*/
