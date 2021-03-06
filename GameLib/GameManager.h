#ifndef CASINOGAME_GAMEMANAGER_H
#define CASINOGAME_GAMEMANAGER_H

#include "Game.h"
#include "Jackpot.h"
#include "TexasHoldem.h"
#include "Roulette.h"
#include "JackpotBot.h"
#include "TexasBot.h"
#include "RouletteBot.h"

/**
 * The GameManager class, keeps the whole casino logic running
 */
class GameManager {
    std::vector<Game*> games;
    std::vector<GamblerBot*> bots;
    Gambler *player;
    int lastMillis = 0;

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
