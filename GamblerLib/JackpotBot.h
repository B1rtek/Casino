#ifndef CASINOGAME_JACKPOTBOT_H
#define CASINOGAME_JACKPOTBOT_H

#include "GamblerBot.h"

/**
 * Class representing a bot who's playing Jackpot
 */
class JackpotBot : public GamblerBot {
public:
    explicit JackpotBot(const std::string &name="");

    explicit JackpotBot(int balance, const std::string &name="");

    JackpotBot(int balance, Game *game, const std::string &name="");

    void makeAMove(int millisecondsPassed) noexcept override;
};


#endif //CASINOGAME_JACKPOTBOT_H
