//
// Created by 黄喆敏 on 2021/11/1.
//

#ifndef QLINK_CONSTANT_H
#define QLINK_CONSTANT_H

#include <QString>

namespace Constant {
    static const QString iconUrl = "../static";
    static const int boxType = 4;
    static const int boxScore[4] = {15, 25, 35, 45};

    static const int countdown = 150; //设置180s的倒计时
    static const int mapMin = 3;
    static const int mapMax = 10;
    static const int mapDefault = 6;
    static const int windowWidth = 800;
    static const int windowHeight = 800;

    static const int mapMinX = 150; //地图左上角和右下角坐标
    static const int mapMinY = 185;
    static const int mapMaxX = 650;
    static const int mapMaxY = 685;
    static const int playerMinY = 140; //避免玩家移动到操作台
    static const int playerMaxY = 700;

    static const int propWidth = 30; //道具宽度
    static const int propHeight = 30; //道具高度
    static const int PropNum = 3; //道具种类

    static const int addCountdown = 30; //增加30s倒计时
    static const int hintTime = 10; //hint道具生效时间

    static const double moveSpeed = 15;  //设置移动速度
    enum PlayerType {
        SINGLE,
        DOUBLE_1,
        DOUBLE_2
    };

    enum PropType {
        ADD_TIME,
        SHUFFLE,
        HINT
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

    enum BoxStatus {
        SELECTED_BY_FIRST,   //被第一个玩家选中
        SELECTED_BY_SECOND,  //被第二个玩家选中
        NOT_SELECTED,
        EMPTY
    };
}

#endif //QLINK_CONSTANT_H
