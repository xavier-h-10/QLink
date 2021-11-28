//
// Created by 黄喆敏 on 2021/11/1.
//

#include "QPlayer.h"
#include "Constant.h"
#include <QDebug>
#include <random>
#include <QJsonObject>
#include <QJsonValue>

QPlayer::QPlayer()
{
}

QPlayer::QPlayer(int type, QLabel *label) : type(type), label(label)
{
    score = 0;
    posx = posy = 0.0;
    enabled = false;
    QString filename = ":/res/player" + QString::number(type + 1) + ".png";
    image = new QImage();
    image->load(filename);
    pixmap = QPixmap::fromImage(*image);
    pixmap = pixmap.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    generate();
}

void QPlayer::generate()
{
    posx = genRandom(Constant::mapMinX - 10, Constant::mapMaxX + 10, 30, Constant::windowWidth - 30);
    posy = genRandom(Constant::mapMinY - 10, Constant::mapMaxY + 10, Constant::playerMinY, Constant::playerMaxY);
    qDebug() << "QPLayer::generate" << posx << " " << posy;
    label->setGeometry(posx, posy, 30, 30);
}


void QPlayer::show()
{
    label->setGeometry(posx, posy, 30, 30);
    label->setPixmap(pixmap);
    label->setAlignment(Qt::AlignCenter);
    label->setAutoFillBackground(true);
    enabled = true;
}

void QPlayer::hide()
{
    label->clear();
    enabled = false;
}

bool QPlayer::moveVaild(double x, double y)
{
    if (x < 0 || y < Constant::playerMinY || x > Constant::windowWidth || y > Constant::playerMaxY) return false;
    return true;
}

void QPlayer::move(double dx, double dy)
{
    if (enabled) {
        qDebug() << "move player " << type << " posx=" << posx << " posy=" << posy;
        dx = dx * Constant::moveSpeed;
        dy = dy * Constant::moveSpeed;
        if (moveVaild(posx + dx, posy + dy)) {
            posx += dx;
            posy += dy;
            label->setGeometry(posx, posy, 30, 30);
        }
    }
}


double QPlayer::genRandom(double disabledMin, double disabledMax, double min, double max)
{
    std::default_random_engine e(time(NULL));
    std::mt19937 rand_engine(e());
    std::uniform_real_distribution<double> random(0, Constant::windowHeight);
    int tot = 0;
    while (tot < 500) {
        tot++;
        double res = random(rand_engine);
        if (type != 0) {
            for (int i = 1; i <= 3; i++) res = random(rand_engine);
        } else {
            for (int i = 1; i <= 5; i++) res = random(rand_engine);
        }
        if ((res < disabledMin || res > disabledMax) && res > min && res < max) {
            return res;
        }
    }
    return 0.0;
}

double QPlayer::getX()
{
    return posx;
}

double QPlayer::getY()
{
    return posy;
}

void QPlayer::addScore(int x)
{
    score += x;
}

int QPlayer::getScore()
{
    return score;
}


QJsonObject QPlayer::convertToJson()
{
    QJsonObject object;
    object.insert("score", score);
    object.insert("type", type);
    object.insert("posx", posx);
    object.insert("posy", posy);
    object.insert("enabled", enabled);
    return object;
}


bool QPlayer::recoverFromJson(QJsonObject object)
{
    qDebug() << "QPlayer::recoverFromJson called";
    QJsonValue value = object.value("score");
    if (value.isDouble()) {
        score = value.toVariant().toInt();
    } else {
        return false;
    }

    value = object.value("type");
    if (value.isDouble()) {
        type = value.toVariant().toInt();
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
    }

    //重新加载图片
    QString filename = ":/res/player" + QString::number(type + 1) + ".png";
    image = new QImage();
    image->load(filename);
    pixmap = QPixmap::fromImage(*image);
    pixmap = pixmap.scaled(30, 30, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    label->setGeometry(posx, posy, 30, 30);

    return true;
}

void QPlayer::clear()
{
    score = 0;
}
