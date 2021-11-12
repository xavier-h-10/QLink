//
// Created by 黄喆敏 on 2021/11/1.
//

#ifndef QLINK_QLINKMAP_H
#define QLINK_QLINKMAP_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include "QLinkBox.h"

class QLinkMap: public QWidget {
public:
    QLinkMap(int m, int n);

    ~QLinkMap();

    bool judgeMap();

    bool judgeBoxes(int x1,int y1,int x2,int y2);

private:
    QGridLayout *layout;
    QVector<QVector<QLinkBox *> > boxes;
    QVector<QVector<int> > map;
    int m;
    int n;

    bool vis;

    bool search(int nowX,int nowY,int toX,int toY,int corner,int direction); // 判断方块是否可以通过两次以内的折线进行连接

    bool checkPoint(int x,int y); //判断点是否出界
};


#endif //QLINK_QLinkWindow_H
