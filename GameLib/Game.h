#ifndef PROI_4_KASYNO_GRA_GAME_H
#define PROI_4_KASYNO_GRA_GAME_H

#include <vector>
#include <map>
#include <set>
#include <climits>
#include <string>

class Gambler;

#include "Gambler.h"

/**
 * Enum used to identify the type of the game in the GameManager
 */
enum GameType {
    TEXAS_HOLDEM,
    ROULETTE,
    JACKPOT
};

/**
 * Game class, the base class for all casino games, implements methods used by all games
 */
class Game {
protected:
    std::vector<Gambler *> gamblersPlaying;
    std::set<Gambler *> spectators;
    std::map<Gambler *, int> currentBets, inGameMoney;
    int minimumEntry = 0, totalBet = 0, targetTime = 30000, maxPlayers = 100, minPlayers = 2, lastMillis = 0, lastMoveMillis = 0; // game starts 30 seconds after manager starts
    std::string name;
    bool inProgress = false;
    std::vector<Gambler*> lastGameWinners;
    GameType gameType;

    virtual void removeBankruptPlayers() noexcept;

    virtual std::vector<Gambler*> chooseTheWinners() noexcept;

public:
    explicit Game(int minimumEntry, std::string name="") noexcept;

    Game(Gambler* gambler, int minimumEntry, std::string name="") noexcept;

    Game(const std::vector<Gambler*>& gamblers, int minimumEntry, std::string name="") noexcept;

    virtual void startGame() noexcept;

    virtual void advanceGame(int millisecondsPassed);

    bool bet(Gambler *gambler, int amount) noexcept;

    void payTheWinners(const std::vector<Gambler *>& winners) noexcept;

    virtual bool addPlayer(Gambler *gambler) noexcept;

    virtual bool removePlayer(Gambler *gambler) noexcept;

    bool addSpectator(Gambler *gambler) noexcept;

    void removeSpectator(Gambler *gambler) noexcept;

    std::map<Gambler *, int> getCurrentBets() const noexcept;

    std::map<Gambler *, int> getInGameMoney() const noexcept;

    std::vector<Gambler *> getPlayers() const noexcept;

    std::set<Gambler *> getSpectators() const noexcept;

    int getMinimumEntry() const noexcept;

    int getTotalBet() const noexcept;

    std::string getName() const noexcept;

    bool isInProgress() const noexcept;

    int getTargetTime() const noexcept;

    std::vector<Gambler*> getLastGameWinners() const noexcept;

    GameType getGameType() const noexcept;

    std::string getPlayerCountStr() const noexcept;

    std::string getGameSituationDescription() const noexcept;

    virtual bool unjammingPerformed(Gambler *player) noexcept;
};


#endif //PROI_4_KASYNO_GRA_GAME_H
