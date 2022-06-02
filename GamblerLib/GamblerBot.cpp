#include "GamblerBot.h"

GamblerBot::GamblerBot(const std::string &name) noexcept: Gambler(name) {
    this->bot = true;
}

GamblerBot::GamblerBot(int balance, const std::string &name) noexcept: Gambler(balance, name) {
    this->bot = true;
}

GamblerBot::GamblerBot(int balance, Game *game, const std::string &name) noexcept: Gambler(balance, game, name) {
    this->bot = true;
}

int GamblerBot::getTargetTime() const noexcept {
    return this->targetTime;
}

/**
 * Schedules time for the bot at which it'll attempt joining the selected game
 * @param game game that will be potentially joined after the scheduled time
 * @param millisecondsPassed milliseconds passed since the Casino started
 */
void GamblerBot::scheduleGameJoin(Game *game, int millisecondsPassed) noexcept {
    this->gameToJoin = game;
    this->targetTime = millisecondsPassed + rand() % 20000;
    this->moveScheduled = true;
}

/**
 * Called with each casino refresh to make the bot join the planned game or leave their current game
 * @param millisecondsPassed milliseconds passed since the Casino started
 */
void GamblerBot::leaveOrJoin(int millisecondsPassed) noexcept {
    if(this->gamePlayed == nullptr && this->gameToJoin != nullptr && this->targetTime <= millisecondsPassed && rand() % 2 == 0) {
        this->joinGame(gameToJoin);
    } else if (this->gamePlayed != nullptr && !this->gamePlayed->isInProgress()) {
        if(rand() % 100 == 0) {
            this->leaveGame();
        }
    }
    this->moveScheduled = false;
}

bool GamblerBot::isMoveScheduled() const noexcept {
    return this->moveScheduled;
}
