#include "UnitTest.h"
#include <iostream>

using namespace std;

int main()
{
    UnitTest *test = new UnitTest();
    QTest::qExec(test);
    delete test;
    return 0;
}
