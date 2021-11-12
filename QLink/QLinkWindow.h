#ifndef QLINKWINDOW_H
#define QLINKWINDOW_H

#include <QObject>
#include <QTimer>
#include "QPlayer.h"
#include "Constant.h"
#include <QMainWindow>

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

private slots:
    void on_quitButton_clicked();
    void updateTime();

    void on_startButton_clicked();

    void on_pauseButton_clicked();

    void on_saveButton_clicked();

    void on_loadButton_clicked();

    void on_returnButton_clicked();

private:
    Ui::QLinkWindow *ui;

    Constant::MODE mode;

    QTimer *timer;

    int remainTime;

    bool started, paused;

    QPlayer *player1, *player2;

    QString convertTime(int time);

signals:
    void stopGame();
    void quitGame();
};

#endif // QLINKWINDOW_H
