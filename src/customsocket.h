#ifndef CUSTOMSOCKET_H
#define CUSTOMSOCKET_H

#include <QObject>
#include <QWidget>
#include <QTcpSocket>
#include <QTcpServer>
#include <QTime>

class customSocket : public QWidget
{
Q_OBJECT

public:
    enum type {Client, Server};
    type workMode;

    explicit customSocket(type socketType, const QString& host, quint16 port, QWidget* parent = nullptr);
    //~customSocket();

private:
    QTcpSocket* socket;
    quint16 nextBlockSize;

private slots:
    void slotReadyRead   (                            );
    /*void slotError       (QAbstractSocket::SocketError);
    void slotSendToServer(                            );
    void slotConnected   (                            );*/
};

#endif // CUSTOMSOCKET_H
