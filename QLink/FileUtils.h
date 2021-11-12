//
// Created by 黄喆敏 on 2021/11/1.
//

#ifndef QLINK_FILEUTILS_H
#define QLINK_FILEUTILS_H

#include <QString>
#include <QWidget>

class FileUtils {
    static void loadFile(const QString &dir);

    static QString openFileDialog(QWidget *widget);
};


#endif //QLINK_FILEUTILS_H
