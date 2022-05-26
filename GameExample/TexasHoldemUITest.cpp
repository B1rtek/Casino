#include <QApplication>
#include <QtWidgets/QMainWindow>
#include "UITexasHoldemTest.h"
#include "TexasHoldem.h"
#include "TexasBot.h"

using namespace std;

class TexasHoldemUITest : public QMainWindow {
    Ui_MainWindow ui;
    TexasHoldem *texasHoldem;
    std::vector<Gambler*> bots;
    Gambler *gambler;

public:
    explicit TexasHoldemUITest(QWidget *parent = nullptr) {
        this->ui = Ui_MainWindow();
        this->ui.setupUi(this);
        this->ui.advanceTimeLineEdit->setText("30000");
        this->bots = {gambler, new TexasBot(1000, "Marcus"), new TexasBot(1000, "Tyler"), new TexasBot(1000, "Lina")};
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