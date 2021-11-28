//
// Created by 黄喆敏 on 2021/11/1.
//

#ifndef QLINK_QLINKMAP_H
#define QLINK_QLINKMAP_H

#include <QWidget>
#include <QGridLayout>
#include <QVector>
#include <QJsonObject>
#include <QLineF>
#include "QLinkBox.h"
#include "Constant.h"

class QLinkMap {
public:

    /**
     * @brief 构造函数,载入方格对应的图片
     */
    QLinkMap();

    /**
     * @brief 生成可行的地图
     * @param m 宽
     * @param n 高
     */
    void generate(int m, int n);

    /**
     * @brief 设置某一个方格的状态
     * @param x 横坐标
     * @param y 纵坐标
     * @param p 方格状态
     */
    void setBoxStatus(int x, int y, Constant::BoxStatus p);

    /**
     * @brief 获取某一格的状态
     * @param x 横坐标
     * @param y 纵坐标
     * @return 方格状态
     */
    Constant::BoxStatus getBoxStatus(int x, int y);

    /**
     * @brief 检验两个方格是否可以消除,并返回分值
     * @param fromX
     * @param fromY
     * @param toX
     * @param toY
     * @return 不可消除返回0分,可消除返回两个方格分值之和
     */
    int checkRemove(int fromX, int fromY, int toX, int toY);

    /**
     * @brief 判断地图是否可解
     * @return 可解返回true,否则返回false
     */
    bool checkSolvable();

    /**
     * @brief 判断方格是否消完
     * @return 消完返回true,否则返回false
     */
    bool checkFinish();

    /**
     * @brief 获取之前消去的两点路径
     * @return 路径
     */
    QVector <QLineF> getPath();

    /**
     * @brief convertToJson
     * @return JSON对象
     */
    QJsonObject convertToJson(); //转换为json对象保存

    /**
     * @brief 从JSON对象恢复
     * @param object JSON对象
     * @return 地图是否可以恢复
     */
    bool recoverFromJson(QJsonObject object);

    /**
     * @brief 重排地图
     */
    void shuffle();

    /**
     * @brief 给一对提示方格
     */
    void hint();

    /**
     * @brief 判断消除的是否为之前给的hint
     * @param fromX
     * @param fromY
     * @param toX
     * @param toY
     * @return 若是之前给的hint,返回true,否则返回false
     */
    bool isHint(int fromX, int fromY, int toX, int toY);

    /**
     * @brief 清空地图
     */
    void clear();

    /**
     * @brief 清空某一个格子
     * @param x
     * @param y
     */
    void clearBox(int x, int y);

    /**
     * @brief 求当前剩余的方块个数,便于双人模式下判断是否可解
     * @return 剩余的方块个数
     */
    int remainNumber();

    /**
     * @brief hint时间结束,需要重置hint的方格
     */
    void deHint();

    QGridLayout *getLayout();

    ~QLinkMap();

private:
    QGridLayout *layout;

    QVector <QVector<QLinkBox *>> boxes;

    QImage *icons[Constant::boxType];

    QVector <QVector<int>> map;

    QVector <QVector<Constant::BoxStatus>> status;

    QVector <QPair<int, int>> route;

    QVector <QLineF> path;

    int h, w;

    int fromX, fromY, toX, toY;  //存储找到的一堆坐标

    int hintFromX, hintFromY, hintToX, hintToY; //存储给出的hint坐标

    int direction[4][2] = {{-1, 0},
                           {1,  0},
                           {0,  -1},
                           {0,  1}};

    /**
     * @brief 判断方块是否可以通过两次以内的折线进行连接
     * @param nowX 当前横坐标
     * @param nowY 当前纵坐标
     * @param toX  目标横坐标
     * @param toY  目标纵坐标
     * @param corner 当前拐角数
     * @param d 当前方向 0-3
     * @return
     */
    bool search(int nowX, int nowY, int toX, int toY, int corner, int d);

//    void dijkstra(int fromX,int fromY,int toX,int toY);

    /**
     * @brief 判断点是否出界(不包括地图外一圈)
     * @param x
     * @param y
     * @return
     */
    bool checkPoint(int x, int y);

    /**
     * @brief 判断当前位置是否不可走(包括地图外一圈)
     * @param x
     * @param y
     * @return
     */
    bool checkPointOut(int x, int y);

    /**
     * @brief 生成可行的地图
     */
    void generateMap();

    /**
     * @brief 根据当前路径,生成直线
     */
    void generatePath();

    /**
     * @brief 获取给定点所在位置
     * @param x
     * @param y
     * @return 坐标
     */
    QPointF getPos(int x, int y);

};


#endif //QLINK_QLinkWindow_H
