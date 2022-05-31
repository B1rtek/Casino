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

        }
            break;

    }
}

void CasinoWindow::joinGame() {
    QList<QTableWidgetSelectionRange> selected = this->ui.tableGames->selectedRanges();
    if(!selected.empty()) {
        this->gameManager.joinGame(selected[0].topRow());
    }
}

void CasinoWindow::spectateGame() {
    QList<QTableWidgetSelectionRange> selected = this->ui.tableGames->selectedRanges();
    if(!selected.empty()) {
        this->gameManager.spectateGame(selected[0].topRow());
    }
}
