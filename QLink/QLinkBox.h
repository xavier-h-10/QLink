//
// Created by 黄喆敏 on 2021/11/1.
//

#ifndef QLINK_QLINKBOX_H
#define QLINK_QLINKBOX_H

#include <QImage>
#include <QLabel>
#include <QObject>
#include <QWidget>
#include <QPixmap>

class QLinkBox {
public:
    QLinkBox(int h, int w, int type, QImage *icon);

    ~QLinkBox();

    QLabel *getLabel();

    void select(int num); //根据玩家编号,选中时需要标注不同颜色

    void deSelect();

    void clear();

    void hint();

    void changeType(QImage *icon); //shuffle后改变类型

private:
    QLabel *label;
    QPixmap pixmap;
    int h, w;
    bool isEmpty;
    int type;

};


#endif //QLINK_QLINKBOX_H
