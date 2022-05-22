#include "TexasBot.h"

TexasBot::TexasBot(const std::string &name) : GamblerBot(name) {}

TexasBot::TexasBot(int balance, const std::string &name) : GamblerBot(balance, name) {}

TexasBot::TexasBot(int balance, Game *game, const std::string &name) : GamblerBot(balance, game, name) {}

void TexasBot::makeAMove(int millisecondsPassed) noexcept {
    if (this->gamePlayed != nullptr) {
        if(dynamic_cast<TexasHoldem*>(this->gamePlayed)->getCurrentPlayer() != this) return;
        switch (millisecondsPassed % 3) {
            case 0: {
                dynamic_cast<TexasHoldem*>(this->gamePlayed)->fold(this);
            }
                break;
            case 1: {
                dynamic_cast<TexasHoldem*>(this->gamePlayed)->call(this);
            }
                break;
            case 2: {
                dynamic_cast<TexasHoldem*>(this->gamePlayed)->raise(this, 2);
            }
        }
    }
}
