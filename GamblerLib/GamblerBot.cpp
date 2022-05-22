//
// Created by skrze on 01.05.2022.
//

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
