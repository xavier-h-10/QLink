//
// Created by 黄喆敏 on 2021/11/1.
//

#ifndef QLINK_QLINKBOX_H
#define QLINK_QLINKBOX_H

#include <QImage>
#include <QLabel>


class QLinkBox {
public:
    QLinkBox(int w,int h,int type);
    ~QLinkBox();

private:
    QImage icon;
    QLabel *label;
    int w;
    int h;
    int type;

};


#endif //QLINK_QLINKBOX_H
