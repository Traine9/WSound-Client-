#include "audioplayer.h"
#include <QDebug>
#include <QAudioRecorder>

AudioPlayer::AudioPlayer(QAudioFormat format, QObject *parent)
    : QObject(parent)
{

    adi = QAudioDeviceInfo::defaultOutputDevice();
    QAudioRecorder a;
    af.setChannelCount(format.channelCount());
    af.setSampleRate(format.sampleRate());
    af.setSampleSize(format.sampleSize());
    af.setCodec(format.codec());
    af.setByteOrder(format.byteOrder());
    af.setSampleType(format.sampleType());

    QAudioDeviceInfo info(adi);
    if (!adi.isFormatSupported(af)){
        af = adi.nearestFormat(af);
    }
    createAudioOutput();
}

AudioPlayer::AudioPlayer(QObject *parent)
    : QObject(parent)
{

    adi = QAudioDeviceInfo::defaultOutputDevice();
    QAudioRecorder a;
    af.setChannelCount(2);
    af.setSampleRate(48000);
    af.setSampleSize(16);
    af.setCodec("audio/pcm");
    af.setByteOrder(QAudioFormat::LittleEndian);
    af.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(adi);
    if (!adi.isFormatSupported(af)){
        af = adi.nearestFormat(af);
    }
    createAudioOutput();
}

int AudioPlayer::play(QByteArray *data)
{
    if(created){
        device->write(*data);
    }

    return 0;
}

AudioPlayer::~AudioPlayer()
{
    delete device;
    delete ao;
    created = 0;
}

void AudioPlayer::createAudioOutput()
{
    if(ao != 0)
        delete ao;

    ao = 0;
    ao = new QAudioOutput(adi, af, this);
    device = ao->start();
    created = 1;
}
