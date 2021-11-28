//
// Created by 黄喆敏 on 2021/11/1.
//

#include "QLinkProp.h"
#include "Constant.h"
#include <QDebug>
#include <random>
#include <QJsonObject>
#include <QJsonArray>
#include <ctime>

QLinkProp::QLinkProp(QLabel *label, int num) : label(label), num(num)
{
    posx = posy = 0.0;
    enabled = false;
    genTime = 0;
    if (num >= Constant::PropNum || num < 0) {
        num = 0;
    }
    generate();
}

//生成一个新的道具
void QLinkProp::generate()
{
    srand(time(NULL));
    type = rand() % Constant::PropNum;

    enabled = false;

    QString filename = ":/res/prop" + QString::number(type + 1) + ".png";
    image = new QImage();
    image->load(filename);
    pixmap = QPixmap::fromImage(*image);
    pixmap = pixmap.scaled(Constant::propWidth, Constant::propHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    posx = genRandom(Constant::mapMinX - 20, Constant::mapMaxX + 20, 30, Constant::windowWidth - 30);
    posy = genRandom(Constant::mapMinY - 10, Constant::mapMaxY + 10, Constant::playerMinY, Constant::playerMaxY);
    qDebug() << "QLinkProp:generate " << posx << " " << posy;
    label->setGeometry(posx, posy, 30, 30);
}


void QLinkProp::show()
{
    label->setGeometry(posx, posy, 30, 30);
    label->setPixmap(pixmap);
    label->setAlignment(Qt::AlignCenter);
    label->setAutoFillBackground(true);
    enabled = true;
}

void QLinkProp::hide()
{
    label->clear();
    enabled = false;
}


double QLinkProp::genRandom(double disabledMin, double disabledMax, double min, double max)
{
    std::default_random_engine e(time(NULL));
    std::mt19937 rand_engine(e());
    std::uniform_real_distribution<double> random(0, Constant::windowHeight);
    int tot = 0;
    genTime += num * num;
    while (tot < 500) {
        tot++;
        double res = random(rand_engine);
        for (int i = 1; i <= genTime; i++) res = random(rand_engine);
        if ((res < disabledMin || res > disabledMax) && res > min && res < max) {
            return res;
        }
    }
    return 0.0;
}

double QLinkProp::getX()
{
    return posx;
}

double QLinkProp::getY()
{
    return posy;
}


QJsonObject QLinkProp::convertToJson()
{
    QJsonObject object;
    object.insert("type", type);
    object.insert("posx", posx);
    object.insert("posy", posy);
    object.insert("enabled", enabled);
    object.insert("num", num);
    return object;
}

bool QLinkProp::recoverFromJson(QJsonObject object)
{
    QJsonValue value = object.value("type");
    if (value.isDouble()) {
        type = value.toVariant().toInt();
        if (type >= Constant::PropNum) {
            return false;
        }
    } else {
        return false;
    }
    value = object.value("num");
    if (value.isDouble()) {
        num = value.toVariant().toInt();
    } else {
        return false;
    }
    value = object.value("posx");
    if (value.isDouble()) {
        posx = value.toVariant().toDouble();
    } else {
        return false;
    }
    value = object.value("posy");
    if (value.isDouble()) {
        posy = value.toVariant().toDouble();
    } else {
        return false;
    }
    value = object.value("enabled");
    if (value.isBool()) {
        enabled = value.toVariant().toBool();
    } else {
        return false;
    }
    QString filename = ":/res/prop" + QString::number(type + 1) + ".png";
    image = new QImage();
    image->load(filename);
    pixmap = QPixmap::fromImage(*image);
    pixmap = pixmap.scaled(Constant::propWidth, Constant::propHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    label->setGeometry(posx, posy, 30, 30);
    return true;
}

int QLinkProp::getType()
{
    return type;
}

bool QLinkProp::checkCollide(double x, double y)
{
    if (x >= posx - Constant::propWidth && x <= posx + Constant::propWidth && y >= posy - Constant::propHeight &&
        y <= posy + Constant::propHeight) {
        qDebug() << "QLinkProp::checkCollide:" << x << " " << y << " " << posx << " " << posy << " true";
        return true;
    } else {
        qDebug() << "QLinkProp::checkCollide:" << x << " " << y << " " << posx << " " << posy << " false";
        return false;
    }
    return false;
}

void QLinkProp::setType(int num)
{
    if (num >= Constant::PropNum || num < 0) {
        return;
    }
    type = num;
    QString filename = ":/res/prop" + QString::number(type + 1) + ".png";
    image = new QImage();
    image->load(filename);
    pixmap = QPixmap::fromImage(*image);
    pixmap = pixmap.scaled(Constant::propWidth, Constant::propHeight, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    label->setGeometry(posx, posy, 30, 30);
}

