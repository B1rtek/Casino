#ifndef CASINOGAME_TESTTEXASBOT_H
#define CASINOGAME_TESTTEXASBOT_H

#include "GamblerBot.h"
#include "TexasHoldem.h"

class TestTexasBot : public GamblerBot {
public:
    explicit TestTexasBot(const std::string &name="");

    explicit TestTexasBot(int balance, const std::string &name="");

    TestTexasBot(int balance, Game *game, const std::string &name="");

    void makeAMove(int millisecondsPassed) noexcept override;
};


#endif //CASINOGAME_TESTTEXASBOT_H
