#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QAudioFormat>
#include <QAudioRecorder>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->label->setVisible(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonConnect_clicked()
{

    player = new AudioPlayer();
    if(tcpsocket != 0){
        delete tcpsocket;
    }
    tcpsocket = new TCPSocket(QHostAddress(ui->lineEdit->text()), 55025);
    udpsocket = new UDPSocket(QHostAddress(ui->lineEdit->text()), 1234);
    tcpsocket->Connect();
//        qDebug() << "Connected";
//        connect(tcpsocket, SIGNAL(formatReady(QAudioFormat&)), this, SLOT(createPlayer(QAudioFormat&)));
//        qDebug() << "signal connected";

    connect(udpsocket->socket, SIGNAL(readyRead()), this, SLOT(incomingData()));
    //ui->pushButtonConnect->setVisible(false);
   // ui->label->setVisible(true);
}

void MainWindow::incomingData()
{
    QByteArray data = QByteArray(15360, 0);
    data = udpsocket->getData();
    if(data != 0)
        player->play(&data);
}

void MainWindow::createPlayer(QAudioFormat &format)
{
    qDebug() << format;
    //player = new AudioPlayer(format, this);
}

void MainWindow::on_pushButtonBack_clicked()
{
    if(tcpsocket->isConnected()){
        QByteArray data;
        data.append("1");
        tcpsocket->SendPackage(&data);
    } else {
        qDebug() << "No";
    }
}

void MainWindow::on_pushButtonNext_clicked()
{
    if(tcpsocket->isConnected()){
        QByteArray data;
        data.append("2");
        tcpsocket->SendPackage(&data);
    } else {
        qDebug() << "No";
    }
}

void MainWindow::on_pushButtonPause_clicked()
{
    if(tcpsocket->isConnected()){
        QByteArray data;
        data.append("3");
        tcpsocket->SendPackage(&data);
    } else {
        qDebug() << "No";
    }
}

void MainWindow::on_pushButtonMute_clicked()
{
    if(tcpsocket->isConnected()){
        QByteArray data;
        data.append("4");
        tcpsocket->SendPackage(&data);
    } else {
        qDebug () << "No";
    }
}

void MainWindow::on_pushButtonVolumeUp_clicked()
{
    if(tcpsocket->isConnected()){
        QByteArray data;
        data.append("5");
        tcpsocket->SendPackage(&data);
    } else {
        qDebug () << "No";
    }
}

void MainWindow::on_pushButtonVolumeDown_clicked()
{
    if(tcpsocket->isConnected()){
        QByteArray data;
        data.append("6");
        tcpsocket->SendPackage(&data);
    } else {
        qDebug () << "No";
    }
}

void MainWindow::on_pushButtonDisconnecct_clicked()
{
    if(tcpsocket != 0){
        tcpsocket->disconnect();
        delete tcpsocket;
        delete player;
        delete udpsocket;
    }
}
