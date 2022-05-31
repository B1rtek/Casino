#ifndef CASINOGAME_CASINOWINDOW_H
#define CASINOGAME_CASINOWINDOW_H

#include <chrono>
#include <random>
#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QStyleFactory>
#include "UICasino.h"
#include "GameManager.h"

enum GamePage {
    MAIN_MENU,
    GAME_SELECT,
    HELP_PAGE,
    GAME_TEXAS,
    GAME_ROULETTE,
    GAME_JACKPOT
};

class CasinoWindow: public QMainWindow {
    Ui_CasinoWindow ui;
    GameManager gameManager;
    QTimer *timer;
    std::chrono::time_point<std::chrono::steady_clock> chronoTimeStart;

    void linkButtons();

    void setDarkMode();

    void setupObjects();

    void setupUI();

    void sendClockSignal();

    void refreshUI();

    void joinGame();

    void spectateGame();
public:
    explicit CasinoWindow(QWidget *parent = nullptr);

    CasinoWindow(const CasinoWindow &window);
};


#endif //CASINOGAME_CASINOWINDOW_H
