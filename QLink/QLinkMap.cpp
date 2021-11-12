//
// Created by 黄喆敏 on 2021/11/1.
//

#include "QLinkMap.h"
#include "Constant.h"
#include <ctime>
#include <cstdlib>

QLinkMap::QLinkMap(int m, int n) : m(m), n(n) {
    map.resize(m);
    for (int i = 0; i < m; i++) {
        map[i].resize(n);
    }

    srand(time(NULL));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            int tmp = rand() % Constant::boxType;
            map[i][j]=tmp;
        }
    }
    setLayout(layout);


}

QLinkMap::~QLinkMap() {
    delete layout;
    layout = nullptr;
}

bool QLinkMap::judgeMap() {
    return true;
}

bool QLinkMap::judgeBoxes(int x1, int y1, int x2, int y2) {
    if(!checkPoint(x1,y1) || !checkPoint(x2,y2)) {
        return false;
    }
    if(map[x1][y1]==-1 || map[x2][y2]==-1) {
        return false;
    }
    return true;
}


bool QLinkMap::checkPoint(int x, int y) {
    if (x < 0 || x >= m || y < 0 || y >= n) {
        return false;
    }
    return true;
}
