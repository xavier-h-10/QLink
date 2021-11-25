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

QLinkWindow::QLinkWindow(QWidget *parent) :
        QMainWindow(parent), ui(new Ui::QLinkWindow) {
    ui->setupUi(this);
    setWindowTitle(tr("连连看"));
    ui->heightBox->setMinimum(Constant::mapMin);
    ui->heightBox->setMaximum(Constant::mapMax);
    ui->widthBox->setMinimum(Constant::mapMin);
    ui->widthBox->setMaximum(Constant::mapMax);

    mode = Constant::MODE::SINGLE_MODE;

    timer = new QTimer(this);

    connect(timer, SIGNAL(timeout()), this, SLOT(updateTime()));

    this->started = false;
    this->paused = false;
    this->recovered=false;

    player[0] = new QPlayer(0, ui->singlePlayer);
    player[1] = new QPlayer(1, ui->doublePlayer);
    ui->heightBox->setValue(Constant::mapDefault);
    ui->widthBox->setValue(Constant::mapDefault);

    prop = new QLinkProp(ui->prop);

    map = new QLinkMap();
}

QLinkWindow::~QLinkWindow() {
    delete ui;
    ui = nullptr;
    delete map;
    map = nullptr;
}

void QLinkWindow::init(Constant::MODE mode) {
    this->mode = mode;

    QPalette pe;
    pe.setColor(QPalette::WindowText, Qt::red);
    ui->resultLabel->setText("");
    ui->resultLabel->setPalette(pe);
    ui->singleScore->setPalette(pe);
    ui->doubleScore->setPalette(pe);
    ui->clock->display("00:00");
    ui->clock->setSegmentStyle(QLCDNumber::Flat);

    if (mode == Constant::MODE::SINGLE_MODE) {
        ui->modeTitle->setText("单人模式");
        ui->singleLabel->setText("玩家分数:");
        ui->singleScore->setText("0");
        ui->doubleLabel->setText("");
        ui->doubleScore->setText("");
    } else {
        ui->modeTitle->setText("双人模式");
        ui->singleLabel->setText("玩家一分数:");
        ui->singleScore->setText("0");
        ui->doubleLabel->setText("玩家二分数:");
        ui->doubleScore->setText("0");
    }
    ui->pauseButton->setText("暂停 (Pause)");

    this->started = false;
    this->paused = false;

    if(!recovered) {
        this->remainTime = Constant::countdown;
        this->hintTime=0;
    }

    setFocusPolicy(Qt::StrongFocus); //每次进入界面,需要重新focus

    h = ui->heightBox->value();
    w = ui->widthBox->value();

    if(!recovered) {
        selected[0].clear();
        selected[1].clear();
    }

    recovered=false;

}

void QLinkWindow::updateTime() {
    qDebug() << "QLinkWindow::updateTime called start=" << this->started;
    if (!this->started) {
        timer->stop();
    }
    if(hintTime) {
        hintTime--;
    }
    remainTime--;
    const QString &nowTime = convertTime(remainTime);
    qDebug() << "nowTime=" << nowTime;
    ui->clock->display(nowTime);

    if (remainTime <= 0) {
        timer->stop();
        QMessageBox::information(this, tr("游戏提示"), tr("倒计时完成，游戏结束!"));
        ui->pauseButton->setText("暂停 (Pause)");
        this->started = false;
    }
    qDebug() << "QLinkWindow::updateTime ended";
}

void QLinkWindow::on_startButton_clicked() {
    if (this->started) {
        QMessageBox::information(this, tr("游戏提示"), tr("游戏已经开始!"));
        return;
    }

    h = ui->heightBox->value();
    w = ui->widthBox->value();
    if((h*w)%2==1) {
        QMessageBox::information(this,tr("游戏提示"),tr("地图大小为奇数,无法生成地图!"));
        return;
    }

    on_clearButton_clicked(); //先调用清空方法

    init(mode);

    map->generate(h,w);

    player[0]->generate();
    player[1]->generate();
    prop->generate();

    ui->gridFrame->setLayout(map->getLayout());
    updateTime();
    this->started = true;

    player[0]->show();
    if (mode == Constant::MODE::DOUBLE_MODE) {
        player[1]->show();
    }

    if (mode == Constant::SINGLE_MODE) {
        prop->show();
    }
    timer->start(1000);
}


void QLinkWindow::on_pauseButton_clicked() {
    if (!this->started) {
        QMessageBox::information(this, tr("游戏提示"), tr("游戏尚未开始!"));
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
void QLinkWindow::on_saveButton_clicked() {
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

void QLinkWindow::on_loadButton_clicked() {
    if (this->started && !this->paused) {
        QMessageBox::information(this, tr("游戏提示"), tr("请先暂停游戏，再载入存档!"));
        return;
    }
    if(!recoverFromFile()) {
        QMessageBox::information(this, tr("游戏提示"), tr("恢复存档失败!"));
    }

}


void QLinkWindow::on_returnButton_clicked() {
    timer->stop();
    started=false;
    paused=false;
    on_clearButton_clicked();
    emit stopGame();
}

void QLinkWindow::on_quitButton_clicked() {
    timer->stop();
    emit quitGame();
}


QString QLinkWindow::convertTime(int time) {
    QString ans = "";
    int min = time / 60;
    int sec = time % 60;
    ans = ans + "0" + QString::number(min) + ":";
    if (sec < 10) ans += "0";
    ans += QString::number(sec);
    return ans;
}

void QLinkWindow::keyPressEvent(QKeyEvent *event) {
    qDebug() << "QLinkWindow::keyPressEvent called";
    if (started && !paused) {
//        QSet<int> pressedKeys;
//        pressedKeys+=event->key();
//        if(pressedKeys.contains(Qt::Key_W) && pressedKeys.contains(Qt::Key_U)) {
//            qDebug()<<"check multiple keys!!!!";
//        }
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
        checkCollideWithProp();
    }
}

void QLinkWindow::checkCollideWithMap(int num, int dx, int dy) {
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

void QLinkWindow::handleCollide(int num) {
    double posX = player[num]->getX();
    double posY = player[num]->getY();
    int nowy = (posX - Constant::mapMinX) / ((Constant::mapMaxX - Constant::mapMinX) / h);
    int nowx = (posY - Constant::mapMinY) / ((Constant::mapMaxY - Constant::mapMinY) / w);
    ui->resultLabel->setText("");

    Constant::BoxStatus status = map->getBoxStatus(nowx, nowy);
    if (status == Constant::BoxStatus::NOT_SELECTED) {
        qDebug() << "QLinkWindow::checkCollide, setBoxStatus" << nowx << " nowy=" << nowy;
        if(num==0) {
            map->setBoxStatus(nowx, nowy, Constant::BoxStatus::SELECTED_BY_FIRST);
        }
        else {
            map->setBoxStatus(nowx,nowy,Constant::BoxStatus::SELECTED_BY_SECOND);
        }
        selected[num].push_back(std::make_pair(nowx, nowy));
    }

    int size = selected[num].size();
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

            if(hintTime && map->isHint(fromX,fromY,toX,toY)) {
                map->hint();   //若消掉的是hint给出的一对,则再给一个hint
            }

            ui->resultLabel->setText("消除成功!");
            player[num]->addScore(score);
            if (num == 0) {
                ui->singleScore->setText(QString::number(player[0]->getScore()));
            } else {
                ui->doubleScore->setText(QString::number(player[1]->getScore()));
            }
            if(map->checkFinish()) {
                timer->stop();
                QMessageBox::information(this,tr("游戏提示"),tr("方块消除成功,游戏结束!"));
                started = false;
                paused= false;
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
}


void QLinkWindow::checkCollideWithProp() {
    if (mode == Constant::DOUBLE_MODE) return;
    double posX = player[0]->getX();
    double posY = player[0]->getY();
    if (prop->checkCollide(posX, posY)) {
        if (prop->getType() == Constant::PropType::ADD_TIME) {
            remainTime += Constant::addCountdown;
        } else if (prop->getType() == Constant::SHUFFLE) {
            //地图重排后,不保留原来选中的
            for(int i=0;i<=1;i++) {
                for(int j=0;j<selected[i].size();j++) {
                    map->setBoxStatus(selected[i][j].first,selected[i][j].second,Constant::NOT_SELECTED);
                }
                selected[i].clear();
            }
            map->shuffle();
        } else if (prop->getType() == Constant::HINT) {
            if(!hintTime) {
                map->hint(); //之前没有hint,调用hint方法,给一对hint
            }
            hintTime=Constant::hintTime; //重置hint道具生效时间
        }
        prop->hide();
        prop->generate();
        prop->show();
    }
}


void QLinkWindow::paintEvent(QPaintEvent *) {

}


void QLinkWindow::saveToFile() {
    if(!this->started) return;
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
    json.insert("hintTime",hintTime);
    if(mode==Constant::SINGLE_MODE) {
        json.insert("prop",prop->convertToJson());
    }
    if(player[0]!=nullptr) {
        json.insert("player_0",player[0]->convertToJson());
    }
    if(player[1]!=nullptr) {
        json.insert("player_1",player[1]->convertToJson());
    }
    if(map!=nullptr) {
        json.insert("map",map->convertToJson());
    }
//    for(int i=0;i<2;i++) {
//        QString str="player"+QString::number(i);
//        int tmp=selected[i].size();
//        for(int j=0;j<tmp;j++) {
//            json.insert(str+"_"+j+".first",selected[i][j].first);
//            json.insert(str+"_"+j+".second",selected[i][j].second);
//        }
//    }

    QJsonDocument jsonDoc;
    jsonDoc.setObject(json);

    file.write(jsonDoc.toJson());
    file.close();
    QMessageBox::information(this, tr("游戏提示"), tr("写入文件成功!"));
}


bool QLinkWindow::recoverFromFile() {
    if(this->started) return false;
    QString filename = QFileDialog::getOpenFileName(this, tr("打开JSON文件"), "", tr("JSON Files(*.json);All Files(*.*)"));
    if (!filename.isNull()) {
        qDebug() << "QLinkWindow::recoverFrom " << filename;
    } else {
        return false;
    }
    QFile file(filename);
    file.open(QFile::ReadOnly);
    QJsonParseError jsonParserError;
    QJsonDocument jsonDoc= QJsonDocument::fromJson(file.readAll(),&jsonParserError);
    if(jsonDoc.isNull() || jsonParserError.error!=QJsonParseError::NoError || !jsonDoc.isObject()) {
        return false;
    }

    QJsonObject object=jsonDoc.object();
    QJsonValue value=object.value("mode");
    if(value.isDouble()) {
        mode=(Constant::MODE) value.toVariant().toInt();
    }
    else {
        return false;
    }

    value=object.value("remainTime");
    if(value.isDouble()) {
        remainTime=value.toVariant().toInt();
    }
    else {
        return false;
    }

    value=object.value("hintTime");
    if(value.isDouble()) {
        hintTime=value.toVariant().toInt();
    }

    value=object.value("prop");
    if(value.isObject()) {
        if(!prop->recoverFromJson(value.toObject())) {
            return false;
        }
    }

    value=object.value("player_0");
    if(value.isObject()) {
        if(!player[0]->recoverFromJson(value.toObject())) {
            return false;
        }
    }

    value=object.value("player_1");
    if(value.isObject()) {
        if(!player[1]->recoverFromJson(value.toObject())) {
            return false;
        }
    }

    value=object.value("map");
    if(value.isObject()) {
        if(!map->recoverFromJson(value.toObject())) {
            return false;
        }
    }
    else {
        return false;
    }

    recovered=true;  //成功恢复,将recovered设为true,同时暂停游戏
    started=false;
    paused=true;
    ui->pauseButton->setText("继续 (Continue)");
    return true;
}

void QLinkWindow::on_clearButton_clicked()
{
    if(started && !paused) {
        QMessageBox::information(this, tr("游戏提示"), tr("请先暂停游戏,再清空地图!"));
        return;
    }
    if(player[0]) {
        player[0]->hide();
    }
    if(player[1]) {
        player[1]->hide();
    }
    if(prop) {
        prop->hide();
    }
    if(timer) {
        timer->stop();
    }
    if(map) {
        map->clear();
    }

    ui->clock->display("");
    ui->singleScore->setText("0");
    if(mode==Constant::DOUBLE_MODE) {
        ui->doubleScore->setText("0");
    }

    started=paused=false;
    ui->pauseButton->setText("暂停 (Pause)");
}

