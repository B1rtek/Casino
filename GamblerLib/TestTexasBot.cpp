#include "TestTexasBot.h"

TestTexasBot::TestTexasBot(const std::string &name) : GamblerBot(name) {}

TestTexasBot::TestTexasBot(int balance, const std::string &name) : GamblerBot(balance, name) {}

TestTexasBot::TestTexasBot(int balance, Game *game, const std::string &name) : GamblerBot(balance, game, name) {}

void TestTexasBot::makeAMove(int millisecondsPassed) noexcept {
    if (this->gamePlayed != nullptr) {
        if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentPlayer() != this) return;
        if (!this->moveScheduled) {
            this->targetTime = millisecondsPassed + 300;
            this->moveScheduled = true;
        } else if (this->targetTime <= millisecondsPassed) {
            switch (millisecondsPassed % 3) {
                case 0: {
                    if (millisecondsPassed % 7 == 0) {
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                    }
                }
                    break;
                case 1: {
                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                }
                    break;
                case 2: {
                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, 5);
                }
            }
            this->moveScheduled = false;
        }
    }
}
