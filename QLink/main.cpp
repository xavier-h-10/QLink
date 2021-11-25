#include "QWindowController.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    QWindowController &controller = QWindowController::getInstance();
    return a.exec();
}
