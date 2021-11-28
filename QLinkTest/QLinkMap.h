//
// Created by 黄喆敏 on 2021/11/1.
//

#ifndef QLINK_QLINKMAP_H
#define QLINK_QLINKMAP_H

#include <QVector>

class QLinkMap {
public:

    QLinkMap();

    ~QLinkMap();


    void setBoxStatus(int x, int y, int p);

    int getBoxStatus(int x, int y); //获取某一格的状态

    int checkRemove(int fromX, int fromY, int toX, int toY); //检验两个方格是否可以消除,并返回分值


    bool checkSolvable(); //判断地图是否可解

    bool checkFinish(); //判断游戏是否结束

    void loadMap(const QVector <QVector<int>> &map, const QVector <QVector<int>> &status);

private:

    QVector <QVector<int>> map;

    QVector <QVector<int>> status;

    QVector <QPair<int, int>> route;

    int h, w;

    int fromX, fromY, toX, toY;  //存储找到的一对，可以到达

    int direction[4][2] = {{-1, 0},
                           {1,  0},
                           {0,  -1},
                           {0,  1}};

    // 判断方块是否可以通过两次以内的折线进行连接
    // corner: 当前拐角数
    bool search(int nowX, int nowY, int toX, int toY, int corner, int d);

    bool checkPoint(int x, int y); //判断点是否出界

    bool checkPointOut(int x, int y); //判断当前位置是否不可走
};


#endif //QLINK_QLinkWindow_H
