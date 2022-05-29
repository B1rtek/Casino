#include "Roulette.h"

#include <random>

Roulette::Roulette(int minimumEntry, const std::string &name) noexcept: Game(minimumEntry, name) {}

Roulette::Roulette(Gambler *gambler, int minimumEntry, const std::string &name) noexcept: Game(gambler, minimumEntry,
                                                                                               name) {}

Roulette::Roulette(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name) noexcept:
        Game(gamblers, minimumEntry, name) {}

void Roulette::advanceGame(int millisecondsPassed) {
    if (this->inProgress) {
        if (this->targetTime <= millisecondsPassed) { // time for betting ended
            this->rollTheNumber();
            this->checkAndPayBets();
            this->removeBankruptPlayers();
            this->targetTime = millisecondsPassed + 30000; // new game begins in 30 seconds
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
            this->targetTime = millisecondsPassed + 60000; // give everyone 60 seconds for betting
        }
    }
}

void Roulette::rollTheNumber() noexcept {
    std::mt19937 mt(time(nullptr));
    this->lastNumberRolled = mt() % 37;
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
                if ((this->lastNumberRolled >= 1 && this->lastNumberRolled <= 18 && bet.number == 1) ||
                    (this->lastNumberRolled > 18 && bet.number > 1)) {
                    this->inGameMoney[bet.gambler] += 2 * bet.amount;
                    bet.successful = true;
                }
            }
                break;
            case TWELVE: {
                if ((this->lastNumberRolled >= 1 && this->lastNumberRolled <= 12 && bet.number == 1) ||
                    (this->lastNumberRolled >= 13 && this->lastNumberRolled <= 24 && bet.number == 13) ||
                    (this->lastNumberRolled >= 25 && bet.number == 25)) {
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
    if(this->inProgress && this->bet(gambler, amount)) {
        this->bets.emplace_back(betType, number, amount, gambler);
        return true;
    }
    return false;
}

std::vector<RouletteBet> Roulette::getRouletteBets() {
    return this->bets;
}


