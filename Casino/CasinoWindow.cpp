#include "CasinoWindow.h"

CasinoWindow::CasinoWindow(QWidget *parent) {
    this->ui = Ui_CasinoWindow();
    this->ui.setupUi(this);

    this->linkButtons();
    this->setupObjects();
    this->setupUI();
}

void CasinoWindow::linkButtons() {
    connect(this->ui.buttonPlay, &QPushButton::clicked, [this](){this->ui.stackedWidget->setCurrentIndex(GAME_SELECT);});
    connect(this->ui.buttonHelp, &QPushButton::clicked, [this](){this->ui.stackedWidget->setCurrentIndex(HELP_PAGE);});
    connect(this->ui.buttonQuit, &QPushButton::clicked, this, &QMainWindow::close);
}

void CasinoWindow::setupObjects() {
    this->gameManager = GameManager();
    this->gameManager.start();
    this->timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &CasinoWindow::sendClockSignal);
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

}
