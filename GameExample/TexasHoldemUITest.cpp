#include <QApplication>
#include <QtWidgets/QMainWindow>
#include "UITexasHoldemTest.h"
#include "TexasHoldem.h"
#include "TexasBot.h"

using namespace std;

class TexasHoldemUITest : public QMainWindow {
    Ui_MainWindow ui;
    TexasHoldem *texasHoldem;
    std::vector<Gambler *> bots;
    Gambler *gambler;

    void refreshUI() {
        this->ui.tableCardsList->clear();
        this->ui.playerBalanceBetList->clear();
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
        for(auto &gamblerItemPair: items) {
            this->ui.playerBalanceBetList->addItem(QString(gamblerItemPair.second.c_str()));
        }
        // table info
        auto table = this->texasHoldem->getCurrentDealtCards();
        for(auto &card:table) {
            this->ui.tableCardsList->addItem(QString(Card::toString(*card).c_str()));
        }
    }

    void linkButtons() {
        connect(this->ui.foldButton, &QPushButton::clicked, this, &TexasHoldemUITest::texasHoldemFold);
        connect(this->ui.callButton, &QPushButton::clicked, this, &TexasHoldemUITest::texasHoldemCall);
        connect(this->ui.raiseButton, &QPushButton::clicked, this, &TexasHoldemUITest::texasHoldemRaise);
        connect(this->ui.advanceTimeButton, &QPushButton::clicked, this, &TexasHoldemUITest::advanceGame);
    }

    void texasHoldemFold() {
        int time = stoi(this->ui.advanceTimeLineEdit->text().toStdString());
        this->ui.advanceTimeLineEdit->setText(QString(to_string(time).c_str()));
        this->texasHoldem->fold(this->gambler);
        this->refreshUI();
    }

    void texasHoldemCall() {
        int time = stoi(this->ui.advanceTimeLineEdit->text().toStdString());
        this->ui.advanceTimeLineEdit->setText(QString(to_string(time).c_str()));
        this->texasHoldem->call(this->gambler);
        this->refreshUI();
    }

    void texasHoldemRaise() {
        int time = stoi(this->ui.advanceTimeLineEdit->text().toStdString());
        this->ui.advanceTimeLineEdit->setText(QString(to_string(time).c_str()));
        int amount = stoi(this->ui.raiseLineEdit->text().toStdString());
        this->texasHoldem->raise(this->gambler, amount);
        this->refreshUI();
    }

    void advanceGame() {
        int time = stoi(this->ui.advanceTimeLineEdit->text().toStdString());
        this->texasHoldem->advanceGame(time++);
        this->ui.advanceTimeLineEdit->setText(QString(to_string(time).c_str()));
        this->refreshUI();
    }

public:
    explicit TexasHoldemUITest(QWidget *parent = nullptr) {
        this->ui = Ui_MainWindow();
        this->ui.setupUi(this);

        this->linkButtons();

        this->ui.advanceTimeLineEdit->setText("30000");
        this->gambler = new Gambler(1001, "B1rtek");
        this->bots = {this->gambler, new TexasBot(1001, "Marcus"), new TexasBot(1001, "Tyler"), new TexasBot(1001, "Lina")};
        this->texasHoldem = new TexasHoldem(bots, 1000);
    }

    TexasHoldemUITest(TexasHoldemUITest const &test) {
        this->ui = test.ui;
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
    window.show();
    return QApplication::exec();
}