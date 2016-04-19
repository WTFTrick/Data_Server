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

    enum TYPE_DATA{DATA_RAW, DATA_HIST, DATA_CONFIG_MUTOMO, DATA_CMD};

private:
    QTcpServer* m_ptcpServer;
    QTcpSocket* pClientSocket;

    void DataFromClient(TYPE_DATA t_data, QByteArray data);
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
