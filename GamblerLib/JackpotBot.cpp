#include "JackpotBot.h"

JackpotBot::JackpotBot(const std::string &name) : GamblerBot(name) {
    this->gamblerType = JACKPOT_BOT;
}

JackpotBot::JackpotBot(int balance, const std::string &name) : GamblerBot(balance, name) {
    this->gamblerType = JACKPOT_BOT;
}

JackpotBot::JackpotBot(int balance, Game *game, const std::string &name) : GamblerBot(balance, game, name) {
    this->gamblerType = JACKPOT_BOT;
}

/**
 * Makes the bot bet additional money if the algorithm decides to do so
 * @param millisecondsPassed
 */
void JackpotBot::makeAMove(int millisecondsPassed) noexcept {
    if (this->gamePlayed->isInProgress()) {
        if (!this->moveScheduled) {
            this->targetTime = millisecondsPassed + rand() % 1000;
            this->moveScheduled = true;
        } else if (this->targetTime <= millisecondsPassed) {
            bool willBet = !(rand() % 2);
            if (this->gamePlayed->getTotalBet() > this->gamePlayed->getCurrentBets()[this] * 20) { // chances less than 5%
                willBet = true;
            }
            if (willBet) {
                int maxPart = 50;
                if (this->gamePlayed->getInGameMoney()[this] <= 10) {
                    maxPart = 1;
                } else if (this->gamePlayed->getInGameMoney()[this] <= 100) {
                    maxPart = 2;
                }
                int amountToBet = ((this->gamePlayed->getInGameMoney()[this] / maxPart) * (rand() % 100 + 1) / 100);
                this->gamePlayed->bet(this, amountToBet);
            }
            this->moveScheduled = false;
        }
    }
}
