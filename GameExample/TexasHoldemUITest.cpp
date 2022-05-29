#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QStyleFactory>
#include "UITexasHoldemTest.h"
#include "TexasHoldem.h"
#include "TexasBot.h"

using namespace std;

class TexasHoldemUITest : public QMainWindow {
    Ui_MainWindow ui;
    TexasHoldem *texasHoldem;
    std::vector<Gambler *> bots;
    Gambler *gambler;
    int time = 25000;
    chrono::time_point<chrono::steady_clock> chronoTime;

    void refreshUI() {
        this->ui.advanceTimeLineEdit->setText(QString(to_string(this->time++).c_str()));
        this->ui.playerBalanceBetList->clear();
        this->ui.tableCardsList->clear();
        // player info
        map<Gambler *, string> items;
        auto foldStatus = this->texasHoldem->getNotFolded();
        auto gamblersList = this->texasHoldem->getPlayers();
        auto gamblersCards = this->texasHoldem->getGamblersCards();
        auto gamblersBalance = this->texasHoldem->getInGameMoney();
        auto gamblersBets = this->texasHoldem->getCurrentBets();
        Gambler* currentGambler = this->texasHoldem->getCurrentPlayer();
        for(auto &gamblerFoldPair: foldStatus) {
            if(!gamblerFoldPair.second) {
                items[gamblerFoldPair.first] += "[FOLD] ";
            }
        }
        for(auto &gamblerPlaying:gamblersList) {
            items[gamblerPlaying] += gamblerPlaying->getName();
            items[gamblerPlaying] += ", ";
        }
        for (auto &gamblerCardsPair: gamblersCards) {
            if(gamblerCardsPair.first == this->gambler) {
                for(auto &card:gamblerCardsPair.second) {
                    items[gamblerCardsPair.first] += Card::toString(*card);
                    items[gamblerCardsPair.first] += ", ";
                }
            } else {
                if(this->texasHoldem->getGameState() != SHOWDOWN) {
                    for(auto &card:gamblerCardsPair.second) {
                        items[gamblerCardsPair.first] += Card::toString(*CardGame::noneCard);
                        items[gamblerCardsPair.first] += ", ";
                    }
                } else {
                    for(auto &card:gamblerCardsPair.second) {
                        items[gamblerCardsPair.first] += Card::toString(*card);
                        items[gamblerCardsPair.first] += ", ";
                    }
                }
            }

        }
        for(auto &gamblerBalancePair:gamblersBalance) {
            items[gamblerBalancePair.first] += to_string(gamblerBalancePair.second);
            items[gamblerBalancePair.first] += ", ";
        }
        for(auto &gamblerBetPair:gamblersBets) {
            items[gamblerBetPair.first] += to_string(gamblerBetPair.second);
            items[gamblerBetPair.first] += ", ";
        }
        for(auto &gamblerItemPair: items) {
            if(gamblerItemPair.first != currentGambler) {
                gamblerItemPair.second.pop_back();
                gamblerItemPair.second.pop_back();
            } else {
                gamblerItemPair.second += "[C]";
            }
        }
        for(auto &gamblerPlaying: this->texasHoldem->getPlayers()) {
            this->ui.playerBalanceBetList->addItem(QString(items[gamblerPlaying].c_str()));
        }
        if(this->texasHoldem->isInProgress()) {
            // table info
            auto table = this->texasHoldem->getCurrentDealtCards();
            for(auto &card:table) {
                this->ui.tableCardsList->addItem(QString(Card::toString(*card).c_str()));
            }
            this->ui.gameStateLabel->setText(QString(this->texasHoldem->getGameStateString().c_str()));
        } else {
            int timeToStart = (this->texasHoldem->getTargetTime() - this->time)/1000;
            string toDisplay = "Next game starts in " + to_string(timeToStart) + " seconds";
            this->ui.tableCardsList->addItem(QString(toDisplay.c_str()));
            if(!this->texasHoldem->getLastGameWinners().empty()) {
                toDisplay = "Last game won by ";
                for(auto &winner:this->texasHoldem->getLastGameWinners()) {
                    toDisplay += winner->getName();
                    toDisplay += ", ";
                }
                toDisplay.pop_back();
                toDisplay.pop_back();
                toDisplay += " with " + this->texasHoldem->getLastWinningHandString();
                this->ui.tableCardsList->addItem(QString(toDisplay.c_str()));
                toDisplay.clear();
                if(!this->texasHoldem->getLastWinningHand().empty()) {
                    for(auto &card:this->texasHoldem->getLastWinningHand()) {
                        toDisplay += Card::toString(*card);
                        toDisplay += ", ";
                    }
                    toDisplay.pop_back();
                    toDisplay.pop_back();
                    this->ui.tableCardsList->addItem(QString(toDisplay.c_str()));
                    toDisplay = "Last table:";
                    this->ui.tableCardsList->addItem(QString(toDisplay.c_str()));
                    for(auto &card:this->texasHoldem->getCurrentDealtCards()) {
                        toDisplay += Card::toString(*card);
                        toDisplay += ", ";
                    }
                    toDisplay.pop_back();
                    toDisplay.pop_back();
                    this->ui.tableCardsList->addItem(QString(toDisplay.c_str()));
                }
            }
        }
    }

    void linkButtons() {
        connect(this->ui.foldButton, &QPushButton::clicked, this, &TexasHoldemUITest::texasHoldemFold);
        connect(this->ui.callButton, &QPushButton::clicked, this, &TexasHoldemUITest::texasHoldemCall);
        connect(this->ui.raiseButton, &QPushButton::clicked, this, &TexasHoldemUITest::texasHoldemRaise);
        connect(this->ui.advanceTimeButton, &QPushButton::clicked, this, &TexasHoldemUITest::advanceGame);
        connect(this->ui.botFoldButton, &QPushButton::clicked, this, &TexasHoldemUITest::botFold);
        connect(this->ui.botCallButton, &QPushButton::clicked, this, &TexasHoldemUITest::botCall);
        connect(this->ui.botRaiseButton, &QPushButton::clicked, this, &TexasHoldemUITest::botRaise);
    }

    void setupObjects() {
        this->ui.advanceTimeLineEdit->setText("30000");
        this->gambler = new Gambler(1001, "B1rtek");
        this->bots = {this->gambler, new TexasBot(1001, "Marcus"), new TexasBot(1001, "Tyler"), new TexasBot(1001, "Lina")};
        this->texasHoldem = new TexasHoldem(bots, 1000);
        this->chronoTime = chrono::steady_clock::now();
    }

    void texasHoldemFold() {
        this->texasHoldem->fold(this->gambler);
        this->refreshUI();
    }

    void texasHoldemCall() {
        this->texasHoldem->call(this->gambler);
        this->refreshUI();
    }

    void texasHoldemRaise() {
        string toRaiseAmount = this->ui.raiseLineEdit->text().toStdString();
        if(!toRaiseAmount.empty()) {
            int amount = stoi(toRaiseAmount);
            this->texasHoldem->raise(this->gambler, amount);
            this->refreshUI();
        }
    }

    void advanceGame() {
        string newTime = this->ui.advanceTimeLineEdit->text().toStdString();
        if(!newTime.empty()) {
            this->time = stoi(this->ui.advanceTimeLineEdit->text().toStdString());
            this->texasHoldem->advanceGame(this->time++);
            this->refreshUI();
        }
    }

    void botFold() {
        while(this->time % 21 != 0) {
            ++this->time;
        }
        this->texasHoldem->advanceGame(this->time++);
        this->refreshUI();
    }

    void botCall() {
        while(this->time % 3 != 1) {
            ++this->time;
        }
        this->texasHoldem->advanceGame(this->time++);
        this->refreshUI();
    }

    void botRaise() {
        while(this->time % 3 != 2) {
            ++this->time;
        }
        this->texasHoldem->advanceGame(this->time++);
        this->refreshUI();
    }

    void setDarkMode() {
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

public:
    explicit TexasHoldemUITest(QWidget *parent = nullptr) {
        this->ui = Ui_MainWindow();
        this->ui.setupUi(this);

        this->linkButtons();
        this->setupObjects();
        this->setDarkMode();

        auto *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &TexasHoldemUITest::sendClockSignal);
        timer->start(100);
    }

    TexasHoldemUITest(TexasHoldemUITest const &test) {
        this->ui = test.ui;
    }

public slots:
    void sendClockSignal() {
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - this->chronoTime);
        this->time = elapsed.count();
        this->ui.advanceTimeLineEdit->setText(to_string(this->time).c_str());
        this->texasHoldem->advanceGame(this->time);
        this->refreshUI();
    }

//    ~TexasHoldemUITest() override {
//        QMainWindow::~QMainWindow();
//        for(auto &bot:this->bots) {
//            delete bot;
//        }
//        delete this->texasHoldem;
//    }
};

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    QApplication::setStyle("fusion");
    TexasHoldemUITest window = TexasHoldemUITest();
    srand(time(nullptr));

    window.show();
    return QApplication::exec();
}