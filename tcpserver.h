#ifndef TSPSERVER_H
#define TSPSERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>

#include "dgenerator.h"

class TCPServer : public QTcpServer
{
     Q_OBJECT


public:
    TCPServer( QObject *parent = 0 );
    ~TCPServer();


private:
    QTcpServer* m_ptcpServer;
    QTcpSocket* pClientSocket;
    quint16     m_nNextBlockSize;
    quint8      m_nNextBlockSizeSt;

    void CreatorConnections();


public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
            void sendToClient(QByteArray arrData);
};

#endif // TSPSERVER_H
