#include "Roulette.h"

#include <random>

/**
 * All constructors are inherited from the base Game class, Roulette constructors additionally set the gameType
 * field to ROULETTE, it's used by the GameManager to assign games of the correct types to bots
 */
Roulette::Roulette(int minimumEntry, const std::string &name) noexcept: Game(minimumEntry, name) {
    this->gameType = ROULETTE;
}

Roulette::Roulette(Gambler *gambler, int minimumEntry, const std::string &name) noexcept: Game(gambler, minimumEntry,
                                                                                               name) {
    this->gameType = ROULETTE;
}

Roulette::Roulette(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name) noexcept:
        Game(gamblers, minimumEntry, name) {
    this->gameType = ROULETTE;
}

/**
 * Method that gets called from the GameManager and changes the state of the game and triggers moves from all
 * bots who are playing
 * @param millisecondsPassed millisecondsPassed since the start of the Casino
 */
void Roulette::advanceGame(int millisecondsPassed) {
    Game::advanceGame(millisecondsPassed);
    if (this->inProgress) {
        if (this->targetTime <= millisecondsPassed) { // time for betting ended
            this->rollTheNumber();
            this->checkAndPayBets();
            this->inProgress = false;
            this->removeBankruptPlayers();
            this->targetTime = millisecondsPassed + 10000; // new game begins in 10 seconds
        } else {
            for (auto &gambler: this->gamblersPlaying) {
                if (gambler->isBot()) {
                    gambler->makeAMove(millisecondsPassed);
                }
            }
        }
    } else {
        if (this->targetTime <= millisecondsPassed) {
            if(this->gamblersPlaying.size() >= 1) {
                this->startGame();
                this->targetTime = millisecondsPassed + 15000; // give everyone 15 seconds for betting
            } else {
                this->targetTime = millisecondsPassed + 10000; // wait another 10 s for a player
            }

        }
    }
}

void Roulette::rollTheNumber() noexcept {
    this->lastNumberRolled = rand() % 37;
}

/**
 * Iterates through all bets placed during the betting time and pays out winnings from the ones who were won
 * Before it does that though it places a random bet for everyone who failed to bet in the provided time
 */
void Roulette::checkAndPayBets() noexcept {
    // if someone didn't bet, bet a random amount of their balance as a fee for playing the game :)
    for(auto &gambler: this->gamblersPlaying) {
        if(this->currentBets[gambler] == 0) {
            int amountToBet = std::max(((this->getInGameMoney()[gambler] / 10) * (rand() % 100 + 1) / 100), 1);
            int numberToBet = rand() % 37;
            int betType = rand() % 6;
            this->rouletteBet(gambler, static_cast<RouletteBetType>(betType), amountToBet, numberToBet);
        }
    }
    for (auto &bet: this->bets) {
        switch (bet.type) {
            case COLOR:
            case EVENODD: {
                if (this->lastNumberRolled % 2 == bet.number % 2 && this->lastNumberRolled != 0) {
                    this->inGameMoney[bet.gambler] += 2 * bet.amount;
                    bet.gambler->addTransaction(2 * bet.amount, this->name);
                    bet.successful = true;
                }
            }
                break;
            case HALF: {
                if ((this->lastNumberRolled >= 1 && this->lastNumberRolled <= 18 && bet.number >= 1 && bet.number <= 18) ||
                    (this->lastNumberRolled > 18 && bet.number > 18)) {
                    this->inGameMoney[bet.gambler] += 2 * bet.amount;
                    bet.gambler->addTransaction(2 * bet.amount, this->name);
                    bet.successful = true;
                }
            }
                break;
            case TWELVE: {
                if ((this->lastNumberRolled >= 1 && this->lastNumberRolled <= 12 && bet.number >= 1 && bet.number <= 12) ||
                    (this->lastNumberRolled >= 13 && this->lastNumberRolled <= 24 && bet.number >= 13 && bet.number <= 24) ||
                    (this->lastNumberRolled >= 25 && bet.number >= 25)) {
                    this->inGameMoney[bet.gambler] += 3 * bet.amount;
                    bet.gambler->addTransaction(3 * bet.amount, this->name);

                    bet.successful = true;
                }
            }
                break;
            case COLUMN: {
                if (this->lastNumberRolled % 3 == bet.number % 3 && this->lastNumberRolled != 0) {
                    this->inGameMoney[bet.gambler] += 3 * bet.amount;
                    bet.gambler->addTransaction(3 * bet.amount, this->name);
                    bet.successful = true;
                }
            }
                break;
            case NUMBER: {
                if (this->lastNumberRolled == bet.number) {
                    this->inGameMoney[bet.gambler] += 36 * bet.amount;
                    bet.gambler->addTransaction(36 * bet.amount, this->name);
                    bet.successful = true;
                } else if (this->lastNumberRolled == 0) {
                    this->inGameMoney[bet.gambler] += bet.amount / 2;
                    bet.gambler->addTransaction(bet.amount / 2, this->name);
                }
            }
                break;
        }
    }
}

/**
 * Starts the game by zeroing out the bets and calling the base class' startGame() method
 */
void Roulette::startGame() noexcept {
    Game::startGame();
    this->bets.clear();
    for(auto &gambler: this->gamblersPlaying) {
        this->currentBets[gambler] = 0;
    }
}

/**
 * Places a bet in the Roulette game according to the given parameters
 * @param gambler gambler who is placing the bet
 * @param betType type of the bet placed (Color, Column, Number etc)
 * @param amount amount of money bet
 * @param number number that was selected to represent the bet
 * @return true if the bet was successfully placed, false otherwise
 *
 * @param number is interpreted later in the win checking process as the correct bet - for example bet
 * of type Half for number 5 indicates that this bet was a 1:1 bet for the 1st half of the board,
 * another example would be a Column bet for 22, which indicates a 2:1 bet placed for the second column
 */
bool Roulette::rouletteBet(Gambler *gambler, RouletteBetType betType, int amount, int number) {
    if(amount == 0) return false;
    if(this->inProgress && this->bet(gambler, amount)) {
        this->bets.emplace_back(betType, number, amount, gambler);
        this->lastMoveMillis = this->lastMillis;
        return true;
    }
    return false;
}

std::vector<RouletteBet> Roulette::getRouletteBets() {
    return this->bets;
}

int Roulette::getLastRolledNumber() const noexcept {
    return this->lastNumberRolled;
}

/**
 * Removes all players who ran out of money (with the threshold being 0)
 */
void Roulette::removeBankruptPlayers() noexcept {
    for(auto &gambler: this->gamblersPlaying) {
        this->currentBets[gambler] = 0;
        if (this->inGameMoney[gambler] == 0) {
            gambler->leaveGame();
            gambler->spectate(this);
        }
    }
}
