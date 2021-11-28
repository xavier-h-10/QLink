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
    emit loadGame();
}


void QLinkMenu::on_quitGameButton_clicked()
{
    emit quitGame();
}

