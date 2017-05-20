#ifndef UDPSOCKET_H
#define UDPSOCKET_H
#include <QUdpSocket>
#include <QObject>
#include <QHostAddress>
#include <queue>

class UDPSocket : public QObject
{
    Q_OBJECT

public:
    UDPSocket(QHostAddress addr, uint16_t port, QObject *parent = 0);
    ~UDPSocket();
    int SendData(QByteArray *data);
    QByteArray getData();
    QUdpSocket *socket;

private slots:
    void readyRead();

private:
    QHostAddress addr;
    uint16_t port;
    QByteArray buffer;
    std::queue<QByteArray> arr;
    int SIZE = 5;

};

#endif // UDPSOCKET_H
