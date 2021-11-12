//
// Created by 黄喆敏 on 2021/11/1.
//

#ifndef QLINK_CONSTANT_H
#define QLINK_CONSTANT_H

#include <QString>

namespace Constant {
    static const QString iconUrl = "../static";
    static const int boxType = 4;
    static const int countdown=15; //设置180s的倒计时
    static const int mapMin=3;
    static const int mapMax=10;
    static const int mapDefault=5;
    enum PlayerType {
        SINGLE,
        DOUBLE_1,
        DOUBLE_2
    };
    enum Direction {
        LEFT,
        RIGHT,
        TOP,
        DOWN
    };
    enum MODE {
        SINGLE_MODE,
        DOUBLE_MODE,
    };
}

#endif //QLINK_CONSTANT_H
