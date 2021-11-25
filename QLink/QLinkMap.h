//
// Created by 黄喆敏 on 2021/11/1.
//

#ifndef QLINK_QLINKMAP_H
#define QLINK_QLINKMAP_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QJsonObject>
#include "QLinkBox.h"
#include "Constant.h"

class QLinkMap {
public:

    QLinkMap();

//    QLinkMap(int m, int n);

    void generate(int m,int n);

    ~QLinkMap();

    bool judgeMap();

    QGridLayout *getLayout();

    void setBoxStatus(int x, int y, Constant::BoxStatus p);

    Constant::BoxStatus getBoxStatus(int x, int y); //获取某一格的状态

    int checkRemove(int fromX, int fromY, int toX, int toY); //检验两个方格是否可以消除,并返回分值

    bool checkSolvable(); //判断地图是否可解

    bool checkFinish(); //判断游戏是否结束

    QJsonObject convertToJson(); //转换为json对象保存

    bool recoverFromJson(QJsonObject object); //从json对象恢复

    void shuffle(); //重排地图

    void hint();

    bool isHint(int fromX,int fromY, int toX,int toY); //判断消除的是否为之前给的hint

    void clear(); //清空地图

private:
    QGridLayout *layout;
    QVector <QVector<QLinkBox *>> boxes;

    QImage *icons[Constant::boxType];
    QVector <QVector<int>> map;
    QVector <QVector<Constant::BoxStatus>> status;
    int h, w;

    int fromX, fromY, toX, toY;  //存储找到的一对，可以到达

    int hintFromX,hintFromY,hintToX,hintToY;

    // 判断方块是否可以通过两次以内的折线进行连接
    // corner: 当前拐角数
    bool search(int nowX, int nowY, int toX, int toY, int corner, int d);

    bool checkPoint(int x, int y); //判断点是否出界

    int direction[4][2] = {{-1, 0},
                           {1,  0},
                           {0,  -1},
                           {0,  1}};

    void generateMap(); //生成可行的地图

};


#endif //QLINK_QLinkWindow_H
