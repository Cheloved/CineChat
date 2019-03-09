#include "customsocket.h"

//customSocket::~customSocket(){}

customSocket::customSocket(type socketType, const QString& host,
                           quint16 port, QWidget* parent) : QWidget (parent), nextBlockSize(0)
{
    // Define socket and connect it
    socket = new QTcpSocket(this);
    socket->connectToHost(host, port);

    // Make connection between socket signals and this->slots
    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));

    /*connect(socket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,   SLOT(slotError(QAbstractSocket::SocketError)));*/

    // Apply work mode
    this->workMode = socketType;
}

void customSocket::slotReadyRead()
{
    QDataStream in(socket);
        in.setVersion(QDataStream::Qt_4_2);
        for (;;) {
            if (!nextBlockSize) {
                if (socket->bytesAvailable() < sizeof(quint16)) {
                    break;
                }
                in >> nextBlockSize;
            }

            if (socket->bytesAvailable() < nextBlockSize) {
                break;
            }
            QTime time;
            QString str;
            in >> time >> str;

            nextBlockSize = 0;
        }
}
