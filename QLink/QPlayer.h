//
// Created by 黄喆敏 on 2021/11/1.
//

#ifndef QLINK_QPLAYER_H
#define QLINK_QPLAYER_H

#include <QLabel>


class QPlayer {
public:
    QPlayer();

    QPlayer(int type, QLabel *label);

    void show();

    void hide();

    void generate(); //生成新的位置

    void move(double dx, double dy);

    double getX();

    double getY();

    void addScore(int x);

    int getScore();

    QJsonObject convertToJson();

    bool recoverFromJson(QJsonObject object);

private:
    int score;
    int type;
    double posx, posy;
    bool enabled;
    QLabel *label;
    QImage *image;
    QPixmap pixmap;

    bool moveVaild(double x, double y);

    double genRandom(double disabledMin, double disabledMax, double min, double max); //生成随机坐标，且不在地图内

};


#endif //QLINK_QPLAYER_H
