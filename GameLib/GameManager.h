#ifndef CASINOGAME_GAMEMANAGER_H
#define CASINOGAME_GAMEMANAGER_H

#include <vector>

#include "Game.h"
#include "Jackpot.h"
#include "TexasHoldem.h"
#include "Roulette.h"
#include "TestJackpotBot.h"
#include "TexasBot.h"
#include "RouletteBot.h"

class GameManager {
    std::vector<Game*> games;
    std::vector<GamblerBot*> bots;
    Gambler *player;

    void assignGameToBot(GamblerBot *bot) noexcept;

public:
    GameManager();

    void advanceCasino(int millisecondsPassed);

    virtual ~GameManager();
};


#endif //CASINOGAME_GAMEMANAGER_H
