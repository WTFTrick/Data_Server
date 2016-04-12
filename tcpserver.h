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

    enum TYPE_DATA{DATA_RAW, DATA_HIST, CFG_MUTOMO, CMD};


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
            void disconnectedClient ();


signals:
            void execCommand (quint8 cmd);
};

#endif // TSPSERVER_H
