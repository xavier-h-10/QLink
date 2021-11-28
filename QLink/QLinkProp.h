#ifndef QLINKPROP_H
#define QLINKPROP_H

#include <QLabel>


class QLinkProp {
public:
    /**
     * @brief 默认构造函数
     * @param label 道具对应的ui组件
     * @param num 道具种类
     */
    QLinkProp(QLabel *label, int num);

    /**
     * @brief 随机生成一个道具
     */
    void generate();

    /**
     * @brief 展示道具
     */
    void show();

    /**
     * @brief 隐藏道具
     */
    void hide();

    /**
     * @brief 检验人物是否与道具碰撞
     * @param 人物横坐标
     * @param 人物纵坐标
     * @return 是否碰撞
     */
    bool checkCollide(double x, double y);

    /**
     * @brief convertToJson
     * @return JSON对象
     */
    QJsonObject convertToJson();

    /**
     * @brief 从JSON对象恢复
     * @param object JSON对象
     * @return 地图是否可以恢复
     */
    bool recoverFromJson(QJsonObject object);

    /**
     * @brief 设置道具类型,并更改图片
     * @param num 道具类型
     */
    void setType(int num);

    double getX();

    double getY();

    void setRemainTime(int time);

    int getRemainTime(int time);

    int getType();

private:
    int type;

    int genTime; //生成随机数的次数

    double posx, posy;

    bool enabled;

    QLabel *label;

    QImage *image;

    QPixmap pixmap;

    int num;

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


#endif // QLINKPROP_H
