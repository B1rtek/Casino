/**
 * Program with a test UI which lets the user play Roulette, used for UI and Roulette testing
 */

#include <QApplication>
#include <QtWidgets/QMainWindow>
#include <QTimer>
#include <QStyleFactory>
#include "UIRouletteTest.h"
#include "Roulette.h"
#include "RouletteBot.h"

using namespace std;

/**
 * Test class representing a Roulette window, parts of it were later incorporated into the CasinoWindow class
 */
class RouletteUITest : public QMainWindow {
    Ui_MainWindow ui;
    Roulette *roulette;
    std::vector<Gambler *> bots;
    Gambler *gambler;
    int time = 25000;
    chrono::time_point<chrono::steady_clock> chronoTime;

    /**
     * Method that refreshes the UI by getting all data needed to display and updating the content
     * of the displayed widgets according to the newest data
     */
    void refreshUI() {
        this->ui.playerBalanceBetList->clear();
        this->ui.percentagesList->clear();
        // player info
        map<Gambler *, string> items;
        auto gamblersList = this->roulette->getPlayers();
        auto gamblersBalance = this->roulette->getInGameMoney();
        auto gamblersBets = this->roulette->getCurrentBets();
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
        for (auto &gamblerPlaying: this->roulette->getPlayers()) {
            this->ui.playerBalanceBetList->addItem(QString(items[gamblerPlaying].c_str()));
        }
        // bet info
        vector<RouletteBet> bets = this->roulette->getRouletteBets();
        int timeToStart = (this->roulette->getTargetTime() - this->time) / 1000;
        string toDisplay;
        if (this->roulette->isInProgress()) {
            toDisplay = "Betting ends in " + to_string(timeToStart) + " seconds";
        } else {
            toDisplay = "Next game starts in " + to_string(timeToStart) + " seconds";
        }
        this->ui.labelTime->setText(QString(toDisplay.c_str()));
        if (!bets.empty()) {
            toDisplay = "Number from the last game: " + to_string(this->roulette->getLastRolledNumber());
            this->ui.labelLastNumber->setText(QString(toDisplay.c_str()));
        }
        for (auto &bet: bets) {
            this->ui.percentagesList->addItem(QString(bet.getBetStringRepresentation().c_str()));
        }
    }

    void linkButtons() {
        // I'm sorry
        connect(this->ui.toolButton_1, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_1->text());});
        connect(this->ui.toolButton_2, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_2->text());});
        connect(this->ui.toolButton_3, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_3->text());});
        connect(this->ui.toolButton_4, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_4->text());});
        connect(this->ui.toolButton_5, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_5->text());});
        connect(this->ui.toolButton_6, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_6->text());});
        connect(this->ui.toolButton_7, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_7->text());});
        connect(this->ui.toolButton_8, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_8->text());});
        connect(this->ui.toolButton_9, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_9->text());});
        connect(this->ui.toolButton_10, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_10->text());});
        connect(this->ui.toolButton_11, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_11->text());});
        connect(this->ui.toolButton_12, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_12->text());});
        connect(this->ui.toolButton_13, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_13->text());});
        connect(this->ui.toolButton_14, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_14->text());});
        connect(this->ui.toolButton_15, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_15->text());});
        connect(this->ui.toolButton_16, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_16->text());});
        connect(this->ui.toolButton_17, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_17->text());});
        connect(this->ui.toolButton_18, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_18->text());});
        connect(this->ui.toolButton_19, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_19->text());});
        connect(this->ui.toolButton_20, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_20->text());});
        connect(this->ui.toolButton_21, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_21->text());});
        connect(this->ui.toolButton_22, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_22->text());});
        connect(this->ui.toolButton_23, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_23->text());});
        connect(this->ui.toolButton_24, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_24->text());});
        connect(this->ui.toolButton_25, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_25->text());});
        connect(this->ui.toolButton_26, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_26->text());});
        connect(this->ui.toolButton_27, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_27->text());});
        connect(this->ui.toolButton_28, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_28->text());});
        connect(this->ui.toolButton_29, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_29->text());});
        connect(this->ui.toolButton_30, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_30->text());});
        connect(this->ui.toolButton_31, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_31->text());});
        connect(this->ui.toolButton_32, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_32->text());});
        connect(this->ui.toolButton_33, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_33->text());});
        connect(this->ui.toolButton_34, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_34->text());});
        connect(this->ui.toolButton_35, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_35->text());});
        connect(this->ui.toolButton_36, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_36->text());});
        connect(this->ui.toolButton_37, &QToolButton::clicked, [this]() {this->rouletteBetNumber(this->ui.toolButton_37->text());});

        connect(this->ui.betColumn1Button, &QPushButton::clicked, [this]() {this->rouletteBetColumn(1);});
        connect(this->ui.betColumn2Button, &QPushButton::clicked, [this]() {this->rouletteBetColumn(2);});
        connect(this->ui.betColumn3Button, &QPushButton::clicked, [this]() {this->rouletteBetColumn(3);});
        connect(this->ui.betTwelve1Button, &QPushButton::clicked, [this]() {this->rouletteBetTwelve(1);});
        connect(this->ui.betTwelve2Button, &QPushButton::clicked, [this]() {this->rouletteBetTwelve(13);});
        connect(this->ui.betTwelve3Button, &QPushButton::clicked, [this]() {this->rouletteBetTwelve(25);});
        connect(this->ui.betHalf1Button, &QPushButton::clicked, [this]() {this->rouletteBetHalf(1);});
        connect(this->ui.betHalf2Button, &QPushButton::clicked, [this]() {this->rouletteBetHalf(2);});
        connect(this->ui.betEvenodd1Button, &QPushButton::clicked, [this]() {this->rouletteBetEvenOdd(2);});
        connect(this->ui.betEvenodd2Button, &QPushButton::clicked, [this]() {this->rouletteBetEvenOdd(1);});
        connect(this->ui.betColor1Button, &QPushButton::clicked, [this]() {this->rouletteBetEvenOdd(2);});
        connect(this->ui.betColor2Button, &QPushButton::clicked, [this]() {this->rouletteBetEvenOdd(1);});
    }

    /**
     * Initializes objects used in the game
     */
    void setupObjects() {
        this->gambler = new Gambler(1001, "B1rtek");
        this->bots = {this->gambler, new RouletteBot(1001, "Marcus"), new RouletteBot(1001, "Tyler"),
                      new RouletteBot(1001, "Lina")};
        this->roulette = new Roulette(bots, 1000);
        this->chronoTime = chrono::steady_clock::now();
    }

    /**
     * Method that allows the gambler to place a straight bet in the game through
     * an interaction with any of the buttons with a number, it and the next similar methods
     * were later merged into one in the final CasinoWindow class
     */
    void rouletteBetNumber(const QString& toolButtonContent) {
        string betText = this->ui.betLineEdit->text().toStdString();
        if(!betText.empty()) {
            int amount = stoi(betText);
            this->roulette->rouletteBet(gambler, NUMBER, amount, stoi(toolButtonContent.toStdString()));
            this->refreshUI();
        }
    }

    void rouletteBetColumn(int number) {
        string betText = this->ui.betLineEdit->text().toStdString();
        if(!betText.empty()) {
            int amount = stoi(betText);
            this->roulette->rouletteBet(gambler, COLUMN, amount, number);
            this->refreshUI();
        }
    }

    void rouletteBetTwelve(int number) {
        string betText = this->ui.betLineEdit->text().toStdString();
        if(!betText.empty()) {
            int amount = stoi(betText);
            this->roulette->rouletteBet(gambler, TWELVE, amount, number);
            this->refreshUI();
        }
    }

    void rouletteBetHalf(int number) {
        string betText = this->ui.betLineEdit->text().toStdString();
        if(!betText.empty()) {
            int amount = stoi(betText);
            this->roulette->rouletteBet(gambler, HALF, amount, number);
            this->refreshUI();
        }
    }

    void rouletteBetEvenOdd(int number) {
        string betText = this->ui.betLineEdit->text().toStdString();
        if(!betText.empty()) {
            int amount = stoi(betText);
            this->roulette->rouletteBet(gambler, EVENODD, amount, number);
            this->refreshUI();
        }
    }

    void rouletteBetColor(int number) {
        string betText = this->ui.betLineEdit->text().toStdString();
        if(!betText.empty()) {
            int amount = stoi(betText);
            this->roulette->rouletteBet(gambler, COLOR, amount, number);
            this->refreshUI();
        }
    }

    /**
     * A very useful method that sets the color theme of the window to a nice looking dark mode
     */
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
    /**
     * Sets up the UI and calls all methods needed to set up all objects that the game needs to work,
     * afterwards it starts the timer that calls game and UI refreshes
     * @param parent Qt5 thing, unused but needed
     */
    explicit RouletteUITest(QWidget *parent = nullptr) {
        this->ui = Ui_MainWindow();
        this->ui.setupUi(this);

        this->linkButtons();
        this->setupObjects();
        this->setDarkMode();

        auto *timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &RouletteUITest::sendClockSignal);
        timer->start(100);
    }
    /**
     * Copy constructor, needed because by default QMainWindow is implicitly deleted after its creation
     */
    RouletteUITest(RouletteUITest const &test) {
        this->ui = test.ui;
    }

public slots:

    /**
     * Method called when the timer times out (which is every 100 milliseconds) that refreshes the game and the UI
     */
    void sendClockSignal() {
        auto elapsed = chrono::duration_cast<chrono::milliseconds>(chrono::steady_clock::now() - this->chronoTime);
        this->time = elapsed.count();
        this->roulette->advanceGame(this->time);
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
    RouletteUITest window = RouletteUITest();
    srand(time(nullptr));

    window.show();
    return QApplication::exec();
}