#ifndef QWINDOWCONTROLLER_H
#define QWINDOWCONTROLLER_H

#include <QObject>
#include "QLinkMenu.h"
#include "Constant.h"
#include "QLinkWindow.h"

class QWindowController: public QObject
{
    Q_OBJECT

private:
    QLinkWindow *qLinkWindow;
    QLinkMenu *qLinkMenu;

private slots:
    void startGame(Constant::MODE mode);
    void stopGame();
    void quitGame();
public:
    QWindowController();

    ~QWindowController();

    static QWindowController& getInstance() {
        static QWindowController instance;
        return instance;
    }
};

#endif // QWINDOWCONTROLLER_H
