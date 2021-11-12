#include "QWindowController.h"
#include <QApplication>
#include <QDebug>
#include "QLinkMenu.h"
#include "Constant.h"
#include "QLinkWindow.h"

QWindowController::QWindowController()
{
    qLinkMenu=new QLinkMenu;
    qLinkWindow=new QLinkWindow;
    connect(qLinkMenu,SIGNAL(startGame(Constant::MODE)),this,SLOT(startGame(Constant::MODE)));
    connect(qLinkMenu,SIGNAL(quitGame()),this,SLOT(quitGame()));

    connect(qLinkWindow,SIGNAL(stopGame()),this,SLOT(stopGame()));
    connect(qLinkWindow,SIGNAL(quitGame()),this,SLOT(quitGame()));
    qLinkMenu->show();
}


QWindowController::~QWindowController()
{
    delete qLinkMenu;
    qLinkMenu=nullptr;
}

void QWindowController::startGame(Constant::MODE mode) {
    qDebug()<<"QWindowController::startGame called, mode="<<mode;
    qLinkWindow->init(mode);
    qLinkMenu->hide();
    qLinkWindow->show();
}

void QWindowController::stopGame() {
    qLinkWindow->hide();
    qLinkMenu->show();
}

void QWindowController::quitGame() {
    qDebug()<<"QWindowController::quitGame called";
    qLinkWindow->hide();
    qLinkMenu->hide();
    delete qLinkWindow;
    qLinkWindow=nullptr;
    QApplication::exit();
}

