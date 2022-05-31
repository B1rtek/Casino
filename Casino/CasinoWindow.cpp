#include "CasinoWindow.h"

CasinoWindow::CasinoWindow(QWidget *parent) {
    this->ui = Ui_CasinoWindow();
    this->ui.setupUi(this);
    this->setDarkMode();

    this->linkButtons();
    this->setupObjects();
    this->setupUI();
}

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
}

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
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Disabled, QPalette::Highlight, QColor(80, 80, 80));
    darkPalette.setColor(QPalette::HighlightedText, Qt::white);
    darkPalette.setColor(QPalette::Disabled, QPalette::HighlightedText, QColor(127, 127, 127));
    QApplication::setPalette(darkPalette);
}

void CasinoWindow::setupObjects() {
    this->gameManager = GameManager();
    this->gameManager.start();
    this->chronoTimeStart = std::chrono::steady_clock::now();
    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CasinoWindow::sendClockSignal);
    this->timer->start(100);
}

void CasinoWindow::setupUI() {
    this->ui.stackedWidget->setCurrentIndex(MAIN_MENU);
}

CasinoWindow::CasinoWindow(CasinoWindow const &window) {
    this->ui = window.ui;
}

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

        }
            break;
        case GamePage::GAME_ROULETTE: {

        }
            break;
        case GamePage::GAME_JACKPOT: {
            Jackpot *currentGame;
            if(this->gameManager.getPlayer()->getCurrentGame() != nullptr) {
                currentGame = dynamic_cast<Jackpot *>(this->gameManager.getPlayer()->getCurrentGame()); // if this cast fails something went horribly wrong
            } else {
                currentGame = dynamic_cast<Jackpot *>(this->gameManager.getPlayer()->getSpectatedGame()); // same here
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
        }
            break;

    }
}

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
