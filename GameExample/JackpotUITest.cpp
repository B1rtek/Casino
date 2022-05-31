#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QStyleFactory>
#include "UIJackpotTest.h"
#include "Jackpot.h"
#include "JackpotBot.h"

using namespace std;

class JackpotUITest : public QMainWindow {
    Ui_MainWindow ui;
    Jackpot *jackpot;
    std::vector<Gambler *> bots;
    Gambler *gambler;
    int time = 25000;
    chrono::time_point<chrono::steady_clock> chronoTime;

    void refreshUI() {
        this->ui.advanceTimeLineEdit->setText(QString(to_string(this->time++).c_str()));
        this->ui.playerBalanceBetList->clear();
        this->ui.percentagesList->clear();
        // player info
        map<Gambler *, string> items;
        auto gamblersList = this->jackpot->getPlayers();
        auto gamblersBalance = this->jackpot->getInGameMoney();
        auto gamblersBets = this->jackpot->getCurrentBets();
        for (auto &gamblerPlaying: gamblersList) {
            items[gamblerPlaying] += gamblerPlaying->getName();
            items[gamblerPlaying] += ", ";
        }
        for (auto &gamblerBalancePair: gamblersBalance) {
            items[gamblerBalancePair.first] += to_string(gamblerBalancePair.second);
            items[gamblerBalancePair.first] += ", ";
        }
        for (auto &gamblerBetPair: gamblersBets) {
            items[gamblerBetPair.first] += to_string(gamblerBetPair.second);
            items[gamblerBetPair.first] += ", ";
        }
        for (auto &gamblerPlaying: this->jackpot->getPlayers()) {
            this->ui.playerBalanceBetList->addItem(QString(items[gamblerPlaying].c_str()));
        }
        if (this->jackpot->isInProgress()) {
            // bet info
            int timeToStart = (this->jackpot->getTargetTime() - this->time) / 1000;
            string toDisplay = "Betting ends in " + to_string(timeToStart) + " seconds";
            this->ui.percentagesList->addItem(QString(toDisplay.c_str()));
            auto percentages = this->jackpot->getPercentages();
            vector<pair<double, string>> sortedPerecentages;
            for (auto &gamblerPercentagePair: percentages) {
                sortedPerecentages.emplace_back(gamblerPercentagePair.second, gamblerPercentagePair.first->getName());
            }
            sort(sortedPerecentages.begin(), sortedPerecentages.end(),
                 [](const pair<double, string> &one, const pair<double, string> &two) {
                     return one.first < two.first;
                 });
            for (auto &percentageGamblerPair: sortedPerecentages) {
                toDisplay = percentageGamblerPair.second;
                toDisplay.append(": ").append(to_string(percentageGamblerPair.first)).append("%");
                this->ui.percentagesList->addItem(QString(toDisplay.c_str()));
            }
        } else {
            int timeToStart = (this->jackpot->getTargetTime() - this->time) / 1000;
            string toDisplay = "Next game starts in " + to_string(timeToStart) + " seconds";
            this->ui.percentagesList->addItem(QString(toDisplay.c_str()));
            if (!this->jackpot->getLastGameWinners().empty()) {
                toDisplay = "Last game won by ";
                toDisplay.append(this->jackpot->getLastGameWinners()[0]->getName());
            }
        }
    }

    void linkButtons() {
        connect(this->ui.betButton, &QPushButton::clicked, this, &JackpotUITest::jackpotBet);
        connect(this->ui.advanceTimeButton, &QPushButton::clicked, this, &JackpotUITest::advanceGame);
        connect(this->ui.botBetButton, &QPushButton::clicked, this, &JackpotUITest::botBet);
    }

    void setupObjects() {
        this->ui.advanceTimeLineEdit->setText("30000");
        this->gambler = new Gambler(1001, "B1rtek");
        this->bots = {this->gambler, new JackpotBot(1001, "Marcus"), new JackpotBot(1001, "Tyler"),
                      new JackpotBot(1001, "Lina")};
        this->jackpot = new Jackpot(bots, 1000);
        this->chronoTime = chrono::steady_clock::now();
    }

    void jackpotBet() {
        string toRaiseAmount = this->ui.betLineEdit->text().toStdString();
        if (!toRaiseAmount.empty()) {
            int amount = stoi(toRaiseAmount);
            this->jackpot->bet(this->gambler, amount);
            this->refreshUI();
        }
    }

    void advanceGame() {
        string newTime = this->ui.advanceTimeLineEdit->text().toStdString();
        if (!newTime.empty()) {
            this->time = stoi(this->ui.advanceTimeLineEdit->text().toStdString());
            this->jackpot->advanceGame(this->time++);
            this->refreshUI();
        }
    }

    void botBet() {
        this->time = ((this->time / 10000) + 1) * 10000;
        this->jackpot->advanceGame(this->time++);
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
    explicit JackpotUITest(QWidget *parent = nullptr) {
        this->ui = Ui_MainWindow();
        this->ui.setupUi(this);

        this->linkButtons();
        this->setupObjects();
        this->setDarkMode();

        auto *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &JackpotUITest::sendClockSignal);
        timer->start(100);
    }

    JackpotUITest(JackpotUITest const &test) {
        this->ui = test.ui;
    }

public slots:

    void sendClockSignal() {
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - this->chronoTime);
        this->time = elapsed.count();
        this->ui.advanceTimeLineEdit->setText(to_string(this->time).c_str());
        this->jackpot->advanceGame(this->time);
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
    JackpotUITest window = JackpotUITest();

    window.show();
    return QApplication::exec();
}