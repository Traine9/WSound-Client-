#include "tcpsocket.h"

TCPSocket::TCPSocket(QHostAddress addr, uint16_t port, QObject *parent) : QObject(parent)
{
    this->port = port;
    this->addr = addr;
    socket = new QTcpSocket;
    connect(socket, SIGNAL(connected()), this, SLOT(Connected()));
    connect(socket, SIGNAL(readyRead()), this, SLOT(read()));
}

TCPSocket::~TCPSocket()
{
    socket->close();
}

int TCPSocket::Connect(){
    socket->connectToHost(addr, port);
    socket->waitForConnected(5000);
    return isConnected();
}



int TCPSocket::SendPackage(QByteArray *package){
    return socket->write(*package);
}

bool TCPSocket::isConnected()
{
    if(socket->state() == 0){
        return 0;
    } else if(socket->state() == 3){
        return 1;
    }
    return 0;
}

QTcpSocket *TCPSocket::getSocket()
{
    return socket;
}

QAudioFormat* TCPSocket::getFormat()
{
    return format;
}

void TCPSocket::Connected(){
    qDebug() << "Connected to " << addr << ':' << port;
}

void TCPSocket::read()
{
   /* QByteArray data = socket->read(sizeof(QAudioFormat));
    format = (QAudioFormat*)data.data();
    if(format != 0)
        emit formatReady(*format)*/;
}


