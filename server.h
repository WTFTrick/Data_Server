#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>
#include <QTimer>


#include "ichannel.h"

/*
struct InfoChannel
{
    quint16 nm_channel;
    quint16 freq;
};
*/

class Server : public QTcpServer
{
        Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    quint16     m_nNextBlockSize;

private:
    void sendToClient(QTcpSocket* pSocket, QVector<InfoChannel> *arrData);
    void CreatorConnections();
    void DataGeneration(QVector<InfoChannel> *arrData);
    QTimer timer;
    int sizeArray;
    int CountOfBins;
    QTcpSocket* pClientSocket;
public:
    Server(int nPort, QObject *parent=0);
    ~Server();

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();

private slots:
            void timerSlot();
};

#endif // SERVER_H
