#include "udpsocket.h"
#include <QNetworkInterface>
#include <QHostInfo>

UDPSocket::UDPSocket(QHostAddress addr, uint16_t port, QObject *parent)
    : QObject(parent)
{
    this->addr = addr;
    this->port = port;
    socket = new QUdpSocket;
    socket->bind(port);
    connect(socket, SIGNAL(readyRead()), this, SLOT(readyRead()));
}

UDPSocket::~UDPSocket()
{
    socket->close();
}

int UDPSocket::SendData(QByteArray *data)
{
    return socket->writeDatagram(*data, addr, port);
}

QByteArray UDPSocket::getData()
{
    if(arr.size() >= SIZE){
        QByteArray data = arr.front();
        arr.pop();
        return data;
    }
    else
        return 0;
}

void UDPSocket::readyRead()
{
    buffer.resize(socket->pendingDatagramSize());
    socket->readDatagram(buffer.data(), buffer.size());
    arr.push(buffer);
}
