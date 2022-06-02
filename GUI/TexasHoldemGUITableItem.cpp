#include "TexasHoldemGUITableItem.h"

TexasHoldemGUITableItem::TexasHoldemGUITableItem(QLabel *labelName, QLabel *labelBalance, QLabel *labelBet, QLabel *labelCard1, QLabel *labelCard2) : labelName(labelName), labelBalance(labelBalance), labelBet(labelBet), labelCard1(labelCard1), labelCard2(labelCard2) {}

/**
 * Refreshes the display in the UI according to new data about the gambler from the Game
 * @param game game the the gambler is playing
 * @param gambler gambler that this display is corresponding to
 * @param player application user, needed to identify cards of other gamblers and not display them
 */
void TexasHoldemGUITableItem::updateItem(TexasHoldem *game, Gambler *gambler, Gambler *player) {
    if(game == nullptr || gambler == nullptr || player == nullptr) {
        this->labelName->setText(QString());
        this->labelBalance->setText(QString());
        this->labelBet->setText(QString());
        this->labelCard1->setText(QString());
        this->labelCard2->setText(QString());
    } else {
        std::string toDisplay = gambler->getName();
        if(game->getCurrentDealer() == gambler) {
            toDisplay += " [D]";
        }
        if(game->getCurrentPlayer() == gambler) {
            toDisplay += " [C]";
        }
        if(!game->getNotFolded()[gambler]) {
            toDisplay += " [FOLD]";
        }
        if(this->labelName->text().toStdString() != toDisplay) {
            this->labelName->setText(QString(toDisplay.c_str()));
        }
        toDisplay = std::to_string(game->getInGameMoney()[gambler]);
        if(this->labelBalance->text().toStdString() != toDisplay) {
            this->labelBalance->setText(QString(toDisplay.c_str()));
        }
        toDisplay = std::to_string(game->getCurrentBets()[gambler]);
        if(this->labelBet->text().toStdString() != toDisplay) {
            this->labelBet->setText(QString(toDisplay.c_str()));
        }
        if(gambler == player || game->getGameState() == SHOWDOWN) {
            toDisplay = Card::toString(*game->getGamblersCards()[gambler][0]);
            if(this->labelCard1->text().toStdString() != toDisplay) {
                this->labelCard1->setText(QString(toDisplay.c_str()));
            }
            toDisplay = Card::toString(*game->getGamblersCards()[gambler][1]);
            if(this->labelCard2->text().toStdString() != toDisplay) {
                this->labelCard2->setText(QString(toDisplay.c_str()));
            }
        } else {
            toDisplay = Card::toString(*CardGame::noneCard);
            if(this->labelCard1->text().toStdString() != toDisplay) {
                this->labelCard1->setText(QString(toDisplay.c_str()));
            }
            if(this->labelCard2->text().toStdString() != toDisplay) {
                this->labelCard2->setText(QString(toDisplay.c_str()));
            }
        }
    }
}
