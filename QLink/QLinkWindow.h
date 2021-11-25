#ifndef QLINKWINDOW_H
#define QLINKWINDOW_H

#include <QObject>
#include <QTimer>
#include "QPlayer.h"
#include "Constant.h"
#include "QLinkMap.h"
#include "QLinkProp.h"
#include <QMainWindow>
#include <QKeyEvent>

QT_BEGIN_NAMESPACE
namespace Ui { class QLinkWindow; }
QT_END_NAMESPACE

class QLinkWindow : public QMainWindow
{
    Q_OBJECT

public:
     QLinkWindow(QWidget *parent = nullptr);

    ~QLinkWindow();

    void init(Constant::MODE mode);

    void saveToFile();

    bool recoverFromFile();

protected:
    void paintEvent(QPaintEvent *);

private slots:
    void on_quitButton_clicked();

    void on_startButton_clicked();

    void on_pauseButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_returnButton_clicked();

    void updateTime();

    void on_clearButton_clicked();

private:
    Ui::QLinkWindow *ui;

    Constant::MODE mode;

    QTimer *timer;

    QLinkMap *map;

    int remainTime,hintTime;

    int h,w;

    bool started, paused;

    bool recovered;  //是否从存档恢复

    QPlayer *player[2];

    QLinkProp *prop;

    std::vector< std::pair<int,int> > selected[2];

    QString convertTime(int time);

    void keyPressEvent(QKeyEvent *event);

    void checkCollideWithMap(int num,int dx,int dy); //检查是否与地图碰撞

    void handleCollide(int num);

    void checkCollideWithProp(); //单人模式下检查是否与道具碰撞


signals:
    void stopGame();

    void quitGame();
};

#endif // QLINKWINDOW_H
