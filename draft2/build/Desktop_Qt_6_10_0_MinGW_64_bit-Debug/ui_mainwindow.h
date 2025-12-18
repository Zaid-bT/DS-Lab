/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.10.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "mazewidget.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_5;
    QStackedWidget *stackedWidget;
    QWidget *page1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label;
    QPushButton *startButton;
    QSpacerItem *verticalSpacer_3;
    QWidget *page4;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QPushButton *easyButton;
    QPushButton *medButton;
    QPushButton *hardButton;
    QPushButton *impButton;
    QSpacerItem *verticalSpacer_2;
    QWidget *page_2;
    QVBoxLayout *verticalLayout_3;
    MazeWidget *mazeWidget;
    QWidget *page3;
    QVBoxLayout *verticalLayout_4;
    MazeWidget *optimalPath;
    QMenuBar *menubar;
    QMenu *menumenu_bar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        verticalLayout_5 = new QVBoxLayout(centralwidget);
        verticalLayout_5->setObjectName("verticalLayout_5");
        stackedWidget = new QStackedWidget(centralwidget);
        stackedWidget->setObjectName("stackedWidget");
        page1 = new QWidget();
        page1->setObjectName("page1");
        verticalLayout_2 = new QVBoxLayout(page1);
        verticalLayout_2->setObjectName("verticalLayout_2");
        label = new QLabel(page1);
        label->setObjectName("label");
        label->setAlignment(Qt::AlignmentFlag::AlignCenter);

        verticalLayout_2->addWidget(label);

        startButton = new QPushButton(page1);
        startButton->setObjectName("startButton");

        verticalLayout_2->addWidget(startButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_3);

        stackedWidget->addWidget(page1);
        startButton->raise();
        label->raise();
        page4 = new QWidget();
        page4->setObjectName("page4");
        verticalLayout = new QVBoxLayout(page4);
        verticalLayout->setObjectName("verticalLayout");
        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        easyButton = new QPushButton(page4);
        easyButton->setObjectName("easyButton");

        verticalLayout->addWidget(easyButton);

        medButton = new QPushButton(page4);
        medButton->setObjectName("medButton");

        verticalLayout->addWidget(medButton);

        hardButton = new QPushButton(page4);
        hardButton->setObjectName("hardButton");

        verticalLayout->addWidget(hardButton);

        impButton = new QPushButton(page4);
        impButton->setObjectName("impButton");

        verticalLayout->addWidget(impButton);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        stackedWidget->addWidget(page4);
        page_2 = new QWidget();
        page_2->setObjectName("page_2");
        verticalLayout_3 = new QVBoxLayout(page_2);
        verticalLayout_3->setObjectName("verticalLayout_3");
        mazeWidget = new MazeWidget(page_2);
        mazeWidget->setObjectName("mazeWidget");
        mazeWidget->setStyleSheet(QString::fromUtf8("background-color:yellow\n"
""));

        verticalLayout_3->addWidget(mazeWidget);

        stackedWidget->addWidget(page_2);
        page3 = new QWidget();
        page3->setObjectName("page3");
        verticalLayout_4 = new QVBoxLayout(page3);
        verticalLayout_4->setObjectName("verticalLayout_4");
        optimalPath = new MazeWidget(page3);
        optimalPath->setObjectName("optimalPath");
        optimalPath->setStyleSheet(QString::fromUtf8("background-color: \"green\""));

        verticalLayout_4->addWidget(optimalPath);

        stackedWidget->addWidget(page3);

        verticalLayout_5->addWidget(stackedWidget);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 800, 25));
        menumenu_bar = new QMenu(menubar);
        menumenu_bar->setObjectName("menumenu_bar");
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menumenu_bar->menuAction());

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "MAZE GAME", nullptr));
        startButton->setText(QCoreApplication::translate("MainWindow", "START", nullptr));
        easyButton->setText(QCoreApplication::translate("MainWindow", "EASY", nullptr));
        medButton->setText(QCoreApplication::translate("MainWindow", "MEDIUM", nullptr));
        hardButton->setText(QCoreApplication::translate("MainWindow", "HARD", nullptr));
        impButton->setText(QCoreApplication::translate("MainWindow", "IMPOSSIBLE", nullptr));
        menumenu_bar->setTitle(QCoreApplication::translate("MainWindow", "menu bar", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
