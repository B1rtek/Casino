#ifndef CASINOGAME_TEXASBOT_H
#define CASINOGAME_TEXASBOT_H

#include "GamblerBot.h"
#include "TexasHoldem.h"

class TexasBot : public GamblerBot {
public:
    explicit TexasBot(const std::string &name="");

    explicit TexasBot(int balance, const std::string &name="");

    TexasBot(int balance, Game *game, const std::string &name="");

    void makeAMove(int millisecondsPassed) noexcept override;
};


#endif //CASINOGAME_TEXASBOT_H
