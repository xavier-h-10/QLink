//
// Created by 黄喆敏 on 2021/11/1.
//

#include "QLinkBox.h"
#include "Constant.h"
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <QPalette>
#include <QDebug>

QLinkBox::QLinkBox(int h, int w, int type) : h(h), w(w), type(type)
{
    label = new QLabel();
    pixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(pixmap);
    label->setAlignment(Qt::AlignCenter);
    label->setAutoFillBackground(true);
    label->setStyleSheet("border: 0px; background-color:rgb(255,250,205);");
}


QLinkBox::QLinkBox(int h, int w, int type, QImage *icon) : h(h), w(w), type(type)
{
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(255, 250, 205)); // color: lemonchiffon

    label = new QLabel();
    pixmap = QPixmap::fromImage(*icon);
    pixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(pixmap);
    label->setAlignment(Qt::AlignCenter);
    label->setAutoFillBackground(true);
    label->setPalette(palette);
}

QLinkBox::~QLinkBox()
{
    delete label;
    label = nullptr;
}

QLabel *QLinkBox::getLabel()
{
    return label;
}

void QLinkBox::select(int num)
{
    qDebug() << "QLinkBox::select called";
    if (num == 0) {
        label->setStyleSheet("border: 3px solid red; background-color:rgb(255,250,205);");
    } else {
        label->setStyleSheet("border: 3px solid blue; background-color:rgb(255,250,205);");
    }
}

void QLinkBox::deSelect()
{
    label->setStyleSheet("border: 0px; background-color:rgb(255,250,205);");
}

void QLinkBox::hint()
{
    label->setStyleSheet("border: 3px solid green; background-color:rgb(255,250,205);");
}

void QLinkBox::clear()
{
    label->clear();

    pixmap = QPixmap(50, 50);
    pixmap.fill(QColor(236, 236, 236));
    label->setPixmap(pixmap);

    label->setStyleSheet("border: 0px;");
}

void QLinkBox::changeType(QImage *icon)
{
    QPalette palette;
    palette.setColor(QPalette::Window, QColor(255, 250, 205));

    pixmap = QPixmap::fromImage(*icon);
    pixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    label->setPixmap(pixmap);
    label->setAlignment(Qt::AlignCenter);
    label->setAutoFillBackground(true);
    label->setPalette(palette);
}
