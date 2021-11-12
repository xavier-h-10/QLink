#include "QLinkWindow.h"
#include "ui_QLinkWindow.h"
#include "Constant.h"
#include <QPalette>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QLCDNumber>
#include <QMainWindow>

QLinkWindow::QLinkWindow(QWidget *parent) :
    QMainWindow(parent)
    , ui(new Ui::QLinkWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("连连看"));
    ui->heightBox->setMinimum(Constant::mapMin);
    ui->heightBox->setMaximum(Constant::mapMax);
    ui->weightBox->setMinimum(Constant::mapMin);
    ui->weightBox->setMaximum(Constant::mapMax);
    mode=Constant::MODE::SINGLE_MODE;

    timer=new QTimer(this);
    player1=new QPlayer(1);
    player2=new QPlayer(2);

    connect(timer,SIGNAL(timeout()),this,SLOT(updateTime()));

    this->started=false;
    this->paused=false;
}

QLinkWindow::~QLinkWindow()
{
    delete ui;
}

void QLinkWindow::init(Constant::MODE mode) {
    this->mode=mode;

    QPalette pe;
    pe.setColor(QPalette::WindowText,Qt::red);
    ui->resultLabel->setText("");
    ui->resultLabel->setPalette(pe);
    ui->singleScore->setPalette(pe);
    ui->doubleScore->setPalette(pe);
    ui->clock->display("00:00");
    ui->clock->setSegmentStyle(QLCDNumber::Flat);
    ui->weightBox->setValue(Constant::mapDefault);
    ui->heightBox->setValue(Constant::mapDefault);

    if(mode==Constant::MODE::SINGLE_MODE) {
        ui->modeTitle->setText("单人模式");
        ui->singleLabel->setText("玩家分数:");
        ui->singleScore->setText("0");
        ui->doubleLabel->setText("");
        ui->doubleScore->setText("");
    }
    else {
        ui->modeTitle->setText("双人模式");
        ui->singleLabel->setText("玩家一分数:");
        ui->singleScore->setText("0");
        ui->doubleLabel->setText("玩家二分数:");
        ui->doubleScore->setText("0");
    }
    ui->pauseButton->setText("暂停 (Pause)");

    this->started=false;
    this->paused=false;
    this->remainTime=Constant::countdown;
}

void QLinkWindow::updateTime() {
    qDebug()<<"QLinkWindow::updateTime called start="<<this->started;
    if(!this->started) {
        timer->stop();
    }
    remainTime--;
    const QString &nowTime=convertTime(remainTime);
    qDebug()<<"nowTime="<<nowTime;
    ui->clock->display(nowTime);

    if(remainTime<=0) {
        timer->stop();
        QMessageBox::information(this,tr("游戏提示"),tr("倒计时完成，游戏结束!"));
        ui->pauseButton->setText("暂停 (Pause)");
        this->started=false;
    }
    qDebug()<<"QLinkWindow::updateTime ended";
}

void QLinkWindow::on_startButton_clicked()
{
    if(this->started) {
        QMessageBox::information(this,tr("游戏提示"),tr("游戏已经开始!"));
        return;
    }
    qDebug()<<"QLinkWindow::startButton: start init";
    init(mode);
    qDebug()<<"QLinkWindow::startButton: end init";
    updateTime();
    this->started=true;
    timer->start(1000);
}


void QLinkWindow::on_pauseButton_clicked()
{
    if(!this->started) {
        QMessageBox::information(this,tr("游戏提示"),tr("游戏尚未开始!"));
    }
    if(this->paused) {
       timer->start(1000);
       ui->pauseButton->setText("暂停 (Pause)");
    }
    else {
        timer->stop();
        ui->pauseButton->setText("继续 (Continue)");
    }
    this->paused=!this->paused;
}


void QLinkWindow::on_saveButton_clicked()
{
    if(!this->started) {
        QMessageBox::information(this,tr("游戏提示"),tr("游戏尚未开始，无法存档!"));
        return;
    }
    if(!this->paused) {
        QMessageBox::information(this,tr("游戏提示"),tr("请先暂停游戏，再保存存档!"));
        return;
    }
}


void QLinkWindow::on_loadButton_clicked()
{
    if(this->started && !this->paused) {
        QMessageBox::information(this,tr("游戏提示"),tr("请先暂停游戏，再载入存档!"));
        return;
    }
}


void QLinkWindow::on_returnButton_clicked()
{
    timer->stop();
    emit stopGame();
}

void QLinkWindow::on_quitButton_clicked()
{
    timer->stop();
    emit quitGame();
}


QString QLinkWindow::convertTime(int time) {
    QString ans="";
    int min=time/60;
    int sec=time%60;
    ans=ans+"0"+QString::number(min)+":";
    if(sec<10) ans+="0";
    ans+=QString::number(sec);
    return ans;
}
