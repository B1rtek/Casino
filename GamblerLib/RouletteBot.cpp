#include "RouletteBot.h"

#include <random>
#include <Roulette.h>

RouletteBot::RouletteBot(const std::string &name) : GamblerBot(name) {}

RouletteBot::RouletteBot(int balance, const std::string &name) : GamblerBot(balance, name) {}

RouletteBot::RouletteBot(int balance, Game *game, const std::string &name) : GamblerBot(balance, game, name) {}

void RouletteBot::makeAMove(int millisecondsPassed) noexcept {
    if (this->gamePlayed->isInProgress()) {
        if (!this->moveScheduled) {
            this->targetTime = millisecondsPassed + 5000 + rand() % 5000;
            this->moveScheduled = true;
        } else if (this->targetTime <= millisecondsPassed) {
            int maxPart = 10;
            if (this->gamePlayed->getInGameMoney()[this] <= 10) {
                maxPart = 1;
            } else if (this->gamePlayed->getInGameMoney()[this] <= 100) {
                maxPart = 2;
            }
            int amountToBet = ((this->gamePlayed->getInGameMoney()[this] / maxPart) * (rand() % 100 + 1) / 100);
            int numberToBet = rand() % 37;
            int betType = rand() % 6;
            dynamic_cast<Roulette *>(this->gamePlayed)->rouletteBet(this, static_cast<RouletteBetType>(betType),
                                                                    amountToBet, numberToBet);
            this->moveScheduled = false;
        }
    }
}
