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
#include "TexasHoldemGUITableItem.h"

/**
 * Enum representing the names of the corresponding stackedWidget's page
 */
enum GamePage {
    MAIN_MENU,
    GAME_SELECT,
    HELP_PAGE,
    GAME_TEXAS,
    GAME_ROULETTE,
    GAME_JACKPOT
};

/**
 * CasinoWindow class, manages all objects and the UI of the game itself
 */
class CasinoWindow: public QMainWindow {
    Ui_CasinoWindow ui;
    GameManager gameManager;
    QTimer *timer;
    std::vector<TexasHoldemGUITableItem> texasHoldemCardDisplays;
    std::vector<QLabel*> texasHoldemTable;
    std::chrono::time_point<std::chrono::steady_clock> chronoTimeStart;

    void linkButtons();

    void setDarkMode();

    void setupObjects();

    void setupUI();

    static void adjustTableSize(QTableWidget *table, int targetSize, int columns);

    static int getIntFromLineEdit(QLineEdit *lineEdit);

    void sendClockSignal();

    void refreshUI();

    void joinGame();

    void leaveGame();

    void spectateGame();

    void jackpotBet();

    void texasHoldemFold();

    void texasHoldemCall();

    void texasHoldemRaise();

    void rouletteBet(RouletteBetType betType, int number);
public:
    explicit CasinoWindow(QWidget *parent = nullptr);

    CasinoWindow(const CasinoWindow &window);
};


#endif //CASINOGAME_CASINOWINDOW_H
