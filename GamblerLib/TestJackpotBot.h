#ifndef CASINOGAME_TESTJACKPOTBOT_H
#define CASINOGAME_TESTJACKPOTBOT_H

#include "GamblerBot.h"

/**
 * Class representing a bot who's playing Jackpot
 */
class TestJackpotBot : public GamblerBot {
public:
    explicit TestJackpotBot(const std::string &name="");

    explicit TestJackpotBot(int balance, const std::string &name="");

    TestJackpotBot(int balance, Game *game, const std::string &name="");

    void makeAMove(int millisecondsPassed) noexcept override;
};


#endif //CASINOGAME_TESTJACKPOTBOT_H
