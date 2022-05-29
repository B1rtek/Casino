/********************************************************************************
** Form generated from reading UI file 'RouletteTest.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ROULETTETEST_H
#define UI_ROULETTETEST_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
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
    QLabel *labelTime;
    QLabel *label;
    QListWidget *playerBalanceBetList;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelLastNumber;
    QLabel *label_2;
    QListWidget *percentagesList;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QGridLayout *gridLayout;
    QToolButton *toolButton_9;
    QToolButton *toolButton_14;
    QToolButton *toolButton_34;
    QToolButton *toolButton_32;
    QToolButton *toolButton_25;
    QToolButton *toolButton_2;
    QPushButton *betColumn2Button;
    QToolButton *toolButton_27;
    QToolButton *toolButton_28;
    QToolButton *toolButton_11;
    QPushButton *betTwelve3Button;
    QToolButton *toolButton_20;
    QToolButton *toolButton_17;
    QToolButton *toolButton_23;
    QToolButton *toolButton_3;
    QToolButton *toolButton_24;
    QToolButton *toolButton_7;
    QToolButton *toolButton_12;
    QToolButton *toolButton_30;
    QToolButton *toolButton_13;
    QToolButton *toolButton_37;
    QToolButton *toolButton_4;
    QToolButton *toolButton_10;
    QToolButton *toolButton_19;
    QToolButton *toolButton_33;
    QToolButton *toolButton_5;
    QToolButton *toolButton_31;
    QToolButton *toolButton_36;
    QToolButton *toolButton_15;
    QToolButton *toolButton_22;
    QToolButton *toolButton_26;
    QToolButton *toolButton_16;
    QToolButton *toolButton_1;
    QToolButton *toolButton_35;
    QToolButton *toolButton_18;
    QPushButton *betTwelve2Button;
    QToolButton *toolButton_21;
    QPushButton *betColumn1Button;
    QPushButton *betTwelve1Button;
    QToolButton *toolButton_6;
    QToolButton *toolButton_8;
    QToolButton *toolButton_29;
    QPushButton *betColumn3Button;
    QPushButton *betHalf1Button;
    QPushButton *betEvenodd1Button;
    QPushButton *betColor1Button;
    QPushButton *betColor2Button;
    QPushButton *betEvenodd2Button;
    QPushButton *betHalf2Button;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_3;
    QLineEdit *betLineEdit;
    QSpacerItem *horizontalSpacer_3;
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
        labelTime = new QLabel(centralwidget);
        labelTime->setObjectName(QString::fromUtf8("labelTime"));

        verticalLayout->addWidget(labelTime, 0, Qt::AlignHCenter);

        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout->addWidget(label, 0, Qt::AlignHCenter);

        playerBalanceBetList = new QListWidget(centralwidget);
        playerBalanceBetList->setObjectName(QString::fromUtf8("playerBalanceBetList"));

        verticalLayout->addWidget(playerBalanceBetList);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelLastNumber = new QLabel(centralwidget);
        labelLastNumber->setObjectName(QString::fromUtf8("labelLastNumber"));

        verticalLayout_2->addWidget(labelLastNumber, 0, Qt::AlignHCenter);

        label_2 = new QLabel(centralwidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_2->addWidget(label_2, 0, Qt::AlignHCenter);

        percentagesList = new QListWidget(centralwidget);
        percentagesList->setObjectName(QString::fromUtf8("percentagesList"));

        verticalLayout_2->addWidget(percentagesList);


        horizontalLayout_4->addLayout(verticalLayout_2);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        toolButton_9 = new QToolButton(centralwidget);
        toolButton_9->setObjectName(QString::fromUtf8("toolButton_9"));

        gridLayout->addWidget(toolButton_9, 1, 8, 1, 1, Qt::AlignHCenter);

        toolButton_14 = new QToolButton(centralwidget);
        toolButton_14->setObjectName(QString::fromUtf8("toolButton_14"));

        gridLayout->addWidget(toolButton_14, 1, 1, 1, 1, Qt::AlignHCenter);

        toolButton_34 = new QToolButton(centralwidget);
        toolButton_34->setObjectName(QString::fromUtf8("toolButton_34"));

        gridLayout->addWidget(toolButton_34, 2, 10, 1, 1, Qt::AlignHCenter);

        toolButton_32 = new QToolButton(centralwidget);
        toolButton_32->setObjectName(QString::fromUtf8("toolButton_32"));

        gridLayout->addWidget(toolButton_32, 2, 8, 1, 1, Qt::AlignHCenter);

        toolButton_25 = new QToolButton(centralwidget);
        toolButton_25->setObjectName(QString::fromUtf8("toolButton_25"));

        gridLayout->addWidget(toolButton_25, 2, 1, 1, 1, Qt::AlignHCenter);

        toolButton_2 = new QToolButton(centralwidget);
        toolButton_2->setObjectName(QString::fromUtf8("toolButton_2"));

        gridLayout->addWidget(toolButton_2, 0, 2, 1, 1, Qt::AlignHCenter);

        betColumn2Button = new QPushButton(centralwidget);
        betColumn2Button->setObjectName(QString::fromUtf8("betColumn2Button"));

        gridLayout->addWidget(betColumn2Button, 1, 14, 1, 1);

        toolButton_27 = new QToolButton(centralwidget);
        toolButton_27->setObjectName(QString::fromUtf8("toolButton_27"));

        gridLayout->addWidget(toolButton_27, 2, 3, 1, 1, Qt::AlignHCenter);

        toolButton_28 = new QToolButton(centralwidget);
        toolButton_28->setObjectName(QString::fromUtf8("toolButton_28"));

        gridLayout->addWidget(toolButton_28, 2, 4, 1, 1, Qt::AlignHCenter);

        toolButton_11 = new QToolButton(centralwidget);
        toolButton_11->setObjectName(QString::fromUtf8("toolButton_11"));

        gridLayout->addWidget(toolButton_11, 0, 10, 1, 1, Qt::AlignHCenter);

        betTwelve3Button = new QPushButton(centralwidget);
        betTwelve3Button->setObjectName(QString::fromUtf8("betTwelve3Button"));

        gridLayout->addWidget(betTwelve3Button, 4, 9, 1, 4);

        toolButton_20 = new QToolButton(centralwidget);
        toolButton_20->setObjectName(QString::fromUtf8("toolButton_20"));
        toolButton_20->setLayoutDirection(Qt::LeftToRight);

        gridLayout->addWidget(toolButton_20, 1, 7, 1, 1, Qt::AlignHCenter);

        toolButton_17 = new QToolButton(centralwidget);
        toolButton_17->setObjectName(QString::fromUtf8("toolButton_17"));

        gridLayout->addWidget(toolButton_17, 1, 4, 1, 1, Qt::AlignHCenter);

        toolButton_23 = new QToolButton(centralwidget);
        toolButton_23->setObjectName(QString::fromUtf8("toolButton_23"));

        gridLayout->addWidget(toolButton_23, 1, 11, 1, 1, Qt::AlignHCenter);

        toolButton_3 = new QToolButton(centralwidget);
        toolButton_3->setObjectName(QString::fromUtf8("toolButton_3"));

        gridLayout->addWidget(toolButton_3, 0, 3, 1, 1, Qt::AlignHCenter);

        toolButton_24 = new QToolButton(centralwidget);
        toolButton_24->setObjectName(QString::fromUtf8("toolButton_24"));

        gridLayout->addWidget(toolButton_24, 1, 12, 1, 1, Qt::AlignHCenter);

        toolButton_7 = new QToolButton(centralwidget);
        toolButton_7->setObjectName(QString::fromUtf8("toolButton_7"));

        gridLayout->addWidget(toolButton_7, 0, 7, 1, 1, Qt::AlignHCenter);

        toolButton_12 = new QToolButton(centralwidget);
        toolButton_12->setObjectName(QString::fromUtf8("toolButton_12"));

        gridLayout->addWidget(toolButton_12, 0, 11, 1, 1, Qt::AlignHCenter);

        toolButton_30 = new QToolButton(centralwidget);
        toolButton_30->setObjectName(QString::fromUtf8("toolButton_30"));

        gridLayout->addWidget(toolButton_30, 2, 6, 1, 1, Qt::AlignHCenter);

        toolButton_13 = new QToolButton(centralwidget);
        toolButton_13->setObjectName(QString::fromUtf8("toolButton_13"));

        gridLayout->addWidget(toolButton_13, 0, 12, 1, 1, Qt::AlignHCenter);

        toolButton_37 = new QToolButton(centralwidget);
        toolButton_37->setObjectName(QString::fromUtf8("toolButton_37"));

        gridLayout->addWidget(toolButton_37, 0, 1, 1, 1, Qt::AlignHCenter|Qt::AlignVCenter);

        toolButton_4 = new QToolButton(centralwidget);
        toolButton_4->setObjectName(QString::fromUtf8("toolButton_4"));

        gridLayout->addWidget(toolButton_4, 0, 4, 1, 1, Qt::AlignHCenter);

        toolButton_10 = new QToolButton(centralwidget);
        toolButton_10->setObjectName(QString::fromUtf8("toolButton_10"));

        gridLayout->addWidget(toolButton_10, 0, 9, 1, 1, Qt::AlignHCenter);

        toolButton_19 = new QToolButton(centralwidget);
        toolButton_19->setObjectName(QString::fromUtf8("toolButton_19"));

        gridLayout->addWidget(toolButton_19, 1, 6, 1, 1, Qt::AlignHCenter);

        toolButton_33 = new QToolButton(centralwidget);
        toolButton_33->setObjectName(QString::fromUtf8("toolButton_33"));

        gridLayout->addWidget(toolButton_33, 2, 9, 1, 1, Qt::AlignHCenter);

        toolButton_5 = new QToolButton(centralwidget);
        toolButton_5->setObjectName(QString::fromUtf8("toolButton_5"));

        gridLayout->addWidget(toolButton_5, 0, 5, 1, 1, Qt::AlignHCenter);

        toolButton_31 = new QToolButton(centralwidget);
        toolButton_31->setObjectName(QString::fromUtf8("toolButton_31"));

        gridLayout->addWidget(toolButton_31, 2, 7, 1, 1, Qt::AlignHCenter);

        toolButton_36 = new QToolButton(centralwidget);
        toolButton_36->setObjectName(QString::fromUtf8("toolButton_36"));

        gridLayout->addWidget(toolButton_36, 2, 12, 1, 1, Qt::AlignHCenter);

        toolButton_15 = new QToolButton(centralwidget);
        toolButton_15->setObjectName(QString::fromUtf8("toolButton_15"));

        gridLayout->addWidget(toolButton_15, 1, 2, 1, 1, Qt::AlignHCenter);

        toolButton_22 = new QToolButton(centralwidget);
        toolButton_22->setObjectName(QString::fromUtf8("toolButton_22"));

        gridLayout->addWidget(toolButton_22, 1, 10, 1, 1, Qt::AlignHCenter);

        toolButton_26 = new QToolButton(centralwidget);
        toolButton_26->setObjectName(QString::fromUtf8("toolButton_26"));

        gridLayout->addWidget(toolButton_26, 2, 2, 1, 1, Qt::AlignHCenter);

        toolButton_16 = new QToolButton(centralwidget);
        toolButton_16->setObjectName(QString::fromUtf8("toolButton_16"));

        gridLayout->addWidget(toolButton_16, 1, 3, 1, 1, Qt::AlignHCenter);

        toolButton_1 = new QToolButton(centralwidget);
        toolButton_1->setObjectName(QString::fromUtf8("toolButton_1"));

        gridLayout->addWidget(toolButton_1, 1, 0, 1, 1, Qt::AlignHCenter);

        toolButton_35 = new QToolButton(centralwidget);
        toolButton_35->setObjectName(QString::fromUtf8("toolButton_35"));

        gridLayout->addWidget(toolButton_35, 2, 11, 1, 1, Qt::AlignHCenter);

        toolButton_18 = new QToolButton(centralwidget);
        toolButton_18->setObjectName(QString::fromUtf8("toolButton_18"));

        gridLayout->addWidget(toolButton_18, 1, 5, 1, 1, Qt::AlignHCenter);

        betTwelve2Button = new QPushButton(centralwidget);
        betTwelve2Button->setObjectName(QString::fromUtf8("betTwelve2Button"));

        gridLayout->addWidget(betTwelve2Button, 4, 5, 1, 4);

        toolButton_21 = new QToolButton(centralwidget);
        toolButton_21->setObjectName(QString::fromUtf8("toolButton_21"));

        gridLayout->addWidget(toolButton_21, 1, 9, 1, 1, Qt::AlignHCenter);

        betColumn1Button = new QPushButton(centralwidget);
        betColumn1Button->setObjectName(QString::fromUtf8("betColumn1Button"));

        gridLayout->addWidget(betColumn1Button, 2, 14, 1, 1);

        betTwelve1Button = new QPushButton(centralwidget);
        betTwelve1Button->setObjectName(QString::fromUtf8("betTwelve1Button"));

        gridLayout->addWidget(betTwelve1Button, 4, 1, 1, 4);

        toolButton_6 = new QToolButton(centralwidget);
        toolButton_6->setObjectName(QString::fromUtf8("toolButton_6"));

        gridLayout->addWidget(toolButton_6, 0, 6, 1, 1, Qt::AlignHCenter);

        toolButton_8 = new QToolButton(centralwidget);
        toolButton_8->setObjectName(QString::fromUtf8("toolButton_8"));

        gridLayout->addWidget(toolButton_8, 0, 8, 1, 1, Qt::AlignHCenter);

        toolButton_29 = new QToolButton(centralwidget);
        toolButton_29->setObjectName(QString::fromUtf8("toolButton_29"));

        gridLayout->addWidget(toolButton_29, 2, 5, 1, 1, Qt::AlignHCenter);

        betColumn3Button = new QPushButton(centralwidget);
        betColumn3Button->setObjectName(QString::fromUtf8("betColumn3Button"));

        gridLayout->addWidget(betColumn3Button, 0, 14, 1, 1);

        betHalf1Button = new QPushButton(centralwidget);
        betHalf1Button->setObjectName(QString::fromUtf8("betHalf1Button"));

        gridLayout->addWidget(betHalf1Button, 5, 1, 1, 2);

        betEvenodd1Button = new QPushButton(centralwidget);
        betEvenodd1Button->setObjectName(QString::fromUtf8("betEvenodd1Button"));

        gridLayout->addWidget(betEvenodd1Button, 5, 3, 1, 2);

        betColor1Button = new QPushButton(centralwidget);
        betColor1Button->setObjectName(QString::fromUtf8("betColor1Button"));

        gridLayout->addWidget(betColor1Button, 5, 5, 1, 2);

        betColor2Button = new QPushButton(centralwidget);
        betColor2Button->setObjectName(QString::fromUtf8("betColor2Button"));

        gridLayout->addWidget(betColor2Button, 5, 7, 1, 2);

        betEvenodd2Button = new QPushButton(centralwidget);
        betEvenodd2Button->setObjectName(QString::fromUtf8("betEvenodd2Button"));

        gridLayout->addWidget(betEvenodd2Button, 5, 9, 1, 2);

        betHalf2Button = new QPushButton(centralwidget);
        betHalf2Button->setObjectName(QString::fromUtf8("betHalf2Button"));

        gridLayout->addWidget(betHalf2Button, 5, 11, 1, 2);


        horizontalLayout->addLayout(gridLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);


        verticalLayout_3->addLayout(horizontalLayout);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_3 = new QLabel(centralwidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_2->addWidget(label_3);

        betLineEdit = new QLineEdit(centralwidget);
        betLineEdit->setObjectName(QString::fromUtf8("betLineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(betLineEdit->sizePolicy().hasHeightForWidth());
        betLineEdit->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(betLineEdit);


        horizontalLayout_5->addLayout(horizontalLayout_2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_3);


        verticalLayout_3->addLayout(horizontalLayout_5);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
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
        labelTime->setText(QCoreApplication::translate("MainWindow", "Time left", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "Player, balance, betted amount", nullptr));
        labelLastNumber->setText(QCoreApplication::translate("MainWindow", "Last number", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Bets", nullptr));
        toolButton_9->setText(QCoreApplication::translate("MainWindow", "23", nullptr));
        toolButton_14->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        toolButton_34->setText(QCoreApplication::translate("MainWindow", "28", nullptr));
        toolButton_32->setText(QCoreApplication::translate("MainWindow", "22", nullptr));
        toolButton_25->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        toolButton_2->setText(QCoreApplication::translate("MainWindow", "6", nullptr));
        betColumn2Button->setText(QCoreApplication::translate("MainWindow", "2 to 1", nullptr));
        toolButton_27->setText(QCoreApplication::translate("MainWindow", "7", nullptr));
        toolButton_28->setText(QCoreApplication::translate("MainWindow", "10", nullptr));
        toolButton_11->setText(QCoreApplication::translate("MainWindow", "30", nullptr));
        betTwelve3Button->setText(QCoreApplication::translate("MainWindow", "3rd 12", nullptr));
        toolButton_20->setText(QCoreApplication::translate("MainWindow", "20", nullptr));
        toolButton_17->setText(QCoreApplication::translate("MainWindow", "11", nullptr));
        toolButton_23->setText(QCoreApplication::translate("MainWindow", "32", nullptr));
        toolButton_3->setText(QCoreApplication::translate("MainWindow", "9", nullptr));
        toolButton_24->setText(QCoreApplication::translate("MainWindow", "35", nullptr));
        toolButton_7->setText(QCoreApplication::translate("MainWindow", "21", nullptr));
        toolButton_12->setText(QCoreApplication::translate("MainWindow", "33", nullptr));
        toolButton_30->setText(QCoreApplication::translate("MainWindow", "16", nullptr));
        toolButton_13->setText(QCoreApplication::translate("MainWindow", "36", nullptr));
        toolButton_37->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
        toolButton_4->setText(QCoreApplication::translate("MainWindow", "12", nullptr));
        toolButton_10->setText(QCoreApplication::translate("MainWindow", "27", nullptr));
        toolButton_19->setText(QCoreApplication::translate("MainWindow", "17", nullptr));
        toolButton_33->setText(QCoreApplication::translate("MainWindow", "25", nullptr));
        toolButton_5->setText(QCoreApplication::translate("MainWindow", "15", nullptr));
        toolButton_31->setText(QCoreApplication::translate("MainWindow", "19", nullptr));
        toolButton_36->setText(QCoreApplication::translate("MainWindow", "34", nullptr));
        toolButton_15->setText(QCoreApplication::translate("MainWindow", "5", nullptr));
        toolButton_22->setText(QCoreApplication::translate("MainWindow", "29", nullptr));
        toolButton_26->setText(QCoreApplication::translate("MainWindow", "4", nullptr));
        toolButton_16->setText(QCoreApplication::translate("MainWindow", "8", nullptr));
        toolButton_1->setText(QCoreApplication::translate("MainWindow", "0", nullptr));
        toolButton_35->setText(QCoreApplication::translate("MainWindow", "31", nullptr));
        toolButton_18->setText(QCoreApplication::translate("MainWindow", "14", nullptr));
        betTwelve2Button->setText(QCoreApplication::translate("MainWindow", "2nd 12", nullptr));
        toolButton_21->setText(QCoreApplication::translate("MainWindow", "26", nullptr));
        betColumn1Button->setText(QCoreApplication::translate("MainWindow", "2 to 1", nullptr));
        betTwelve1Button->setText(QCoreApplication::translate("MainWindow", "1st 12", nullptr));
        toolButton_6->setText(QCoreApplication::translate("MainWindow", "18", nullptr));
        toolButton_8->setText(QCoreApplication::translate("MainWindow", "24", nullptr));
        toolButton_29->setText(QCoreApplication::translate("MainWindow", "13", nullptr));
        betColumn3Button->setText(QCoreApplication::translate("MainWindow", "2 to 1", nullptr));
        betHalf1Button->setText(QCoreApplication::translate("MainWindow", "1 to 18", nullptr));
        betEvenodd1Button->setText(QCoreApplication::translate("MainWindow", "Even", nullptr));
        betColor1Button->setText(QCoreApplication::translate("MainWindow", "Red", nullptr));
        betColor2Button->setText(QCoreApplication::translate("MainWindow", "Black", nullptr));
        betEvenodd2Button->setText(QCoreApplication::translate("MainWindow", "Odd", nullptr));
        betHalf2Button->setText(QCoreApplication::translate("MainWindow", "19 to 36", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Bet amount:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ROULETTETEST_H
