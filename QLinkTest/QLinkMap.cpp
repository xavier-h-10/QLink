//
// Created by 黄喆敏 on 2021/11/1.
//

#include "QLinkMap.h"
#include <ctime>
#include <cstdlib>
#include <cstring>
#include <algorithm>

// empty:0

QLinkMap::QLinkMap()
{
}


bool QLinkMap::checkPoint(int x, int y)
{
    if (x < 0 || x >= h || y < 0 || y >= w) {
        return false;
    }
    return true;
}

int QLinkMap::checkRemove(int fromX, int fromY, int toX, int toY)
{
    if (!checkPoint(fromX, fromY) || !checkPoint(toX, toY)) return 0;
    if (status[fromX][fromY] == 0 || status[fromX][fromY] == 0)
        return 0;
    if (map[fromX][fromY] != map[toX][toY] || map[fromX][fromY] == -1) return 0;
    bool found = false;

    std::vector<int> dir;
    if (fromX < toX) {
        dir = {1, 2, 3, 0};
    } else if (fromX > toX) {
        dir = {0, 1, 2, 3};
    } else {
        if (fromY < toY) {
            dir = {3, 0, 1, 2};
        } else {
            dir = {2, 0, 1, 3};
        }
    }

    for (int i = 0; i < 4; i++) {
        route.clear();
        route.push_back(qMakePair(fromX, fromY));
        if (search(fromX, fromY, toX, toY, 0, dir[i])) {
            found = true;
            route.push_back(qMakePair(toX, toY));
            break;
        }
    }
    if (!found) return 0;
    int score = 10;
    map[fromX][fromY] = -1;
    map[toX][toY] = -1;
    return score;
}

bool QLinkMap::checkPointOut(int x, int y)
{
    if (x < -1 || x > h || y < -1 || y > w) return false;
    return true;
}

bool QLinkMap::search(int nowX, int nowY, int toX, int toY, int corner, int d)
{
    if (nowX == toX && nowY == toY) return true;
    if (!checkPointOut(nowX, nowY)) return false;
    if (d > 4 || d < 0 || corner > 2) return false;

    int dx = direction[d][0];
    int dy = direction[d][1];
    bool f = checkPoint(nowX + dx, nowY + dy);
    if (nowX + dx == toX && nowY + dy == toY) return true;
    if ((f && map[nowX + dx][nowY + dy] == -1) || (!f && checkPointOut(nowX + dx, nowY + dy))) {   //如果按照当前方向可以走,继续搜索
        route.push_back(qMakePair(nowX + dx, nowY + dy));
        bool tmp = search(nowX + dx, nowY + dy, toX, toY, corner, d);
        if (tmp) return true;
        route.pop_back();
    }

    if (corner < 2) {
        for (int i = 0; i < 4; i++) {
            if (d == i) continue;
            dx = direction[i][0];
            dy = direction[i][1];
            if (nowX + dx == toX && nowY + dy == toY) return true;
            if (checkPoint(nowX + dx, nowY + dy) && map[nowX + dx][nowY + dy] != -1) continue; //除了起点和终点,中间经过的点应该为empty
            if (!checkPointOut(nowX + dx, nowY + dy)) continue;

            route.push_back(qMakePair(nowX + dx, nowY + dy));
            bool tmp = search(nowX + dx, nowY + dy, toX, toY, corner + 1, i);
            if (tmp) return true;
            route.pop_back();
        }
    }
    return false;
}

bool QLinkMap::checkSolvable()
{
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (map[i][j] == -1) continue;
            for (int p = i; p < h; p++) {
                for (int q = 0; q < w; q++) {
                    if ((i == p && j == q) || map[p][q] == -1 || map[i][j] != map[p][q]) continue;
                    for (int dir = 0; dir < 4; dir++) {
                        if (search(i, j, p, q, 0, dir)) {
                            {
                                fromX = i;
                                fromY = j;
                                toX = p;
                                toY = q;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool QLinkMap::checkFinish()
{
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (map[i][j] != -1) {
                return false;
            }
        }
    }
    return true;
}


void QLinkMap::loadMap(const QVector <QVector<int>> &map, const QVector <QVector<int>> &status)
{
    this->map = map;
    this->status = status;
    this->h = map.size();
    if (this->h > 0) {
        this->w = map[0].size();
    }
}

