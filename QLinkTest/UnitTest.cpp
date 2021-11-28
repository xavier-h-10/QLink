#include "UnitTest.h"
#include <QVector>

UnitTest::UnitTest()
{
    qLinkMap = new QLinkMap();
}


void UnitTest::testVertical()
{
    QVector <QVector<int>> map{{1,  0,  2,  3},
                               {4,  5,  2,  6},
                               {7,  8,  9,  10},
                               {11, 12, 13, 14}};
    QVector <QVector<int>> status{{1, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {1, 1, 1, 1}};
    qLinkMap->loadMap(map, status);
    QVERIFY(qLinkMap->checkFinish() == false);
    QVERIFY(qLinkMap->checkSolvable() == true);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = i; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    if (i == k && j == l) continue;
                    if ((i == 0 && j == 2 && k == 1 && l == 2)) continue;
                    QVERIFY(qLinkMap->checkRemove(i, j, k, l) == 0);
                }
            }
        }
    }
    QVERIFY(qLinkMap->checkRemove(0, 2, 1, 2) != 0);
}

void UnitTest::testHorizonal()
{
    QVector <QVector<int>> map{{1,  5,  2,  3},
                               {4,  3,  3,  6},
                               {7,  8,  9,  10},
                               {11, 12, 13, 14}};
    QVector <QVector<int>> status{{1, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {1, 1, 1, 1}};
    qLinkMap->loadMap(map, status);
    QVERIFY(qLinkMap->checkFinish() == false);
    QVERIFY(qLinkMap->checkSolvable() == true);
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = i; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    if (i == k && j == l) continue;
                    if ((i == 1 && j == 1 && k == 1 && l == 2) || (i == 1 && j == 2 && k == 1 && l == 1)) continue;
                    QVERIFY(qLinkMap->checkRemove(i, j, k, l) == 0);
                }
            }
        }
    }
    QVERIFY(qLinkMap->checkRemove(1, 1, 1, 2) != 0);
}

void UnitTest::testOneCorner()
{
    QVector <QVector<int>> map{{-1, 4,  2,  3},
                               {4,  3,  8,  6},
                               {7,  8,  -1, 10},
                               {11, 12, 13, 14}};
    QVector <QVector<int>> status{{-1, 1, 1,  1},
                                  {1,  1, 1,  1},
                                  {1,  1, -1, 1},
                                  {1,  1, 1,  1}};
    qLinkMap->loadMap(map, status);
    QVERIFY(qLinkMap->checkFinish() == false);
    QVERIFY(qLinkMap->checkSolvable() == true);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = i; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    if (i == k && j == l) continue;
                    if (i == 0 && j == 1 && k == 1 && l == 0) continue;
                    if (i == 1 && j == 2 && k == 2 && l == 1) continue;
                    QVERIFY(qLinkMap->checkRemove(i, j, k, l) == 0);
                }
            }
        }
    }
    QVERIFY(qLinkMap->checkRemove(0, 1, 1, 0) != 0);
    QVERIFY(qLinkMap->checkRemove(1, 2, 2, 1) != 0);
};


void UnitTest::testTwoCorners()
{
    QVector <QVector<int>> map{{-1, 4,  2,  3},
                               {5,  10, 8,  6},
                               {7,  -1, -1, 3},
                               {11, 12, 10, 14}};
    QVector <QVector<int>> status{{-1, 1,  1,  1},
                                  {1,  1,  1,  1},
                                  {1,  -1, -1, 1},
                                  {1,  1,  1,  1}};
    qLinkMap->loadMap(map, status);
    QVERIFY(qLinkMap->checkFinish() == false);
    QVERIFY(qLinkMap->checkSolvable() == true);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = i; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    if (i == k && j == l) continue;
                    if (i == 0 && j == 3 && k == 2 && l == 3) continue;
                    if (i == 1 && j == 1 && k == 3 && l == 2) continue;
                    QVERIFY(qLinkMap->checkRemove(i, j, k, l) == 0);
                }
            }
        }
    }
    QVERIFY(qLinkMap->checkRemove(0, 3, 2, 3) != 0);
    QVERIFY(qLinkMap->checkRemove(1, 1, 3, 2) != 0);
}

void UnitTest::testThreeCorners()
{
    QVector <QVector<int>> map{{1,  2,  13, 4},
                               {5,  6,  7,  14},
                               {9,  10, 11, 12},
                               {13, 14, 5,  16}};
    QVector <QVector<int>> status{{1, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {1, 1, 1, 1}};
    qLinkMap->loadMap(map, status);
    QVERIFY(qLinkMap->checkFinish() == false);
    QVERIFY(qLinkMap->checkSolvable() == false);

    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            for (int k = i; k < 4; k++) {
                for (int l = 0; l < 4; l++) {
                    if (i == k && j == l) continue;
                    QVERIFY(qLinkMap->checkRemove(i, j, k, l) == 0);
                }
            }
        }
    }
}

void UnitTest::testFailure()
{
    QVector <QVector<int>> map{{1, 2, 3, 4},
                               {2, 1, 4, 3},
                               {3, 4, 1, 2},
                               {4, 1, 2, 5}};
    QVector <QVector<int>> status{{1, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {1, 1, 1, 1},
                                  {1, 1, 1, 1}};
    qLinkMap->loadMap(map, status);
    QVERIFY(qLinkMap->checkFinish() == false);
    QVERIFY(qLinkMap->checkSolvable() == false);
}

void UnitTest::testFinish()
{
    QVector <QVector<int>> map{{-1, -1, -1, -1},
                               {-1, -1, -1, -1},
                               {-1, -1, -1, -1},
                               {-1, -1, -1, -1}};
    QVector <QVector<int>> status{{-1, -1, -1, -1},
                                  {-1, -1, -1, -1},
                                  {-1, -1, -1, -1},
                                  {-1, -1, -1, -1}};
    qLinkMap->loadMap(map, status);
    QVERIFY(qLinkMap->checkFinish() == true);
    QVERIFY(qLinkMap->checkSolvable() == false);
}

//QTEST_MAIN(UnitTest)
