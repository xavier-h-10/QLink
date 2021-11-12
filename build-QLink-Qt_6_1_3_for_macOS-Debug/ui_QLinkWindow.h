/********************************************************************************
** Form generated from reading UI file 'QLinkWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QLINKWINDOW_H
#define UI_QLINKWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_QLinkWindow
{
public:
    QAction *openAction;
    QWidget *centralwidget;
    QLabel *modeTitle;
    QWidget *layoutWidget_2;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *startButton;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pauseButton;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *saveButton;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *loadButton;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *returnButton;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *quitButton;
    QWidget *gridLayoutWidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_1;
    QSplitter *splitter_2;
    QLabel *label;
    QLCDNumber *clock;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QLabel *singleLabel;
    QSpacerItem *horizontalSpacer_1;
    QLabel *singleScore;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_3;
    QLabel *doubleLabel;
    QSpacerItem *horizontalSpacer_2;
    QLabel *doubleScore;
    QSpacerItem *horizontalSpacer_5;
    QLabel *resultLabel;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QSpinBox *heightBox;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_4;
    QSpinBox *weightBox;
    QSpacerItem *horizontalSpacer_12;
    QFrame *line;
    QStatusBar *statusbar;
    QMenuBar *menubar;
    QMenu *menu;

    void setupUi(QMainWindow *QLinkWindow)
    {
        if (QLinkWindow->objectName().isEmpty())
            QLinkWindow->setObjectName(QString::fromUtf8("QLinkWindow"));
        QLinkWindow->resize(800, 600);
        openAction = new QAction(QLinkWindow);
        openAction->setObjectName(QString::fromUtf8("openAction"));
        centralwidget = new QWidget(QLinkWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        modeTitle = new QLabel(centralwidget);
        modeTitle->setObjectName(QString::fromUtf8("modeTitle"));
        modeTitle->setGeometry(QRect(330, 10, 111, 31));
        QFont font;
        font.setPointSize(24);
        modeTitle->setFont(font);
        layoutWidget_2 = new QWidget(centralwidget);
        layoutWidget_2->setObjectName(QString::fromUtf8("layoutWidget_2"));
        layoutWidget_2->setGeometry(QRect(10, 510, 769, 32));
        horizontalLayout_4 = new QHBoxLayout(layoutWidget_2);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        startButton = new QPushButton(layoutWidget_2);
        startButton->setObjectName(QString::fromUtf8("startButton"));

        horizontalLayout_4->addWidget(startButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_6);

        pauseButton = new QPushButton(layoutWidget_2);
        pauseButton->setObjectName(QString::fromUtf8("pauseButton"));

        horizontalLayout_4->addWidget(pauseButton);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_7);

        saveButton = new QPushButton(layoutWidget_2);
        saveButton->setObjectName(QString::fromUtf8("saveButton"));

        horizontalLayout_4->addWidget(saveButton);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_8);

        loadButton = new QPushButton(layoutWidget_2);
        loadButton->setObjectName(QString::fromUtf8("loadButton"));

        horizontalLayout_4->addWidget(loadButton);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_9);

        returnButton = new QPushButton(layoutWidget_2);
        returnButton->setObjectName(QString::fromUtf8("returnButton"));

        horizontalLayout_4->addWidget(returnButton);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_10);

        quitButton = new QPushButton(layoutWidget_2);
        quitButton->setObjectName(QString::fromUtf8("quitButton"));

        horizontalLayout_4->addWidget(quitButton);

        gridLayoutWidget = new QWidget(centralwidget);
        gridLayoutWidget->setObjectName(QString::fromUtf8("gridLayoutWidget"));
        gridLayoutWidget->setGeometry(QRect(30, 160, 611, 331));
        gridLayout = new QGridLayout(gridLayoutWidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gridLayout->setContentsMargins(0, 0, 0, 0);
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(30, 50, 741, 94));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        horizontalLayout_1 = new QHBoxLayout();
        horizontalLayout_1->setObjectName(QString::fromUtf8("horizontalLayout_1"));
        splitter_2 = new QSplitter(widget);
        splitter_2->setObjectName(QString::fromUtf8("splitter_2"));
        splitter_2->setOrientation(Qt::Horizontal);
        label = new QLabel(splitter_2);
        label->setObjectName(QString::fromUtf8("label"));
        QFont font1;
        font1.setPointSize(20);
        label->setFont(font1);
        splitter_2->addWidget(label);
        clock = new QLCDNumber(splitter_2);
        clock->setObjectName(QString::fromUtf8("clock"));
        clock->setDigitCount(5);
        splitter_2->addWidget(clock);

        horizontalLayout_1->addWidget(splitter_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        singleLabel = new QLabel(widget);
        singleLabel->setObjectName(QString::fromUtf8("singleLabel"));
        singleLabel->setFont(font1);

        horizontalLayout_2->addWidget(singleLabel);

        horizontalSpacer_1 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_1);

        singleScore = new QLabel(widget);
        singleScore->setObjectName(QString::fromUtf8("singleScore"));
        singleScore->setFont(font);

        horizontalLayout_2->addWidget(singleScore);


        horizontalLayout_1->addLayout(horizontalLayout_2);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer_4);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        doubleLabel = new QLabel(widget);
        doubleLabel->setObjectName(QString::fromUtf8("doubleLabel"));
        doubleLabel->setFont(font1);

        horizontalLayout_3->addWidget(doubleLabel);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        doubleScore = new QLabel(widget);
        doubleScore->setObjectName(QString::fromUtf8("doubleScore"));
        doubleScore->setFont(font);

        horizontalLayout_3->addWidget(doubleScore);


        horizontalLayout_1->addLayout(horizontalLayout_3);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_1->addItem(horizontalSpacer_5);

        resultLabel = new QLabel(widget);
        resultLabel->setObjectName(QString::fromUtf8("resultLabel"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(resultLabel->sizePolicy().hasHeightForWidth());
        resultLabel->setSizePolicy(sizePolicy);
        resultLabel->setFont(font);

        horizontalLayout_1->addWidget(resultLabel);


        verticalLayout->addLayout(horizontalLayout_1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setFont(font1);

        horizontalLayout->addWidget(label_2);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        heightBox = new QSpinBox(widget);
        heightBox->setObjectName(QString::fromUtf8("heightBox"));

        horizontalLayout->addWidget(heightBox);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_11);

        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout->addWidget(label_4);

        weightBox = new QSpinBox(widget);
        weightBox->setObjectName(QString::fromUtf8("weightBox"));

        horizontalLayout->addWidget(weightBox);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_12);


        verticalLayout->addLayout(horizontalLayout);

        line = new QFrame(widget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        QLinkWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(QLinkWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QLinkWindow->setStatusBar(statusbar);
        menubar = new QMenuBar(QLinkWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 24));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        QLinkWindow->setMenuBar(menubar);

        menubar->addAction(menu->menuAction());
        menu->addAction(openAction);

        retranslateUi(QLinkWindow);

        QMetaObject::connectSlotsByName(QLinkWindow);
    } // setupUi

    void retranslateUi(QMainWindow *QLinkWindow)
    {
        QLinkWindow->setWindowTitle(QCoreApplication::translate("QLinkWindow", "\350\277\236\350\277\236\347\234\213", nullptr));
        openAction->setText(QCoreApplication::translate("QLinkWindow", "\346\211\223\345\274\200", nullptr));
#if QT_CONFIG(shortcut)
        openAction->setShortcut(QCoreApplication::translate("QLinkWindow", "Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        modeTitle->setText(QCoreApplication::translate("QLinkWindow", "\345\215\225\344\272\272\346\250\241\345\274\217", nullptr));
        startButton->setText(QCoreApplication::translate("QLinkWindow", "\345\274\200\345\247\213 (Start)", nullptr));
        pauseButton->setText(QCoreApplication::translate("QLinkWindow", "\346\232\202\345\201\234 (Pause)", nullptr));
        saveButton->setText(QCoreApplication::translate("QLinkWindow", "\345\255\230\346\241\243 (Save)", nullptr));
        loadButton->setText(QCoreApplication::translate("QLinkWindow", "\350\275\275\345\205\245 (Load)", nullptr));
        returnButton->setText(QCoreApplication::translate("QLinkWindow", "\350\277\224\345\233\236 (Return)", nullptr));
        quitButton->setText(QCoreApplication::translate("QLinkWindow", "\351\200\200\345\207\272 (Quit)", nullptr));
        label->setText(QCoreApplication::translate("QLinkWindow", "\345\200\222\350\256\241\346\227\266", nullptr));
        singleLabel->setText(QCoreApplication::translate("QLinkWindow", "\345\210\206\346\225\260", nullptr));
        singleScore->setText(QCoreApplication::translate("QLinkWindow", "0", nullptr));
        doubleLabel->setText(QCoreApplication::translate("QLinkWindow", "\345\210\206\346\225\260", nullptr));
        doubleScore->setText(QCoreApplication::translate("QLinkWindow", "0", nullptr));
        resultLabel->setText(QString());
        label_2->setText(QCoreApplication::translate("QLinkWindow", "\345\234\260\345\233\276\345\244\247\345\260\217", nullptr));
        label_3->setText(QCoreApplication::translate("QLinkWindow", "\351\225\277", nullptr));
        label_4->setText(QCoreApplication::translate("QLinkWindow", "\345\256\275", nullptr));
        menu->setTitle(QCoreApplication::translate("QLinkWindow", "\346\226\207\344\273\266", nullptr));
    } // retranslateUi

};

namespace Ui {
    class QLinkWindow: public Ui_QLinkWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QLINKWINDOW_H
