#ifndef AUDIOPLAYER_H
#define AUDIOPLAYER_H

#include <QObject>
#include <QAudioOutput>
#include <QIODevice>
#include <QAudioFormat>

class AudioPlayer : public QObject
{
    Q_OBJECT

public:
    AudioPlayer(QObject *parent = 0);
    AudioPlayer(QAudioFormat format, QObject *parent = 0);
    int play(QByteArray *data);
    ~AudioPlayer();

private:
    void createAudioOutput();

private:
    QIODevice *device;
    QAudioOutput *ao = 0;
    QAudioFormat af;
    QAudioDeviceInfo adi;
    bool created = 0;
};

#endif // AUDIOPLAYER_H
