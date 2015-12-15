#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QSet>
#include <QTimer>

class QTcpServer;
class QTcpSocket;

class Server : public QTcpServer
{
        Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    quint16     m_nNextBlockSize;

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);
    void CreatorConnections();
    QTimer timer;
public:
    Server(int nPort, QObject *parent=0);

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
private slots:
            void TimerSlot();
};

#endif // SERVER_H
