#ifndef UNITTEST_H
#define UNITTEST_H

#include <QtTest/QtTest>
#include "QLinkMap.h"


class UnitTest : public QObject {
    Q_OBJECT
public:
    UnitTest();

private slots:
    void testVertical();

    void testHorizonal();

    void testOneCorner();

    void testTwoCorners();

    void testThreeCorners();

    void testFailure();

    void testFinish();

private:
    QLinkMap *qLinkMap;
};

#endif // UNITTEST_H
