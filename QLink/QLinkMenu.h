#ifndef QLINKMENU_H
#define QLINKMENU_H

#include "Constant.h"
#include <QWidget>

namespace Ui { class QLinkMenu; }

class QLinkMenu : public QWidget {
    Q_OBJECT

public:
    explicit QLinkMenu(QWidget *parent = nullptr);

    ~QLinkMenu();

private slots:

    void on_startSingleGameButton_clicked();

    void on_startDoubleGameButton_clicked();

    void on_loadGameButton_clicked();

    void on_quitGameButton_clicked();

private:
    Ui::QLinkMenu *ui;

    /**
     * @brief 载入文件
     * @param dir 文件目录
     * @param str 文件名称
     */
    void loadFile(const QString &dir,const QString &str);

signals:
    void startGame(Constant::MODE mode);

    void quitGame();

    void loadGame();
};
#endif // QLINKMENU_H
