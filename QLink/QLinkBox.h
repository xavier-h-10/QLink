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

    /**
     * @brief 恢复时使用的构造函数
     * @param h
     * @param w
     * @param type 方块类型
     */
    QLinkBox(int h, int w, int type);

    /**
     * @brief 默认的构造函数
     * @param h
     * @param w
     * @param type
     * @param icon 方块对应的图片
     */
    QLinkBox(int h, int w, int type, QImage *icon);

    /**
     * @brief 根据玩家编号,选中时需要标注不同颜色
     * @param num 玩家编号
     */
    void select(int num);

    /**
     * @brief 取消选中当前的方格
     *
     */
    void deSelect();

    /**
     * @brief 清空当前的方格
     */
    void clear();

    /**
     * @brief 设置方格为提示色
     */
    void hint();

    /**
     * @brief shuffle后改变当前方格类型
     * @param icon 新的图片
     */
    void changeType(QImage *icon);

    ~QLinkBox();

    QLabel *getLabel();

private:
    QLabel *label;

    QPixmap pixmap;

    int h, w;

    bool isEmpty;

    int type;

};


#endif //QLINK_QLINKBOX_H
