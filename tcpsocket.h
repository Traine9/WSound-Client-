#ifndef TCPSOCKET_H
#define TCPSOCKET_H
#include <QTcpSocket>
#include <QObject>
#include <QHostAddress>
#include <QAudioFormat>

struct Settings{
    unsigned int channels;
    unsigned int bufferSize;
};

class TCPSocket : public QObject
{
    Q_OBJECT

public:
    TCPSocket(QHostAddress addr, uint16_t port, QObject *parent = 0);
    ~TCPSocket();
    int Connect();
    int SendPackage(QByteArray *package);
    bool isConnected();
    QTcpSocket* getSocket();
    QAudioFormat *getFormat();

private:
    QTcpSocket *socket;
    QHostAddress addr;
    uint16_t port;
    QAudioFormat *format;

signals:
    void formatReady(QAudioFormat&);

private slots:
    void Connected();
    void read();
};

#endif // TCPSOCKET_H
