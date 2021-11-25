#ifndef QLINKPROP_H
#define QLINKPROP_H

#include <QLabel>


class QLinkProp {
public:
    QLinkProp(QLabel *label);

    void generate();

    void show();

    void hide();

    int getType();

    bool checkCollide(double x, double y);

    QJsonObject convertToJson();

    bool recoverFromJson(QJsonObject object);

    double getX();

    double getY();

    void updateStatus();

    void setRemainTime(int time);

    int getRemainTime(int time);

private:
    int type;
    double posx, posy;
    bool enabled;
    QLabel *label;
    QImage *image;
    QPixmap pixmap;

    double genRandom(double disabledMin, double disabledMax, double min, double max); //生成随机坐标，且不在地图内

};


#endif // QLINKPROP_H
