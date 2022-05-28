#include "TestJackpotBot.h"

TestJackpotBot::TestJackpotBot(const std::string &name) : GamblerBot(name) {}

TestJackpotBot::TestJackpotBot(int balance, const std::string &name) : GamblerBot(balance, name) {}

TestJackpotBot::TestJackpotBot(int balance, Game *game, const std::string &name) : GamblerBot(balance, game, name) {}

/**
 * Makes the bot bet additional money if the algorithm decides to do so
 * @param millisecondsPassed
 */
void TestJackpotBot::makeAMove(int millisecondsPassed) noexcept {
    if (this->gamePlayed != nullptr) { // if they are playing
        if (this->gamePlayed->isInProgress()) {
            // if bot's chances are less than 1%, bet
            if (this->gamePlayed->getTotalBet() > this->gamePlayed->getCurrentBets()[this] * 100) {
                // % of in game money to bet determined by millisecondsPassed
                int percentToBet = millisecondsPassed % 100 + 1;
                int toBet = this->gamePlayed->getInGameMoney()[this] * 100 / percentToBet;
                this->gamePlayed->bet(this, toBet);
            } else if (millisecondsPassed % 10000 == 0) { // otherwise there's a small chance for betting anyways
                int percentToBet = (millisecondsPassed / 10000) % 100 + 1;
                int toBet = this->gamePlayed->getInGameMoney()[this] * 100 / percentToBet;
                this->gamePlayed->bet(this, toBet);
            }
        } else {
            // if the bot is close to entry money, it leaves, otherwise there is a very small chance that they will leave
            if (this->gamePlayed->getMinimumEntry() * 2 > this->gamePlayed->getInGameMoney()[this] ||
                millisecondsPassed % 20000 == 0) {
                this->leaveGame();
            }
        }
    } else if (this->gameSpectated != nullptr && millisecondsPassed % 100000 == 0) { // if they are spectating there's a small chance that they'll leave
        this->stopSpectating();
    }
}
