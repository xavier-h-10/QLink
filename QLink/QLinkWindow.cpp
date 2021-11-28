#include "QLinkWindow.h"
#include "ui_QLinkWindow.h"
#include "Constant.h"
#include <QPalette>
#include <QTimer>
#include <QMessageBox>
#include <QDebug>
#include <QLCDNumber>
#include <QMainWindow>
#include <QKeyEvent>
#include <QPainter>
#include <QFileDialog>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonParseError>
#include <QGraphicsLineItem>

QLinkWindow::QLinkWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::QLinkWindow)
{
    ui->setupUi(this);
    setWindowTitle(tr("连连看"));
    setMinimumSize(Constant::windowWidth, Constant::windowHeight);
    setMaximumSize(Constant::windowWidth, Constant::windowHeight);
    ui->heightBox->setMinimum(Constant::mapMin);
    ui->heightBox->setMaximum(Constant::mapMax);
    ui->widthBox->setMinimum(Constant::mapMin);
    ui->widthBox->setMaximum(Constant::mapMax);

    ui->graphicsView->setStyleSheet("background: transparent");

    mode = Constant::MODE::SINGLE_MODE;

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    this->started = false;
    this->paused = false;
    this->recovered = false;

    player[0] = new QPlayer(0, ui->singlePlayer);
    player[1] = new QPlayer(1, ui->doublePlayer);
    ui->heightBox->setValue(Constant::mapDefault);
    ui->widthBox->setValue(Constant::mapDefault);

    prop[0] = new QLinkProp(ui->prop_0, 1);
    prop[1] = new QLinkProp(ui->prop_1, 2);
    prop[2] = new QLinkProp(ui->prop_2, 3);

    map = new QLinkMap();

    pen.setColor(QColor(255, 99, 71));
    pen.setWidth(3);
    scene = new QGraphicsScene();
    scene->clear();
    scene->setSceneRect(-400, -250, 750, 450);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->setFixedSize(800, 500);
    ui->graphicsView->setAlignment(Qt::AlignLeft | Qt::AlignTop);

}

QLinkWindow::~QLinkWindow()
{
    if (timer) {
        timer->stop();
    }
    delete ui;
    ui = nullptr;
    delete map;
    map = nullptr;
}

void QLinkWindow::init(Constant::MODE mode)
{
    this->mode = mode;

    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::red);
    ui->resultLabel->setText("");
    ui->resultLabel->setPalette(pe);
    ui->singleScore->setPalette(pe);
    ui->doubleScore->setPalette(pe);

    if (!recovered) {
        remainTime = Constant::countdown;
        hintTime = 0;
    }
    const QString &nowTime = convertTime(remainTime);
    ui->clock->display(nowTime);
    ui->clock->setSegmentStyle(QLCDNumber::Flat);

    if (!recovered) {
        selected[0].clear();
        selected[1].clear();
        player[0]->clear();
        player[1]->clear();
    }

    if (mode == Constant::MODE::SINGLE_MODE) {
        ui->modeTitle->setText("单人模式");
        ui->singleLabel->setText("玩家分数:");
        ui->singleScore->setText(QString::number(player[0]->getScore()));
        ui->doubleLabel->setText("");
        ui->doubleScore->setText("");
    } else {
        ui->modeTitle->setText("双人模式");
        ui->singleLabel->setText("玩家一分数:");
        ui->singleScore->setText(QString::number(player[0]->getScore()));
        ui->doubleLabel->setText("玩家二分数:");
        ui->doubleScore->setText(QString::number(player[1]->getScore()));
    }
    ui->pauseButton->setText("暂停 (Pause)");

    this->started = false;
    this->paused = false;

    setFocusPolicy(Qt::StrongFocus); //每次进入界面,需要重新focus

    h = ui->heightBox->value();
    w = ui->widthBox->value();

    clearTarget.clear();
    recovered = false;
}

void QLinkWindow::updateTime()
{
    qDebug() << "QLinkWindow::updateTime called start=" << this->started;
    if (!this->started) {
        timer->stop();
    }
    if (hintTime) {
        hintTime--;
        if(hintTime==0) {
            map->deHint();
        }
    }
    remainTime--;
    const QString &nowTime = convertTime(remainTime);
    ui->clock->display(nowTime);

    std::list<node>::iterator it;
    for (it = clearTarget.begin(); it != clearTarget.end();) {
        (*it).remainTime--;
        if ((*it).remainTime <= 0) {
            map->clearBox((*it).x, (*it).y);
            it = clearTarget.erase(it);
            scene->clear();
        } else {
            it++;
        }
    }

    if (remainTime <= 0) {
        timer->stop();
        QMessageBox::information(this, tr("游戏提示"), tr("倒计时完成，游戏结束!"));
        ui->pauseButton->setText("暂停 (Pause)");
        this->started = false;
    }

    qDebug() << "QLinkWindow::updateTime ended";
}

void QLinkWindow::on_startButton_clicked()
{
    if (this->started) {
        QMessageBox::information(this, tr("游戏提示"), tr("游戏已经开始!"));
        return;
    }

    h = ui->heightBox->value();
    w = ui->widthBox->value();
    if ((h * w) % 2 == 1) {
        QMessageBox::information(this, tr("游戏提示"), tr("地图大小为奇数,无法生成地图!"));
        return;
    }

    clear(); //先调用清空方法
    init(mode);

    map->generate(h, w);
    player[0]->generate();
    player[1]->generate();
    if (mode == Constant::DOUBLE_MODE) {
        checkPlayerDistance();
    }
    for (int i = 0; i < 3; i++) {
        prop[i]->generate();
        checkPropDistance(i);
    }
    for (int i = 0; i < 3; i++) {
        prop[i]->setType(i);
    }


    ui->gridFrame->setLayout(map->getLayout());


    updateTime();
    this->started = true;

    player[0]->show();
    if (mode == Constant::MODE::DOUBLE_MODE) {
        player[1]->show();
    }

    for (int i = 0; i < 3; i++) {
        prop[i]->show();
    }
    scene->clear(); //开始时清空画的线
    timer->start(1000);
}


void QLinkWindow::on_pauseButton_clicked()
{
    if (!this->started) {
        QMessageBox::information(this, tr("游戏提示"), tr("游戏尚未开始!"));
        return;
    }
    if (this->paused) {
        timer->start(1000);
        ui->pauseButton->setText("暂停 (Pause)");
    } else {
        timer->stop();
        ui->pauseButton->setText("继续 (Continue)");
    }
    this->paused = !this->paused;
}


//保存状态到json文件中
void QLinkWindow::on_saveButton_clicked()
{
    if (!this->started) {
        QMessageBox::information(this, tr("游戏提示"), tr("游戏尚未开始，无法存档!"));
        return;
    }
    if (!this->paused) {
        QMessageBox::information(this, tr("游戏提示"), tr("请先暂停游戏，再保存存档!"));
        return;
    }
    saveToFile();
}

void QLinkWindow::on_loadButton_clicked()
{
    if (this->started && !this->paused) {
        QMessageBox::information(this, tr("游戏提示"), tr("请先暂停游戏，再载入存档!"));
        return;
    }
    if (!recoverFromFile()) {
        QMessageBox::information(this, tr("游戏提示"), tr("恢复存档失败!"));
    }

}

void QLinkWindow::on_returnButton_clicked()
{
    timer->stop();
    started = false;
    paused = false;
    on_clearButton_clicked();
    emit stopGame();
}

void QLinkWindow::on_quitButton_clicked()
{
    timer->stop();
    emit quitGame();
}

QString QLinkWindow::convertTime(int time)
{
    QString ans = "";
    int min = time / 60;
    int sec = time % 60;
    ans = ans + "0" + QString::number(min) + ":";
    if (sec < 10) ans += "0";
    ans += QString::number(sec);
    return ans;
}

void QLinkWindow::keyPressEvent(QKeyEvent *event)
{
    if (started && !paused) {
        switch (event->key()) {
            case Qt::Key_W:
                player[0]->move(0, -1);
                checkCollideWithMap(0, 0, -1);
                break;
            case Qt::Key_A:
                player[0]->move(-1, 0);
                checkCollideWithMap(0, -1, 0);
                break;
            case Qt::Key_S:
                player[0]->move(0, 1);
                checkCollideWithMap(0, 0, 1);
                break;
            case Qt::Key_D:
                player[0]->move(1, 0);
                checkCollideWithMap(0, 1, 0);
                break;
            case Qt::Key_I:
                player[1]->move(0, -1);
                checkCollideWithMap(1, 0, -1);
                break;
            case Qt::Key_J:
                player[1]->move(-1, 0);
                checkCollideWithMap(1, -1, 0);
                break;
            case Qt::Key_K:
                player[1]->move(0, 1);
                checkCollideWithMap(1, 0, 1);
                break;
            case Qt::Key_L:
                player[1]->move(1, 0);
                checkCollideWithMap(1, 1, 0);
                break;
        }
        checkCollideWithProp(0);
        if (mode == Constant::DOUBLE_MODE) {
            checkCollideWithProp(1);
        }
    }
}

void QLinkWindow::checkCollideWithMap(int num, int dx, int dy)
{
    //判断逻辑:当前与一块方格接触,且上一次不与这一块方格接触
    if (num >= 2) return;
    double posX = player[num]->getX();
    double posY = player[num]->getY();
    double prevPosX = posX - dx * Constant::moveSpeed;
    double prevPosY = posY - dy * Constant::moveSpeed;
    if (posX < Constant::mapMinX || posX > Constant::mapMaxX || posY < Constant::mapMinY ||
        posY > Constant::mapMaxY)
        return;
    int nowy = (posX - Constant::mapMinX) / ((Constant::mapMaxX - Constant::mapMinX) / h);
    int nowx = (posY - Constant::mapMinY) / ((Constant::mapMaxY - Constant::mapMinY) / w);

    int prevY = (prevPosX - Constant::mapMinX) / ((Constant::mapMaxX - Constant::mapMinX) / h);
    int prevX = (prevPosY - Constant::mapMinY) / ((Constant::mapMaxY - Constant::mapMinY) / w);

    if (nowx < 0 || nowx > w || nowy < 0 || nowy > h) return;
    if (prevPosX >= Constant::mapMinX && prevPosX <= Constant::mapMaxX && prevPosY >= Constant::mapMinY &&
        prevPosY <= Constant::mapMaxY) {
        if (nowx == prevX && nowy == prevY) {
            return;
        }
    }

    int size = selected[num].size();
    if (size >= 2) return;
    for (int i = 0; i < size; i++) {
        if (selected[num][i].first == nowx && selected[num][i].second == nowy) {
            return;
        }
    }

    handleCollide(num);
}

void QLinkWindow::handleCollide(int num)
{
    double posX = player[num]->getX();
    double posY = player[num]->getY();
    int nowy = (posX - Constant::mapMinX) / ((Constant::mapMaxX - Constant::mapMinX) / h);
    int nowx = (posY - Constant::mapMinY) / ((Constant::mapMaxY - Constant::mapMinY) / w);
    ui->resultLabel->setText("");

    Constant::BoxStatus status = map->getBoxStatus(nowx, nowy);
    //如果没选中,则选中该方格
    if (status == Constant::BoxStatus::NOT_SELECTED) {
        qDebug() << "QLinkWindow::checkCollide, setBoxStatus" << nowx << " nowy=" << nowy;
        if (num == 0) {
            map->setBoxStatus(nowx, nowy, Constant::BoxStatus::SELECTED_BY_FIRST);
        } else {
            map->setBoxStatus(nowx, nowy, Constant::BoxStatus::SELECTED_BY_SECOND);
        }
        selected[num].push_back(std::make_pair(nowx, nowy));
    }

    int size = selected[num].size();
    //当前角色已经选中了2个,判断是否能消除
    if (size >= 2) {
        int fromX = selected[num][0].first;
        int fromY = selected[num][0].second;
        int toX = selected[num][1].first;
        int toY = selected[num][1].second;
        int score = map->checkRemove(fromX, fromY, toX, toY);
        if (score > 0) {
            qDebug() << "QLinkWindow::checkCollide, setBoxStatus empty" << fromX << " " << fromY << " " << toX << " "
                     << toY;
            map->setBoxStatus(fromX, fromY, Constant::BoxStatus::EMPTY);
            map->setBoxStatus(toX, toY, Constant::BoxStatus::EMPTY);
            //因为要画线,所以延时消除
            clearTarget.push_back(node(fromX, fromY, Constant::delayedTime));
            clearTarget.push_back(node(toX, toY, Constant::delayedTime));
            drawLine();

            if (hintTime && map->isHint(fromX, fromY, toX, toY)) {
                map->hint();   //若消掉的是hint给出的一对,则再给一个hint
            }
            ui->resultLabel->setText("消除成功!");
            //设置玩家状态
            player[num]->addScore(score);
            if (num == 0) {
                ui->singleScore->setText(QString::number(player[0]->getScore()));
            } else {
                ui->doubleScore->setText(QString::number(player[1]->getScore()));
            }
            //判断是否游戏结束
            if (map->checkFinish()) {
                timer->stop();
                QMessageBox::information(this, tr("游戏提示"), tr("方块消除成功,游戏结束!"));
                on_clearButton_clicked();
                started = false;
                paused = false;
                return;
            }
            if (!map->checkSolvable()) {
                timer->stop();
                QMessageBox::information(this, tr("游戏提示"), tr("当前地图不可解,游戏结束!"));
                started = false;
                paused = false;
            }
        } else {
            qDebug() << "QLinkWindow::checkCollide, setBoxStatus not_selected" << fromX << " " << fromY << " " << toX
                     << " " << toY;
            map->setBoxStatus(fromX, fromY, Constant::BoxStatus::NOT_SELECTED);
            map->setBoxStatus(toX, toY, Constant::BoxStatus::NOT_SELECTED);
            ui->resultLabel->setText("不可消除!");
        }
        selected[num].clear();
    }
    //双人模式时,可能存在两个玩家各选中一个并只剩这两个方格的情况,因此特判
    if(map->remainNumber()==0) {
        timer->stop();
        QMessageBox::information(this, tr("游戏提示"), tr("当前地图不可解,游戏结束!"));
        started = false;
        paused = false;
        return;
    }
}


void QLinkWindow::checkCollideWithProp(int num)
{
    if (num < 0 || num >= 2) return;
    double posX = player[num]->getX();
    double posY = player[num]->getY();
    for (int i = 0; i < 3; i++) {
        if (!prop[i]) continue;
        if (prop[i]->checkCollide(posX, posY)) {
            if (prop[i]->getType() == Constant::PropType::ADD_TIME) {
                remainTime += Constant::addCountdown;
            } else if (prop[i]->getType() == Constant::SHUFFLE) {
                //地图重排后,不保留原来选中的
                for (int i = 0; i <= 1; i++) {
                    for (int j = 0; j < (int) selected[i].size(); j++) {
                        map->setBoxStatus(selected[i][j].first, selected[i][j].second, Constant::NOT_SELECTED);
                    }
                    selected[i].clear();
                }
                map->shuffle();
            } else if (prop[i]->getType() == Constant::HINT) {
                if (!hintTime) {
                    map->hint(); //之前没有hint,调用hint方法,给一对hint
                }
                hintTime = Constant::hintTime; //重置hint道具生效时间
            }
            prop[i]->hide();
            prop[i]->generate();
            checkPropDistance(i);
            prop[i]->show();
        }
    }
}

void QLinkWindow::saveToFile()
{
    if (!this->started) return;
    QString filename = QFileDialog::getOpenFileName(this, tr("打开JSON文件"), "", tr("JSON Files(*.json);All Files(*.*)"));
    if (!filename.isNull()) {
        qDebug() << "QLinkWindow::saveTo " << filename;
    } else {
        return;
    }
    QFile file(filename);
    file.open(QFile::WriteOnly);

    QJsonObject json;
    json.insert("mode", mode);
    json.insert("remainTime", remainTime);
    json.insert("hintTime", hintTime);
    for (int i = 0; i < 3; i++) {
        json.insert("prop_" + QString::number(i), prop[i]->convertToJson());
    }
    if (player[0] != nullptr) {
        json.insert("player_0", player[0]->convertToJson());
    }
    if (player[1] != nullptr) {
        json.insert("player_1", player[1]->convertToJson());
    }
    if (map != nullptr) {
        json.insert("map", map->convertToJson());
    }
    for(int i=0;i<2;i++) {
        int tmp=selected[i].size();
        if(tmp<1) continue;
        json.insert("selected_"+QString::number(i)+"_x",selected[i][0].first);
        json.insert("selected_"+QString::number(i)+"_y",selected[i][0].second);
    }
    QJsonDocument jsonDoc;
    jsonDoc.setObject(json);

    file.write(jsonDoc.toJson());
    file.close();
    QMessageBox::information(this, tr("游戏提示"), tr("写入文件成功!"));
}


bool QLinkWindow::recoverFromFile()
{
    if (this->started) return false;
    QString filename = QFileDialog::getOpenFileName(this, tr("打开JSON文件"), "", tr("JSON Files(*.json);All Files(*.*)"));
    if (!filename.isNull()) {
        qDebug() << "QLinkWindow::recoverFrom " << filename;
    } else {
        return false;
    }
    QFile file(filename);
    file.open(QFile::ReadOnly);
    QJsonParseError jsonParserError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(file.readAll(), &jsonParserError);
    if (jsonDoc.isNull() || jsonParserError.error != QJsonParseError::NoError || !jsonDoc.isObject()) {
        return false;
    }

    QJsonObject object = jsonDoc.object();
    QJsonValue value = object.value("mode");
    if (value.isDouble()) {
        mode = (Constant::MODE) value.toVariant().toInt();
    } else {
        return false;
    }

    value = object.value("remainTime");
    if (value.isDouble()) {
        remainTime = value.toVariant().toInt();
    } else {
        return false;
    }

    value = object.value("hintTime");
    if (value.isDouble()) {
        hintTime = value.toVariant().toInt();
    }

    for (int i = 0; i < 3; i++) {
        value = object.value("prop_" + QString::number(i));
        if (value.isObject()) {
            if (!prop[i]->recoverFromJson(value.toObject())) {
                return false;
            }
        }
    }

    value = object.value("player_0");
    if (value.isObject()) {
        if (!player[0]->recoverFromJson(value.toObject())) {
            return false;
        }
    }

    value = object.value("player_1");
    if (value.isObject()) {
        if (!player[1]->recoverFromJson(value.toObject())) {
            return false;
        }
    }

    value = object.value("map");
    if (value.isObject()) {
        if (!map->recoverFromJson(value.toObject())) {
            return false;
        }
    } else {
        return false;
    }

    for(int i=0;i<2;i++) {
        selected[i].clear();
        QJsonValue value1=object.value("selected_"+QString::number(i)+"_x");
        QJsonValue value2=object.value("selected_"+QString::number(i)+"_y");
        if(value1.isDouble() && value2.isDouble()) {
            selected[i].push_back(std::make_pair(value1.toInt(),value2.toInt()));
            if(i==0) {
                map->setBoxStatus(value1.toInt(),value2.toInt(),Constant::BoxStatus::SELECTED_BY_FIRST);
            }
            else {
                map->setBoxStatus(value1.toInt(),value2.toInt(),Constant::BoxStatus::SELECTED_BY_SECOND);
            }
        }
    }

    qDebug() << "QLinkWindow::recoverfromFile success";
    recovered = true;  //成功恢复,将recovered设为true,同时暂停游戏

    init(mode);
    ui->gridFrame->setLayout(map->getLayout());
    player[0]->show();
    if (mode == Constant::MODE::DOUBLE_MODE) {
        player[1]->show();
    }

    for (int i = 0; i < 3; i++) {
        if (prop[i]) {
            prop[i]->show();
        }
    }

    if(hintTime>0 && map) map->hint();

    started = true;
    paused = true;
    ui->pauseButton->setText("继续 (Continue)");
    if(!map->checkSolvable()) {
        QMessageBox::information(this, tr("游戏提示"), tr("地图不可解，游戏结束!"));
        started=false;
        paused=false;
    }
    return true;
}

void QLinkWindow::on_clearButton_clicked()
{
//    if (started && !paused) {
//        QMessageBox::information(this, tr("游戏提示"), tr("请先暂停游戏,再清空地图!"));
//        return;
//    }
    if (player[0]) {
        player[0]->hide();
    }
    if (player[1]) {
        player[1]->hide();
    }
    for (int i = 0; i < 3; i++) {
        if (prop[i]) {
            prop[i]->hide();
        }
    }
    if (timer) {
        timer->stop();
    }
    if (map) {
        map->clear();
    }

    ui->clock->display("");
    ui->singleScore->setText("0");
    ui->resultLabel->setText("");
    if (mode == Constant::DOUBLE_MODE) {
        ui->doubleScore->setText("0");
    }
    scene->clear();
    started = paused = false;
    ui->pauseButton->setText("暂停 (Pause)");
}

void QLinkWindow::clear()
{
    on_clearButton_clicked();
}

void QLinkWindow::checkPropDistance(int num)
{
    if (!player[0] || !player[1] || num > 3 || !prop[0] || !prop[1] || !prop[2]) {
        return;
    }
    bool f = true;
    for (int i = 1; i <= 100; i++) {
        f = true;
        for (int j = 0; j < 2; j++) {
            double dis1 = (prop[num]->getX() - player[j]->getX());
            double dis2 = (prop[num]->getY() - player[j]->getY());
            if (dis1 * dis1 + dis2 * dis2 <= Constant::minDistance) {
                prop[num]->generate();
                f = false;
            }
        }
        for (int j = 0; j < 3; j++) {
            if (num == j) continue;
            double dis1 = (prop[num]->getX() - prop[j]->getX());
            double dis2 = (prop[num]->getY() - prop[j]->getY());
            if (dis1 * dis1 + dis2 * dis2 <= Constant::minDistance) {
                prop[num]->generate();
                f = false;
            }
        }
        if (f) break;
    }
}

void QLinkWindow::checkPlayerDistance()
{
    if (!player[0] || !player[1]) {
        return;
    }
    for (int i = 1; i <= 100; i++) {
        double dis1 = (player[1]->getX() - player[0]->getX());
        double dis2 = (player[1]->getY() - player[0]->getY());
        if (dis1 * dis1 + dis2 * dis2 <= Constant::minDistance) {
            qDebug() << "QLinkWindow::checkPlayerDistance" << player[1]->getX() << " " << player[0]->getX() << " "
                     << player[1]->getY() << " " << player[0]->getY();
            player[1]->generate();
        } else {
            break;
        }
    }
}

void QLinkWindow::drawLine()
{
    QVector <QLineF> path = map->getPath();
    int size = path.size();
    for (int i = 0; i < size; i++) {
        scene->addLine(path[i], pen);
    }
}



void QLinkWindow::on_heightBox_valueChanged(int arg1)
{
    int val=ui->heightBox->value();
    ui->widthBox->setValue(val);
}


void QLinkWindow::on_widthBox_valueChanged(int arg1)
{
    int val=ui->widthBox->value();
    ui->heightBox->setValue(val);
}

