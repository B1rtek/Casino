/********************************************************************************
** Form generated from reading UI file 'TexasHoldemTest.ui'
**
** Created by: Qt User Interface Compiler version 5.15.4
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TEXASHOLDEMTEST_H
#define UI_TEXASHOLDEMTEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QListWidget *playerBalanceBetList;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QListWidget *tableCardsList;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *foldButton;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *callButton;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *raiseButton;
    QLineEdit *raiseLineEdit;
    QHBoxLayout *horizontalLayout;
    QPushButton *advanceTimeButton;
    QLineEdit *advanceTimeLineEdit;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 600);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_3 = new QVBoxLayout(centralwidget);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        playerBalanceBetList = new QListWidget(centralwidget);
        playerBalanceBetList->setObjectName(QString::fromUtf8("playerBalanceBetList"));

        verticalLayout->addWidget(playerBalanceBetList);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2, 0, Qt::AlignHCenter);

        tableCardsList = new QListWidget(centralwidget);
        tableCardsList->setObjectName(QString::fromUtf8("tableCardsList"));

        verticalLayout_2->addWidget(tableCardsList);


        horizontalLayout_4->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        foldButton = new QPushButton(centralwidget);
        foldButton->setObjectName(QString::fromUtf8("foldButton"));

        horizontalLayout_5->addWidget(foldButton);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        callButton = new QPushButton(centralwidget);
        callButton->setObjectName(QString::fromUtf8("callButton"));

        horizontalLayout_5->addWidget(callButton);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        raiseButton = new QPushButton(centralwidget);
        raiseButton->setObjectName(QString::fromUtf8("raiseButton"));

        horizontalLayout_2->addWidget(raiseButton);

        raiseLineEdit = new QLineEdit(centralwidget);
        raiseLineEdit->setObjectName(QString::fromUtf8("raiseLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(raiseLineEdit->sizePolicy().hasHeightForWidth());
        raiseLineEdit->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(raiseLineEdit);


        horizontalLayout_5->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_5);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        advanceTimeButton = new QPushButton(centralwidget);
        advanceTimeButton->setObjectName(QString::fromUtf8("advanceTimeButton"));

        horizontalLayout->addWidget(advanceTimeButton);

        advanceTimeLineEdit = new QLineEdit(centralwidget);
        advanceTimeLineEdit->setObjectName(QString::fromUtf8("advanceTimeLineEdit"));
        sizePolicy.setHeightForWidth(advanceTimeLineEdit->sizePolicy().hasHeightForWidth());
        advanceTimeLineEdit->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(advanceTimeLineEdit);

        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout->addWidget(label_3);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout_3->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 27));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Player, balance, bet", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Table", nullptr));
        foldButton->setText(QCoreApplication::translate("MainWindow", "Fold", nullptr));
        callButton->setText(QCoreApplication::translate("MainWindow", "Check/Call", nullptr));
        raiseButton->setText(QCoreApplication::translate("MainWindow", "Raise", nullptr));
        advanceTimeButton->setText(QCoreApplication::translate("MainWindow", "Advance Time", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "%3: 0 = fold, 1 = call, 2 = raise(2)", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TEXASHOLDEMTEST_H
