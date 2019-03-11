#ifndef CUSTOMSOCKET_H
#define CUSTOMSOCKET_H

#include "custominclude.h"

class Client : public QWidget
{
Q_OBJECT
public:
    explicit Client(const QString& host, quint16 port, QWidget* parent = nullptr);
    void GetData();
    ~Client();
private:
    QTcpSocket* socket;
    quint16 nextBlockSize;

    QString data = "";

private slots:
    void slotReadyRead   (                            );
    void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(        QString data        );
    void slotConnected   (                            );
};

class Server : public QWidget
{
Q_OBJECT
public:
    explicit Server(int port, QWidget* parent = nullptr);

public slots:
    virtual void slotNewConnection();
    void slotReadClient();

private:
    QTcpServer* server;
    quint16 nextBlockSize;
    QString data = "";

    void sendToClient(QTcpSocket* pSocket, const QString& str);
};

class customSocket
{

public:
    enum type {ClientMode, ServerMode};
    type workMode;

    explicit customSocket(type socketType, const QString& host, quint16 port, QWidget* parent = nullptr);
    ~customSocket();

private:
    Client* client;
    Server* server;
    QWidget* pnt;
};

#endif // CUSTOMSOCKET_H
