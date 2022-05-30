#include "Game.h"

#include <algorithm>

/**
 * Creates the game
 * @param name name of the game (optional)
 */
Game::Game(int minimumEntry, std::string name) noexcept: minimumEntry(minimumEntry), name(std::move(name)) {}

/**
 * Creates a game with a gambler in it
 * @param gambler gambler that joins the game on creation
 * @param name name of the game (optional)
 */
Game::Game(Gambler *gambler, int minimumEntry, std::string name) noexcept: minimumEntry(minimumEntry),
                                                                           name(std::move(name)) {
    if (gambler != nullptr) {
        gambler->joinGame(this);
    }
}

/**
 * Creates a game with all gamblers from the vector in it
 * @param gambler gamblers that join the game on creation
 * @param name name of the game (optional)
 */
Game::Game(const std::vector<Gambler *> &gamblers, int minimumEntry, std::string name) noexcept: minimumEntry(
        minimumEntry), name(std::move(name)) {
    for (auto gambler: gamblers) {
        if (gambler != nullptr) {
            gambler->joinGame(this);
        }
    }
}

/**
 * Function choosing the winners, to be implemented by subclasses
 */
std::vector<Gambler *> Game::chooseTheWinners() noexcept { return {}; }

/**
 * Function removing the bankrupt players
 */
void Game::removeBankruptPlayers() noexcept {}

/**
 * Starts the game by setting inProgress to true
 */
void Game::startGame() noexcept {
    this->inProgress = true;
}

/**
 * Advances the in-game timer and all actions that depend on it
 * Implementation is left to the subclasses
 */
void Game::advanceGame(int millisecondsPassed) {}

/**
 * Bets the given amount of money
 * @param gambler gambler who's betting
 * @param amount amount to bet which will be deducted from in-game money
 * @return true if the bet went through, false otherwise
 */
bool Game::bet(Gambler *gambler, int amount) noexcept {
    if (gambler == nullptr || !this->inProgress) {
        return false;
    }
    if (gambler->getCurrentGame() != this) {
        return false;
    }
    if (amount <= this->inGameMoney[gambler]) {
        this->inGameMoney[gambler] -= amount;
        this->currentBets[gambler] += amount;
        this->totalBet += amount;
        return true;
    }
    return false;
}

/**
 * Gives winnings to the winners of the game and zeroes out the bets
 */
void Game::payTheWinners(const std::vector<Gambler *>& winners) noexcept {
    int toPay = this->totalBet / int(winners.size());
    for (auto &gambler: winners) {
        this->inGameMoney[gambler] += toPay;
    }
    for(auto &gambler: this->gamblersPlaying) {
        this->currentBets[gambler] = 0;
    }
    this->inProgress = false;
    this->totalBet = this->totalBet - toPay * int(winners.size());
}

/**
 * Adds a player to the game by putting them in the playing gamblers vector and placing their bet in the current bets pool
 * @param gambler gambler to add to the game
 * @return true if the addition was successful, false otherwise
 * The game can be only joined if the gambler has the minimum entry amount available
 * This method should not be used to make the gambler join the game - instead Gambler's
 * joinGame() should be used, as it adds information about the game to the Gambler AND calls this method
 */
bool Game::addPlayer(Gambler *gambler) noexcept {
    if (gambler == nullptr || this->inProgress) {
        return false;
    }
    if (gambler->getCurrentGame() != nullptr || gambler->getSpectatedGame() != nullptr) {
        return false;
    }
    if (gambler->getBalance() > this->minimumEntry) {
        this->gamblersPlaying.push_back(gambler);
        this->currentBets[gambler] = 0;
        this->inGameMoney[gambler] = this->minimumEntry;
        gambler->subtractBalance(this->minimumEntry);
        return true;
    }
    return false;
}

/**
 * Removes a player from the game
 * @param gambler gambler to remove
 * @return true if the removal was successful, false otherwise
 * A gambler can only be removed if they aren't in any game (have a bet == 0)
 * This method should not be used to make the gambler leave the game - instead Gambler's
 * leaveGame() should be used, as it adds information about the game to the Gambler AND calls this method
 */
bool Game::removePlayer(Gambler *gambler) noexcept {
    if (gambler == nullptr || this->inProgress) {
        return false;
    }
    if (this->currentBets[gambler] == 0) {
        this->gamblersPlaying.erase(std::remove(this->gamblersPlaying.begin(), this->gamblersPlaying.end(), gambler),
                                    this->gamblersPlaying.end());
        this->currentBets.erase(this->currentBets.find(gambler));
        gambler->addBalance(this->inGameMoney[gambler]);
        this->inGameMoney.erase(this->inGameMoney.find(gambler));
        return true;
    }
    return false;
}

/**
 * Adds a spectator to the game
 * @param gambler gambler to add to the game
 * @return true if the spectator was successfully added, false otherwise
 * This method shouldn't be used directly, instead it should be called by making
 * the Gambler join as spectator by calling their spectate() method, which calls this method
 */
bool Game::addSpectator(Gambler *gambler) noexcept {
    if (gambler == nullptr) {
        return false;
    }
    if (this->spectators.count(gambler)) {
        return false;
    }
    if (gambler->getCurrentGame() == nullptr && gambler->getSpectatedGame() == nullptr) {
        this->spectators.insert(gambler);
        return true;
    }
    return false;
}

/**
 * Removes a spectator from the game
 * @param gambler gambler to remove from the game
 * This method shouldn't be used directly, instead it should be called by making
 * the Gambler leave as spectator by calling their stopSpectating() method, which calls this method
 */
void Game::removeSpectator(Gambler *gambler) noexcept {
    this->spectators.erase(gambler);
}

std::map<Gambler *, int> Game::getCurrentBets() const noexcept {
    return this->currentBets;
}

std::map<Gambler *, int> Game::getInGameMoney() const noexcept {
    return this->inGameMoney;
}

std::vector<Gambler *> Game::getPlayers() const noexcept {
    return this->gamblersPlaying;
}

std::set<Gambler *> Game::getSpectators() const noexcept {
    return this->spectators;
}

int Game::getTotalBet() const noexcept {
    return this->totalBet;
}

int Game::getMinimumEntry() const noexcept {
    return this->minimumEntry;
}

std::string Game::getName() const noexcept {
    return this->name;
}

bool Game::isInProgress() const noexcept {
    return this->inProgress;
}

int Game::getTargetTime() const noexcept {
    return this->targetTime;
}

std::vector<Gambler *> Game::getLastGameWinners() const noexcept {
    return this->lastGameWinners;
}

GameType Game::getGameType() const noexcept {
    return this->gameType;
}
