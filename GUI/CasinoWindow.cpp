#include "CasinoWindow.h"

/**
 * Initializes all objects and sets up all UI elements
 * @param parent Qt5 thing, unused but needed
 */
CasinoWindow::CasinoWindow(QWidget *parent) {
    this->ui = Ui_CasinoWindow();
    this->ui.setupUi(this);
    this->setDarkMode();

    this->linkButtons();
    this->setupObjects();
    this->setupUI();
}

/**
 * Links buttons to their corresponding actions
 */
void CasinoWindow::linkButtons() {
    // main menu
    connect(this->ui.buttonPlay, &QPushButton::clicked, [this]() { this->ui.stackedWidget->setCurrentIndex(GAME_SELECT); });
    connect(this->ui.buttonHelp, &QPushButton::clicked, [this]() { this->ui.stackedWidget->setCurrentIndex(HELP_PAGE); });
    connect(this->ui.buttonQuit, &QPushButton::clicked, this, &QMainWindow::close);
    // help page
    connect(this->ui.buttonBackFromHelp, &QPushButton::clicked, [this]() { this->ui.stackedWidget->setCurrentIndex(MAIN_MENU); });
    // game join page
    connect(this->ui.buttonBackToMain, &QPushButton::clicked, [this]() { this->ui.stackedWidget->setCurrentIndex(MAIN_MENU); });
    connect(this->ui.buttonJoin, &QPushButton::clicked, this, &CasinoWindow::joinGame);
    connect(this->ui.buttonSpectate, &QPushButton::clicked, this, &CasinoWindow::spectateGame);
    // jackpot
    connect(this->ui.buttonLeaveJackpot, &QPushButton::clicked, this, &CasinoWindow::leaveGame);
    connect(this->ui.buttonBetJackpot, &QPushButton::clicked, this, &CasinoWindow::jackpotBet);
    // texas holdem
    connect(this->ui.buttonLeaveTexas, &QPushButton::clicked, this, &CasinoWindow::leaveGame);
    connect(this->ui.buttonFold, &QPushButton::clicked, this, &CasinoWindow::texasHoldemFold);
    connect(this->ui.buttonCall, &QPushButton::clicked, this, &CasinoWindow::texasHoldemCall);
    connect(this->ui.buttonRaise, &QPushButton::clicked, this, &CasinoWindow::texasHoldemRaise);
    // roulette (I'm sorry for this)
    connect(this->ui.buttonLeaveRoulette, &QPushButton::clicked, this, &CasinoWindow::leaveGame);
    connect(this->ui.toolButtonRouletteBet0, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 0);});
    connect(this->ui.toolButtonRouletteBet1, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 1);});
    connect(this->ui.toolButtonRouletteBet2, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 2);});
    connect(this->ui.toolButtonRouletteBet3, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 3);});
    connect(this->ui.toolButtonRouletteBet4, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 4);});
    connect(this->ui.toolButtonRouletteBet5, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 5);});
    connect(this->ui.toolButtonRouletteBet6, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 6);});
    connect(this->ui.toolButtonRouletteBet7, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 7);});
    connect(this->ui.toolButtonRouletteBet8, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 8);});
    connect(this->ui.toolButtonRouletteBet9, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 9);});
    connect(this->ui.toolButtonRouletteBet10, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 10);});
    connect(this->ui.toolButtonRouletteBet11, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 11);});
    connect(this->ui.toolButtonRouletteBet12, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 12);});
    connect(this->ui.toolButtonRouletteBet13, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 13);});
    connect(this->ui.toolButtonRouletteBet14, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 14);});
    connect(this->ui.toolButtonRouletteBet15, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 15);});
    connect(this->ui.toolButtonRouletteBet16, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 16);});
    connect(this->ui.toolButtonRouletteBet17, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 17);});
    connect(this->ui.toolButtonRouletteBet18, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 18);});
    connect(this->ui.toolButtonRouletteBet19, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 19);});
    connect(this->ui.toolButtonRouletteBet20, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 20);});
    connect(this->ui.toolButtonRouletteBet21, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 21);});
    connect(this->ui.toolButtonRouletteBet22, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 22);});
    connect(this->ui.toolButtonRouletteBet23, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 23);});
    connect(this->ui.toolButtonRouletteBet24, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 24);});
    connect(this->ui.toolButtonRouletteBet25, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 25);});
    connect(this->ui.toolButtonRouletteBet26, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 26);});
    connect(this->ui.toolButtonRouletteBet27, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 27);});
    connect(this->ui.toolButtonRouletteBet28, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 28);});
    connect(this->ui.toolButtonRouletteBet29, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 29);});
    connect(this->ui.toolButtonRouletteBet30, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 30);});
    connect(this->ui.toolButtonRouletteBet31, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 31);});
    connect(this->ui.toolButtonRouletteBet32, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 32);});
    connect(this->ui.toolButtonRouletteBet33, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 33);});
    connect(this->ui.toolButtonRouletteBet34, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 34);});
    connect(this->ui.toolButtonRouletteBet35, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 35);});
    connect(this->ui.toolButtonRouletteBet36, &QToolButton::clicked, [this](){this->rouletteBet(NUMBER, 36);});
    connect(this->ui.buttonBetColumn1, &QPushButton::clicked, [this](){this->rouletteBet(COLUMN, 1);});
    connect(this->ui.buttonBetColumn2, &QPushButton::clicked, [this](){this->rouletteBet(COLUMN, 2);});
    connect(this->ui.buttonBetColumn3, &QPushButton::clicked, [this](){this->rouletteBet(COLUMN, 3);});
    connect(this->ui.buttonBetTwelve1, &QPushButton::clicked, [this](){this->rouletteBet(TWELVE, 1);});
    connect(this->ui.buttonBetTwelve2, &QPushButton::clicked, [this](){this->rouletteBet(TWELVE, 13);});
    connect(this->ui.buttonBetTwelve3, &QPushButton::clicked, [this](){this->rouletteBet(TWELVE, 25);});
    connect(this->ui.buttonBetHalf1, &QPushButton::clicked, [this](){this->rouletteBet(HALF, 1);});
    connect(this->ui.buttonBetHalf2, &QPushButton::clicked, [this](){this->rouletteBet(HALF, 19);});
    connect(this->ui.buttonBetEvenodd1, &QPushButton::clicked, [this](){this->rouletteBet(EVENODD, 2);});
    connect(this->ui.buttonBetEvenodd2, &QPushButton::clicked, [this](){this->rouletteBet(EVENODD, 1);});
    connect(this->ui.buttonBetColor1, &QPushButton::clicked, [this](){this->rouletteBet(COLOR, 2);});
    connect(this->ui.buttonBetColor2, &QPushButton::clicked, [this](){this->rouletteBet(COLOR, 1);});
}

/**
 * Sets the window theme to am upgraded dark mode
 */
void CasinoWindow::setDarkMode() {
    // Thank you Jorgen (https://stackoverflow.com/users/6847516/jorgen) for sharing your dark mode palette ^^
    // https://stackoverflow.com/questions/15035767/is-the-qt-5-dark-fusion-theme-available-for-windows
    QApplication::setStyle(QStyleFactory::create("Fusion"));
    QPalette darkPalette;
    darkPalette.setColor(QPalette::Window, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::WindowText, QColor(127, 127, 127));
    darkPalette.setColor(QPalette::Base, QColor(42, 42, 42));
    darkPalette.setColor(QPalette::AlternateBase, QColor(66, 66, 66));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::Text, QColor(127, 127, 127));
    darkPalette.setColor(QPalette::Dark, QColor(35, 35, 35));
    darkPalette.setColor(QPalette::Shadow, QColor(20, 20, 20));
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::ButtonText, QColor(127, 127, 127));
    darkPalette.setColor(QPalette::BrightText, Qt::black);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127, 127, 127));
    darkPalette.setColor(QPalette::Light, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::Midlight, QColor(192, 192, 192));
    darkPalette.setColor(QPalette::Mid, QColor(127, 127, 127));
    QApplication::setPalette(darkPalette);
}

/**
 * Initializes crucial application components, which are GameManager and the timer which periodically
 * refreshes the UI and triggers updates in all casino games and bots
 */
void CasinoWindow::setupObjects() {
    this->gameManager = GameManager();
    this->gameManager.start();
    this->chronoTimeStart = std::chrono::steady_clock::now();
    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CasinoWindow::sendClockSignal);
    this->timer->start(100);
}

/**
 * Changes state of some elements of the UI compared to their state in the compiled layout, for example sets
 * the current stackedWidget page to MAIN_MENU and populates vectors of the custom displays from the Texas
 * Holdem page
 */
void CasinoWindow::setupUI() {
    this->ui.stackedWidget->setCurrentIndex(MAIN_MENU);
    this->texasHoldemCardDisplays.emplace_back(this->ui.labelGambler1Name, this->ui.labelGambler1Balance, this->ui.labelGambler1Bet, this->ui.labelGambler1Card1, this->ui.labelGambler1Card2);
    this->texasHoldemCardDisplays.emplace_back(this->ui.labelGambler2Name, this->ui.labelGambler2Balance, this->ui.labelGambler2Bet, this->ui.labelGambler2Card1, this->ui.labelGambler2Card2);
    this->texasHoldemCardDisplays.emplace_back(this->ui.labelGambler3Name, this->ui.labelGambler3Balance, this->ui.labelGambler3Bet, this->ui.labelGambler3Card1, this->ui.labelGambler3Card2);
    this->texasHoldemCardDisplays.emplace_back(this->ui.labelGambler4Name, this->ui.labelGambler4Balance, this->ui.labelGambler4Bet, this->ui.labelGambler4Card1, this->ui.labelGambler4Card2);
    this->texasHoldemCardDisplays.emplace_back(this->ui.labelGambler5Name, this->ui.labelGambler5Balance, this->ui.labelGambler5Bet, this->ui.labelGambler5Card1, this->ui.labelGambler5Card2);
    this->texasHoldemCardDisplays.emplace_back(this->ui.labelGambler6Name, this->ui.labelGambler6Balance, this->ui.labelGambler6Bet, this->ui.labelGambler6Card1, this->ui.labelGambler6Card2);
    this->texasHoldemCardDisplays.emplace_back(this->ui.labelGambler7Name, this->ui.labelGambler7Balance, this->ui.labelGambler7Bet, this->ui.labelGambler7Card1, this->ui.labelGambler7Card2);
    this->texasHoldemCardDisplays.emplace_back(this->ui.labelGambler8Name, this->ui.labelGambler8Balance, this->ui.labelGambler8Bet, this->ui.labelGambler8Card1, this->ui.labelGambler8Card2);
    this->texasHoldemCardDisplays.emplace_back(this->ui.labelGambler9Name, this->ui.labelGambler9Balance, this->ui.labelGambler9Bet, this->ui.labelGambler9Card1, this->ui.labelGambler9Card2);
    this->texasHoldemCardDisplays.emplace_back(this->ui.labelGambler10Name, this->ui.labelGambler10Balance, this->ui.labelGambler10Bet, this->ui.labelGambler10Card1, this->ui.labelGambler10Card2);
    this->texasHoldemTable.push_back(this->ui.labelTexasTableCard1);
    this->texasHoldemTable.push_back(this->ui.labelTexasTableCard2);
    this->texasHoldemTable.push_back(this->ui.labelTexasTableCard3);
    this->texasHoldemTable.push_back(this->ui.labelTexasTableCard4);
    this->texasHoldemTable.push_back(this->ui.labelTexasTableCard5);
    std::string styleSheetRed = "color: white; font-size: 20px; font-style: bold; background-color: red";
    std::string styleSheetBlack = "color: white; font-size: 20px; font-style: bold; background-color: black";
    std::string styleSheetGreen = "color: white; font-size: 20px; font-style: bold; background-color: green";
    this->ui.toolButtonRouletteBet0->setStyleSheet(QString(styleSheetGreen.c_str()));
    this->ui.toolButtonRouletteBet1->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet2->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet3->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet4->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet5->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet6->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet7->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet8->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet9->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet10->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet11->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet12->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet13->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet14->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet15->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet16->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet17->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet18->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet19->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet20->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet21->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet22->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet23->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet24->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet25->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet26->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet27->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet28->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet29->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet30->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet31->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet32->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet33->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet34->setStyleSheet(QString(styleSheetBlack.c_str()));
    this->ui.toolButtonRouletteBet35->setStyleSheet(QString(styleSheetRed.c_str()));
    this->ui.toolButtonRouletteBet36->setStyleSheet(QString(styleSheetBlack.c_str()));
}

/**
 * Copy constructor, needed because QMainWindow is implicitly deleted for some reason
 */
CasinoWindow::CasinoWindow(CasinoWindow const &window) {
    this->ui = window.ui;
}

/**
 * Triggered on every timer timeout, causes updates in the whole Casino and the UI
 */
void CasinoWindow::sendClockSignal() {
    auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->chronoTimeStart);
    this->gameManager.advanceCasino(elapsed.count());
    this->refreshUI();
}

void CasinoWindow::refreshUI() {
    switch (this->ui.stackedWidget->currentIndex()) {
        case GamePage::GAME_SELECT: {
            std::string balanceString = "Your balance: " + std::to_string(this->gameManager.getPlayer()->getBalance());
            if (this->ui.labelPlayerBalance->text().toStdString() != balanceString) this->ui.labelPlayerBalance->setText(QString(balanceString.c_str()));
            if (this->ui.tableGames->rowCount() == 0) { // first addition
                int rowCounter = 0;
                for (auto &game: this->gameManager.getGames()) {
                    this->ui.tableGames->insertRow(rowCounter);
                    this->ui.tableGames->setItem(rowCounter, 0, new QTableWidgetItem(QString(game->getName().c_str())));
                    this->ui.tableGames->setItem(rowCounter, 1, new QTableWidgetItem(QString(game->getPlayerCountStr().c_str())));
                    this->ui.tableGames->setItem(rowCounter, 2, new QTableWidgetItem(QString(std::to_string(game->getMinimumEntry()).c_str())));
                    this->ui.tableGames->setItem(rowCounter, 3, new QTableWidgetItem(QString(game->getGameSituationDescription().c_str())));
                    ++rowCounter;
                }
            } else {
                int rowCounter = 0;
                for (auto &game: this->gameManager.getGames()) {
                    QTableWidgetItem updated = QTableWidgetItem(QString(game->getName().c_str()));
                    if (this->ui.tableGames->item(rowCounter, 0)->text() != updated.text()) {
                        *this->ui.tableGames->item(rowCounter, 0) = updated;
                    }
                    updated = QTableWidgetItem(QString(game->getPlayerCountStr().c_str()));
                    if (this->ui.tableGames->item(rowCounter, 1)->text() != updated.text()) {
                        *this->ui.tableGames->item(rowCounter, 1) = updated;
                    }
                    updated = QTableWidgetItem(QString(std::to_string(game->getMinimumEntry()).c_str()));
                    if (this->ui.tableGames->item(rowCounter, 2)->text() != updated.text()) {
                        *this->ui.tableGames->item(rowCounter, 2) = updated;
                    }
                    updated = QTableWidgetItem(QString(game->getGameSituationDescription().c_str()));
                    if (this->ui.tableGames->item(rowCounter, 3)->text() != updated.text()) {
                        *this->ui.tableGames->item(rowCounter, 3) = updated;
                    }
                    ++rowCounter;
                }
            }
            this->ui.tableGames->setEditTriggers(QAbstractItemView::NoEditTriggers);
            this->ui.tableGames->viewport()->update();
        }
            break;
        case GamePage::GAME_TEXAS: {
            TexasHoldem *currentGame;
            if(this->gameManager.getPlayer()->getCurrentGame() != nullptr) {
                currentGame = dynamic_cast<TexasHoldem *>(this->gameManager.getPlayer()->getCurrentGame()); // if this cast fails something went horribly wrong
            } else {
                currentGame = dynamic_cast<TexasHoldem *>(this->gameManager.getPlayer()->getSpectatedGame()); // same here
            }
            if(currentGame == nullptr) { // if both were nullptr we force quit
                this->ui.stackedWidget->setCurrentIndex(GAME_SELECT);
                this->refreshUI();
            }
            // players "table"
            int displayNumber = 0;
            for(auto &gambler: currentGame->getPlayers()) {
                this->texasHoldemCardDisplays[displayNumber++].updateItem(currentGame, gambler, this->gameManager.getPlayer());
            }
            while(displayNumber < 10) {
                this->texasHoldemCardDisplays[displayNumber++].updateItem();
            }
            // table cards "table"
            displayNumber = 0;
            for(auto &card: currentGame->getCurrentDealtCards()) {
                std::string cardRepresentation = Card::toString(*card);
                if(this->texasHoldemTable[displayNumber]->text().toStdString() != cardRepresentation) {
                    this->texasHoldemTable[displayNumber]->setText(QString(cardRepresentation.c_str()));
                }
                ++displayNumber;
            }
            // texas holdem last winner label
            std::string toDisplay;
            if (!currentGame->getLastGameWinners().empty() && !currentGame->isInProgress()) {
                toDisplay = "Last game winners: ";
                for(auto &gambler: currentGame->getLastGameWinners()) {
                    toDisplay += gambler->getName() + ", ";
                }
                toDisplay.pop_back();
                toDisplay.pop_back();
                toDisplay += " with " + currentGame->getLastWinningHandString();
                if(!currentGame->getLastWinningHand().empty()) {
                    toDisplay += ": ";
                    for(auto &card: currentGame->getLastWinningHand()) {
                        toDisplay += Card::toString(*card) + ", ";
                    }
                    toDisplay.pop_back();
                    toDisplay.pop_back();
                }
                if (this->ui.labelLastResultsTexas->text().toStdString() != toDisplay) {
                    this->ui.labelLastResultsTexas->setText(QString(toDisplay.c_str()));
                }
            }
            // texas holdem countdown label
            toDisplay = currentGame->getGameSituationDescription();
            if(this->ui.labelCountdownTexas->text().toStdString() != toDisplay) {
                this->ui.labelCountdownTexas->setText(QString(toDisplay.c_str()));
            }
            // texas holdem state label
            toDisplay = currentGame->getGameStateString();
            if(this->ui.labelTexasGameState->text().toStdString() != toDisplay) {
                this->ui.labelTexasGameState->setText(QString(toDisplay.c_str()));
            }
            // texas holdem name label
            if(this->ui.labelTexasHoldemName->text().toStdString() != currentGame->getName()) {
                this->ui.labelTexasHoldemName->setText(QString(currentGame->getName().c_str()));
            }
        }
            break;
        case GamePage::GAME_ROULETTE: {
            Roulette *currentGame;
            if(this->gameManager.getPlayer()->getCurrentGame() != nullptr) {
                currentGame = dynamic_cast<Roulette *>(this->gameManager.getPlayer()->getCurrentGame()); // if this cast fails something went horribly wrong
            } else {
                currentGame = dynamic_cast<Roulette *>(this->gameManager.getPlayer()->getSpectatedGame()); // same here
            }
            if(currentGame == nullptr) { // if both were nullptr we force quit
                this->ui.stackedWidget->setCurrentIndex(GAME_SELECT);
                this->refreshUI();
            }
            // tables - gamblers table
            CasinoWindow::adjustTableSize(this->ui.tableGamblersRoulette, currentGame->getPlayers().size(), 3);
            int rowCounter = 0;
            for (auto &gambler: currentGame->getPlayers()) {
                QTableWidgetItem updated = QTableWidgetItem(QString(gambler->getName().c_str()));
                if (this->ui.tableGamblersRoulette->item(rowCounter, 0)->text() != updated.text()) {
                    *this->ui.tableGamblersRoulette->item(rowCounter, 0) = updated;
                }
                updated = QTableWidgetItem(QString(std::to_string(currentGame->getInGameMoney()[gambler]).c_str()));
                if (this->ui.tableGamblersRoulette->item(rowCounter, 1)->text() != updated.text()) {
                    *this->ui.tableGamblersRoulette->item(rowCounter, 1) = updated;
                }
                updated = QTableWidgetItem(QString(std::to_string(currentGame->getCurrentBets()[gambler]).c_str()));
                if (this->ui.tableGamblersRoulette->item(rowCounter, 2)->text() != updated.text()) {
                    *this->ui.tableGamblersRoulette->item(rowCounter, 2) = updated;
                }
                ++rowCounter;
            }
            this->ui.tableGamblersRoulette->setEditTriggers(QAbstractItemView::NoEditTriggers);
            this->ui.tableGamblersRoulette->viewport()->update();
            // tables - roulette bets
            rowCounter = this->ui.tableBetsRoulette->rowCount();
            std::vector<RouletteBet> rouletteBets = currentGame->getRouletteBets();
            CasinoWindow::adjustTableSize(this->ui.tableBetsRoulette, rouletteBets.size(), 4);
            bool scrollToBottom = rowCounter != rouletteBets.size();
            rowCounter = 0;
            for(auto &bet: rouletteBets) {
                QTableWidgetItem updated = QTableWidgetItem(QString(bet.gambler->getName().c_str()));
                if(this->ui.tableBetsRoulette->item(rowCounter, 0)->text() != updated.text()) {
                    *this->ui.tableBetsRoulette->item(rowCounter, 0) = updated;
                }
                updated = QTableWidgetItem(QString(bet.getAmountString().c_str()));
                if(this->ui.tableBetsRoulette->item(rowCounter, 1)->text() != updated.text()) {
                    *this->ui.tableBetsRoulette->item(rowCounter, 1) = updated;
                }
                updated = QTableWidgetItem(QString(bet.getBetTypeString().c_str()));
                if(this->ui.tableBetsRoulette->item(rowCounter, 2)->text() != updated.text()) {
                    *this->ui.tableBetsRoulette->item(rowCounter, 2) = updated;
                }
                if(!currentGame->isInProgress()) {
                    updated = QTableWidgetItem(QString(bet.getSuccessString().c_str()));
                    if(this->ui.tableBetsRoulette->item(rowCounter, 3)->text() != updated.text()) {
                        *this->ui.tableBetsRoulette->item(rowCounter, 3) = updated;
                    }
                }
                ++rowCounter;
            }
            this->ui.tableBetsRoulette->setEditTriggers(QAbstractItemView::NoEditTriggers);
            this->ui.tableBetsRoulette->viewport()->update();
            if(scrollToBottom) {
                QTableWidgetItem *last = this->ui.tableBetsRoulette->item((this->ui.tableBetsRoulette->rowCount()-1), 0);
                this->ui.tableBetsRoulette->scrollToItem(last, QAbstractItemView::PositionAtBottom);
            }
            // roulette countdown label
            std::string toDisplay;
            if (currentGame->isInProgress()) {
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->chronoTimeStart);
                int timeToStart = (currentGame->getTargetTime() - elapsed.count()) / 1000;
                toDisplay = "Betting ends in " + std::to_string(timeToStart) + " seconds";
            } else {
                toDisplay = currentGame->getGameSituationDescription();
            }
            if (this->ui.labelCountdownRoulette->text().toStdString() != toDisplay) {
                this->ui.labelCountdownRoulette->setText(QString(toDisplay.c_str()));
            }
            // roulette last number display
            if(!currentGame->getRouletteBets().empty()) {
                toDisplay = "Last rolled number: " + std::to_string(currentGame->getLastRolledNumber());
                if(this->ui.labelLastResultsRoulette->text().toStdString() != toDisplay) {
                    this->ui.labelLastResultsRoulette->setText(QString(toDisplay.c_str()));
                }
            }
            // roulette name label
            if(this->ui.labelRouletteName->text().toStdString() != currentGame->getName()) {
                this->ui.labelRouletteName->setText(QString(currentGame->getName().c_str()));
            }
        }
            break;
        case GamePage::GAME_JACKPOT: {
            Jackpot *currentGame;
            if(this->gameManager.getPlayer()->getCurrentGame() != nullptr) {
                currentGame = dynamic_cast<Jackpot *>(this->gameManager.getPlayer()->getCurrentGame()); // if this cast fails something went horribly wrong
            } else {
                currentGame = dynamic_cast<Jackpot *>(this->gameManager.getPlayer()->getSpectatedGame()); // same here
            }
            if(currentGame == nullptr) { // if both were nullptr we force quit
                this->ui.stackedWidget->setCurrentIndex(GAME_SELECT);
                this->refreshUI();
            }
            // tables - gamblers table
            CasinoWindow::adjustTableSize(this->ui.tableGamblersJackpot, currentGame->getPlayers().size(), 3);
            int rowCounter = 0;
            for (auto &gambler: currentGame->getPlayers()) {
                QTableWidgetItem updated = QTableWidgetItem(QString(gambler->getName().c_str()));
                if (this->ui.tableGamblersJackpot->item(rowCounter, 0)->text() != updated.text()) {
                    *this->ui.tableGamblersJackpot->item(rowCounter, 0) = updated;
                }
                updated = QTableWidgetItem(QString(std::to_string(currentGame->getInGameMoney()[gambler]).c_str()));
                if (this->ui.tableGamblersJackpot->item(rowCounter, 1)->text() != updated.text()) {
                    *this->ui.tableGamblersJackpot->item(rowCounter, 1) = updated;
                }
                updated = QTableWidgetItem(QString(std::to_string(currentGame->getCurrentBets()[gambler]).c_str()));
                if (this->ui.tableGamblersJackpot->item(rowCounter, 2)->text() != updated.text()) {
                    *this->ui.tableGamblersJackpot->item(rowCounter, 2) = updated;
                }
                ++rowCounter;
            }
            this->ui.tableGamblersJackpot->setEditTriggers(QAbstractItemView::NoEditTriggers);
            this->ui.tableGamblersJackpot->viewport()->update();
            // tables - bets table
            CasinoWindow::adjustTableSize(this->ui.tableBetsJackpot, currentGame->getPlayers().size(), 2);
            rowCounter = 0;
            for (auto &gamblerPercentagePair: currentGame->getSortedPercentages()) {
                QTableWidgetItem updated = QTableWidgetItem(QString(gamblerPercentagePair.first->getName().c_str()));
                if (this->ui.tableBetsJackpot->item(rowCounter, 0)->text() != updated.text()) {
                    *this->ui.tableBetsJackpot->item(rowCounter, 0) = updated;
                }
                updated = QTableWidgetItem(QString((std::to_string(currentGame->getPercentages()[gamblerPercentagePair.first]) + '%').c_str()));
                if (this->ui.tableBetsJackpot->item(rowCounter, 1)->text() != updated.text()) {
                    *this->ui.tableBetsJackpot->item(rowCounter, 1) = updated;
                }
                ++rowCounter;
            }
            this->ui.tableBetsJackpot->setEditTriggers(QAbstractItemView::NoEditTriggers);
            this->ui.tableBetsJackpot->viewport()->update();
            // jackpot countdown label
            std::string toDisplay;
            if (currentGame->isInProgress()) {
                auto elapsed = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now() - this->chronoTimeStart);
                int timeToStart = (currentGame->getTargetTime() - elapsed.count()) / 1000;
                toDisplay = "Betting ends in " + std::to_string(timeToStart) + " seconds";
            } else {
                toDisplay = currentGame->getGameSituationDescription();
            }
            if (this->ui.labelCountdownJackpot->text().toStdString() != toDisplay) {
                this->ui.labelCountdownJackpot->setText(QString(toDisplay.c_str()));
            }
            // jackpot last winner label
            if (!currentGame->getLastGameWinners().empty()) {
                toDisplay = "Last game winner: " + currentGame->getLastGameWinners()[0]->getName();
                if (this->ui.labelLastResultsJackpot->text().toStdString() != toDisplay) {
                    this->ui.labelLastResultsJackpot->setText(QString(toDisplay.c_str()));
                }
            }
            // jackpot name label
            if(this->ui.labelJackpotName->text().toStdString() != currentGame->getName()) {
                this->ui.labelJackpotName->setText(QString(currentGame->getName().c_str()));
            }
        }
            break;

    }
}

/**
 * The following methods correspond to actions triggered by pressing the buttons, they are called
 * according to the connect()ionns performed in the window setup
 */
void CasinoWindow::joinGame() {
    QList<QTableWidgetSelectionRange> selected = this->ui.tableGames->selectedRanges();
    if (!selected.empty()) {
        if (this->gameManager.joinGame(selected[0].topRow())) {
            this->ui.stackedWidget->setCurrentIndex(3 + this->gameManager.getPlayer()->getCurrentGame()->getGameType());
            this->refreshUI();
        }
    }
}

void CasinoWindow::spectateGame() {
    QList<QTableWidgetSelectionRange> selected = this->ui.tableGames->selectedRanges();
    if (!selected.empty()) {
        if (this->gameManager.spectateGame(selected[0].topRow())) {
            this->ui.stackedWidget->setCurrentIndex(3 + this->gameManager.getPlayer()->getSpectatedGame()->getGameType());
            this->refreshUI();
        }
    }
}

/**
 * Adjusts the provided table row count to the target one
 * @param table table to resize
 * @param targetSize target row count of the table
 * @param columns column count
 */
void CasinoWindow::adjustTableSize(QTableWidget *table, int targetSize, int columns) {
    if (targetSize != table->rowCount()) { // fix the row count
        while (targetSize < table->rowCount()) {
            for (int i = 0; i < columns; i++) {
                delete table->item(table->rowCount() - 1, i);
            }
            table->removeRow(table->rowCount() - 1);
        }
        while (targetSize > table->rowCount()) {
            table->insertRow(table->rowCount());
            for (int i = 0; i < columns; i++) {
                table->setItem(table->rowCount() - 1, i, new QTableWidgetItem());
            }
        }
    }
}

void CasinoWindow::leaveGame() {
    if (this->gameManager.leaveGame() || this->gameManager.stopSpectating()) {
        this->ui.stackedWidget->setCurrentIndex(GamePage::GAME_SELECT);
        this->refreshUI();
    }
}

void CasinoWindow::jackpotBet() {
    if (this->gameManager.getPlayer()->getCurrentGame() != nullptr) {
        if (this->gameManager.getPlayer()->getCurrentGame()->getGameType() == JACKPOT) {
            int toBet = CasinoWindow::getIntFromLineEdit(this->ui.lineEditBetJackpot);
            if (toBet != 0 && this->gameManager.jackpotBet(toBet)) {
                this->refreshUI();
            }
        }
    }
}

/**
 * Reads an integet from a QLineEdit and catches all exceptions that might occur while doing that
 * @param lineEdit QLineEdit to read the number from
 * @return A number read or 0 if the read failed
 */
int CasinoWindow::getIntFromLineEdit(QLineEdit *lineEdit) {
    std::string intAsString = lineEdit->text().toStdString();
    if (!intAsString.empty()) {
        try {
            return stoi(intAsString);
        } catch (const std::invalid_argument& e) {
            lineEdit->setText(QString());
        } catch (const std::out_of_range& e) {
            lineEdit->setText(QString());
        }
    }
    return 0;
}

void CasinoWindow::texasHoldemFold() {
    if (this->gameManager.getPlayer()->getCurrentGame() != nullptr) {
        if (this->gameManager.getPlayer()->getCurrentGame()->getGameType() == TEXAS_HOLDEM) {
            if (this->gameManager.texasHoldemFold()) {
                this->refreshUI();
            }
        }
    }
}

void CasinoWindow::texasHoldemCall() {
    if (this->gameManager.getPlayer()->getCurrentGame() != nullptr) {
        if (this->gameManager.getPlayer()->getCurrentGame()->getGameType() == TEXAS_HOLDEM) {
            if (this->gameManager.texasHoldemCall()) {
                this->refreshUI();
            }
        }
    }
}

void CasinoWindow::texasHoldemRaise() {
    if (this->gameManager.getPlayer()->getCurrentGame() != nullptr) {
        if (this->gameManager.getPlayer()->getCurrentGame()->getGameType() == TEXAS_HOLDEM) {
            int toRaise = CasinoWindow::getIntFromLineEdit(this->ui.lineEditRaise);
            if (toRaise != 0 && this->gameManager.texasHoldemRaise(toRaise)) {
                this->refreshUI();
            }
        }
    }
}

void CasinoWindow::rouletteBet(RouletteBetType betType, int number) {
    if (this->gameManager.getPlayer()->getCurrentGame() != nullptr) {
        if (this->gameManager.getPlayer()->getCurrentGame()->getGameType() == ROULETTE) {
            int toBet = CasinoWindow::getIntFromLineEdit(this->ui.lineEditBetRoulette);
            if (toBet != 0 && this->gameManager.rouletteBet(betType, number, toBet)) {
                this->refreshUI();
            }
        }
    }
}
