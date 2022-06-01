#ifndef CASINOGAME_GAMEMANAGER_H
#define CASINOGAME_GAMEMANAGER_H

#include <vector>

#include "Game.h"
#include "Jackpot.h"
#include "TexasHoldem.h"
#include "Roulette.h"
#include "JackpotBot.h"
#include "TexasBot.h"
#include "RouletteBot.h"

class GameManager {
    std::vector<Game*> games;
    std::vector<GamblerBot*> bots;
    Gambler *player;

    void assignGameToBot(GamblerBot *bot) noexcept;

public:
    GameManager();

    void start();

    void advanceCasino(int millisecondsPassed);

    bool joinGame(int gameIndex);

    bool leaveGame();

    bool spectateGame(int gameIndex);

    bool stopSpectating();

    bool jackpotBet(int amount);

    bool texasHoldemFold();

    bool texasHoldemCall();

    bool texasHoldemRaise(int amount);

    bool rouletteBet(RouletteBetType betType, int number, int amount);

    std::vector<Game*> getGames() const noexcept;

    Gambler* getPlayer() const noexcept;

    virtual ~GameManager();
};


#endif //CASINOGAME_GAMEMANAGER_H
