#ifndef CASINOGAME_ROULETTEBOT_H
#define CASINOGAME_ROULETTEBOT_H

#include "GamblerBot.h"

class RouletteBot : public GamblerBot {
public:
    RouletteBot(const std::string &name = "");

    RouletteBot(int balance, const std::string &name = "");

    RouletteBot(int balance, Game *game, const std::string &name = "");

    void makeAMove(int millisecondsPassed) noexcept override;
};


#endif //CASINOGAME_ROULETTEBOT_H
