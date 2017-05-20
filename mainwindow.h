#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QDebug>
#include <QMainWindow>
#include "tcpsocket.h"
#include "udpsocket.h"
#include "audioplayer.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    TCPSocket *tcpsocket = 0;
    UDPSocket *udpsocket = 0;
    AudioPlayer *player = 0;

    //UDPSocket *udpsocket;

private slots:
    void on_pushButtonConnect_clicked();
    void incomingData();
    void createPlayer(QAudioFormat &format);
    void on_pushButtonBack_clicked();
    void on_pushButtonNext_clicked();
    void on_pushButtonPause_clicked();
    void on_pushButtonMute_clicked();

    void on_pushButtonVolumeUp_clicked();
    void on_pushButtonVolumeDown_clicked();
    void on_pushButtonDisconnecct_clicked();
};

#endif // MAINWINDOW_H
