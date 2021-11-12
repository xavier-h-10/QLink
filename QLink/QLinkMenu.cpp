#include "QLinkMenu.h"
#include "ui_QLinkMenu.h"
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QMessageBox>
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>

QLinkMenu::QLinkMenu(QWidget *parent)
    : QWidget(parent),
      ui(new Ui::QLinkMenu)
{
    ui->setupUi(this);
    setWindowTitle(tr("连连看"));


}

QLinkMenu::~QLinkMenu()
{
    delete ui;
}



//void QLinkMenu::loadFile(const QString &tring,const QString &str)
//{
//    QString fileName=dir_string+"/"+str;
//    QFile file(fileName);
//    if (!file.open(QFile::ReadOnly | QFile::Text))
//    {
//        statusBar()->showMessage(tr("Failed to load file")+file.fileName(),2000);
//        return;
//    }

//    QTextStream stream(&file);
//    QStringList headers = stream.readLine().split(',');
//    int now=0;
//    while(!stream.atEnd())
//    {
//        QString tmpLine=stream.readLine();
//        if(!tmpLine.isEmpty())
//        {
//            QStringList p=tmpLine.split(',');
//            QVector<double> q;
//            q.clear();
//            for(int i=0;i<7;i++)
//            {
//                q.append(p.value(i+1).toDouble());
//            }
//            mapData.append(q);
//            now++;
//        }
//    }
//}


//void QLinkMenu::on_openAction_triggered()
//{
//    QString fd = QFileDialog::getOpenFileName(this, tr("Open File"),"/",tr("Json (*.json);;Plain files(*.*)"));
//    qDebug()<<fd;
//    if (fd == "") {
//        statusBar()->showMessage(tr("Please reopen a file."), 2000);
//        return;

//    }
//    QFile aFile(fd);
//    if (!aFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
//        QMessageBox::information(this, tr("Warning"), tr("This file can not be read."));
//        return;
//    }
//    QString value=aFile.readAll();
//    aFile.close();

//    QJsonParseError parseJsonErr;
//    QJsonDocument document=QJsonDocument::fromJson(value.toUtf8(),&parseJsonErr);
//    if(parseJsonErr.error!=QJsonParseError::NoError) {
//        QMessageBox::information(this,tr("Warning"),tr("JSON file has wrong format."));
//        return;
//    }

//    statusBar()->showMessage(tr("Loaded %1").arg(fd), 2000);
//    QJsonObject jsonObject=document.object();

//}


void QLinkMenu::on_startSingleGameButton_clicked()
{
    emit startGame(Constant::MODE::SINGLE_MODE);
}


void QLinkMenu::on_startDoubleGameButton_clicked()
{
    emit startGame(Constant::MODE::DOUBLE_MODE);
}


void QLinkMenu::on_loadGameButton_clicked()
{

}


void QLinkMenu::on_quitGameButton_clicked()
{
    emit quitGame();
}

