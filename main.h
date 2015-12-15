#ifndef MAIN
#define MAIN

class QTcpServer;
class QTcpSocket;

class Server
{
Q_OBJECT
private:
    QTcpServer* m_ptcpServer;
    quint16     m_nNextBlockSize;

private:
    void sendToClient(QTcpSocket* pSocket, const QString& str);

public:
    Server(int nPort);

public slots:
    virtual void slotNewConnection();
            void slotReadClient   ();
};






#endif // MAIN

