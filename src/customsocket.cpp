#include "customsocket.h"


/* Functions of Main socket class
 * are discribed here
*/

customSocket::customSocket(type socketType, const QString& host, quint16 port, QWidget* parent)
{
    // Apply work mode
    this->workMode = socketType;

    if ( socketType == ClientMode )
        this->client = new Client(host, port, parent);
}

customSocket::~customSocket()
{
    delete client;
    delete server;
}

// Client functions below
Client::Client(const QString& host, quint16 port, QWidget* parent) : QWidget (parent), nextBlockSize(0)
{
    this->socket = new QTcpSocket();
    socket->connectToHost(host, port);

    connect(socket, SIGNAL(readyRead()), SLOT(slotReadyRead()));

    connect(socket, SIGNAL(connected()), SLOT(slotConnected()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)),
            this,   SLOT(slotError(QAbstractSocket::SocketError)));
}

Client::~Client()
{ delete socket; }

void Client::slotReadyRead()
{
    QDataStream in(socket);
    in.setVersion(QDataStream::Qt_4_2);
    for (;;)
    {
        if (!nextBlockSize)
        {
            if (socket->bytesAvailable() < sizeof(quint16))
            {
                break;
            }
            in >> nextBlockSize;
        }

        if (socket->bytesAvailable() < nextBlockSize)
        {
            break;
        }
        QTime time;
        QString str;
        in >> time >> str;

        data.append(time.toString() + " " + str);

        nextBlockSize = 0;
    }
}

void Client::slotError(QAbstractSocket::SocketError err)
{
    QString strError =
    "Error: " + (err == QAbstractSocket::HostNotFoundError ?
    "The host was not found." :
    err == QAbstractSocket::RemoteHostClosedError ?
    "The remote host is closed." :
     err == QAbstractSocket::ConnectionRefusedError ?
     "The connection was refused." :
     QString(socket->errorString())
     );
     data.append(strError);
}

void Client::slotSendToServer(QString data)
{
    QByteArray  arrBlock;
    QDataStream out(&arrBlock, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_2);
    out << quint16(0) << QTime::currentTime() << data;

    out.device()->seek(0);
    out << quint16(arrBlock.size() - sizeof(quint16));

    socket->write(arrBlock);
}

void Client::slotConnected()
{
    qDebug() << "Connection has been established";
}
