//
// Created by 黄喆敏 on 2021/11/1.
//

#ifndef QLINK_QPLAYER_H
#define QLINK_QPLAYER_H

#include <QLabel>


class QPlayer {
public:
    /**
     * @brief 默认构造函数,恢复时使用
     */
    QPlayer();

    /**
     * @brief 构造函数,开始一盘新游戏时使用
     * @param type
     * @param label
     */
    QPlayer(int type, QLabel *label);

    /**
     * @brief 展示玩家位置
     */
    void show();

    /**
     * @brief 隐藏玩家位置
     */
    void hide();

    /**
     * @brief 生成新的位置
     */
    void generate();

    /**
     * @brief 移动玩家位置
     * @param dx 横坐标移动距离
     * @param dy 纵坐标移动距离
     */
    void move(double dx, double dy);

    /**
     * @brief convertToJson
     * @return JSON对象
     */
    QJsonObject convertToJson();

    /**
     * @brief 从JSON对象恢复
     * @param object JSON对象
     * @return 玩家是否可以恢复
     */
    bool recoverFromJson(QJsonObject object);

    /**
     * @brief 清空玩家状态
     */
    void clear();

    double getX();

    double getY();

    void addScore(int x);

    int getScore();

private:
    int score;

    int type;

    double posx, posy;

    bool enabled;

    QLabel *label;

    QImage *image;

    QPixmap pixmap;

    /**
     * @brief 判断玩家是否可以移动到该坐标
     * @param x
     * @param y
     * @return
     */
    bool moveVaild(double x, double y);

    /**
     * @brief 生成[min, disabledMin) / (disableMax, max]范围的随机数
     * @param disabledMin 禁止的最小范围
     * @param disabledMax 禁止的最大范围
     * @param min 最小范围
     * @param max 最大范围
     * @return 随机数
     */
    double genRandom(double disabledMin, double disabledMax, double min, double max);
};


#endif //QLINK_QPLAYER_H
