//
// Created by 黄喆敏 on 2021/11/1.
//

#include "FileUtils.h"
#include <QFileDialog>
#include <QWidget>
#include <iostream>
#include <QDebug>
#define debug 0

void FileUtils::loadFile(const QString &dir) {

}

QString FileUtils::openFileDialog(QWidget * widget) {
    QString filename=QFileDialog::getOpenFileName(widget, "选择一个json文件", "./", "JSON(*.json);;ALL(*.*)");
    if(debug) {
        qDebug()<<"FileUtils: openFileDialog:"<<filename;
    }
}