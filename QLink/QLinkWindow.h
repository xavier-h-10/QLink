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
#include <QGraphicsScene>
#include <QPen>
#include <list>

QT_BEGIN_NAMESPACE
namespace Ui { class QLinkWindow; }
QT_END_NAMESPACE

class QLinkWindow : public QMainWindow {
    Q_OBJECT

public:
    QLinkWindow(QWidget *parent = nullptr);

    ~QLinkWindow();

    /**
     * @brief 初始化地图,对ui控件进行操作
     * @param mode 游戏模式
     */
    void init(Constant::MODE mode);

    /**
     * @brief 游戏状态保存到文件
     */
    void saveToFile();

    /**
     * @brief 从文件恢复游戏状态
     * @return 是否恢复成功
     */
    bool recoverFromFile();

    /**
     * @brief 清空当前窗口
     */
    void clear();

private slots:
    void on_quitButton_clicked();

    void on_startButton_clicked();

    void on_pauseButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_returnButton_clicked();

    void on_clearButton_clicked();

    /**
     * @brief 每一秒调用一次,更新时间
     */
    void updateTime();

    void on_heightBox_valueChanged(int arg1);

    void on_widthBox_valueChanged(int arg1);

private:
    Ui::QLinkWindow *ui;

    Constant::MODE mode;

    QTimer *timer;

    QLinkMap *map;

    int remainTime, hintTime;

    int h, w;

    bool started, paused;

    bool recovered;  //是否从存档恢复

    QPlayer *player[2];

    QLinkProp *prop[3];

    std::vector <std::pair<int, int>> selected[2];

    struct node {
        int x, y;
        int remainTime;
        node(int x, int y, int remainTime) : x(x), y(y), remainTime(remainTime) {}
    };

    std::list <node> clearTarget;

    QPen pen; //画方格连线

    QGraphicsScene *scene; //方格连线所用

    /**
     * @brief 秒数转换为分:秒格式
     * @param time 时间
     * @return 转换结果
     */
    QString convertTime(int time);

    /**
     * @brief 监听键盘
     * @param event
     */
    void keyPressEvent(QKeyEvent *event);

    /**
     * @brief 检查是否与地图碰撞,同时根据上次位置判断是否需要选中该方格
     * @param num 玩家编号
     * @param dx 横坐标移动方向
     * @param dy 纵坐标移动方向
     */
    void checkCollideWithMap(int num, int dx, int dy);

    /**
     * @brief 判断玩家与方格碰撞后的处理逻辑
     * @param num 玩家编号
     */
    void handleCollide(int num);

    /**
     * @brief 检查是否与道具相撞
     * @param num 玩家编号
     */
    void checkCollideWithProp(int num);

    /**
     * @brief 检验生成道具与角色距离,防止过近
     * @param num 道具编号
     */
    void checkPropDistance(int num);

    /**
     * @brief 检验生成道具与角色距离,防止过近
     */
    void checkPlayerDistance();

    /**
     * @brief 画方格连线
     */
    void drawLine();

    signals:
    void stopGame();

    void quitGame();
};

#endif // QLINKWINDOW_H
