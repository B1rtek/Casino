#ifndef CASINOGAME_CASINOWINDOW_H
#define CASINOGAME_CASINOWINDOW_H

#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QStyleFactory>
#include "UICasino.h"
#include "GameManager.h"

class CasinoWindow: public QMainWindow {
    Ui_CasinoWindow ui;
    GameManager gameManager;

};


#endif //CASINOGAME_CASINOWINDOW_H
