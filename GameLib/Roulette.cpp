#include "Roulette.h"

#include <random>

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

void Roulette::advanceGame(int millisecondsPassed) {
    if (this->inProgress) {
        if (this->targetTime <= millisecondsPassed) { // time for betting ended
            this->inProgress = false;
            this->rollTheNumber();
            this->checkAndPayBets();
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
            this->startGame();
            this->targetTime = millisecondsPassed + 30000; // give everyone 30 seconds for betting
        }
    }
}

void Roulette::rollTheNumber() noexcept {
    this->lastNumberRolled = rand() % 37;
}

void Roulette::checkAndPayBets() noexcept {
    for (auto &bet: this->bets) {
        switch (bet.type) {
            case COLOR:
            case EVENODD: {
                if (this->lastNumberRolled % 2 == bet.number % 2 && this->lastNumberRolled != 0) {
                    this->inGameMoney[bet.gambler] += 2 * bet.amount;
                    bet.successful = true;
                }
            }
                break;
            case HALF: {
                if ((this->lastNumberRolled >= 1 && this->lastNumberRolled <= 18 && bet.number >= 1 && bet.number <= 18) ||
                    (this->lastNumberRolled > 18 && bet.number > 18)) {
                    this->inGameMoney[bet.gambler] += 2 * bet.amount;
                    bet.successful = true;
                }
            }
                break;
            case TWELVE: {
                if ((this->lastNumberRolled >= 1 && this->lastNumberRolled <= 12 && bet.number >= 1 && bet.number <= 12) ||
                    (this->lastNumberRolled >= 13 && this->lastNumberRolled <= 24 && bet.number >= 13 && bet.number <= 24) ||
                    (this->lastNumberRolled >= 25 && bet.number >= 25)) {
                    this->inGameMoney[bet.gambler] += 3 * bet.amount;
                    bet.successful = true;
                }
            }
                break;
            case COLUMN: {
                if (this->lastNumberRolled % 3 == bet.number % 3 && this->lastNumberRolled != 0) {
                    this->inGameMoney[bet.gambler] += 3 * bet.amount;
                    bet.successful = true;
                }
            }
                break;
            case NUMBER: {
                if (this->lastNumberRolled == bet.number) {
                    this->inGameMoney[bet.gambler] += 36 * bet.amount;
                    bet.successful = true;
                } else if (this->lastNumberRolled == 0) {
                    this->inGameMoney[bet.gambler] += bet.amount / 2;
                }
            }
                break;
        }
    }
}

void Roulette::startGame() noexcept {
    Game::startGame();
    this->bets.clear();
    for(auto &gambler: this->gamblersPlaying) {
        this->currentBets[gambler] = 0;
    }
}

bool Roulette::rouletteBet(Gambler *gambler, RouletteBetType betType, int amount, int number) {
    if(amount == 0) return false;
    if(this->inProgress && this->bet(gambler, amount)) {
        this->bets.emplace_back(betType, number, amount, gambler);
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

void Roulette::removeBankruptPlayers() noexcept {
    for(auto &gambler: this->gamblersPlaying) {
        if (this->inGameMoney[gambler] == 0) {
            this->currentBets[gambler] = 0;
            gambler->leaveGame();
            gambler->spectate(this);
        }
    }
}
