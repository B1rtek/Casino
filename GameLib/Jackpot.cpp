#include <ctime>
#include <stdexcept>
#include <algorithm>
#include "Jackpot.h"

/**
 * All constructors inherit the base Game class constructor
 * The only difference is that the minimumEntry is rounded down to the nearest multiple of 100
 */
Jackpot::Jackpot(int minimumEntry, const std::string &name) : Game(minimumEntry, name) {
    if (minimumEntry % 100 != 0) {
        throw std::invalid_argument("minimumEntry for Jackpot must be divisible by 100");
    }
    this->gameType = JACKPOT;
    this->minPlayers = 1;
}

Jackpot::Jackpot(Gambler *gambler, int minimumEntry, const std::string &name) : Game(gambler, minimumEntry,
                                                                                     name) {
    if (minimumEntry % 100 != 0) {
        throw std::invalid_argument("minimumEntry for Jackpot must be divisible by 100");
    }
    this->gameType = JACKPOT;
    this->minPlayers = 1;

}

Jackpot::Jackpot(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name) :
        Game(gamblers, minimumEntry, name) {
    if (minimumEntry % 100 != 0) {
        throw std::invalid_argument("minimumEntry for Jackpot must be divisible by 100");
    }
    this->gameType = JACKPOT;
    this->minPlayers = 1;

}

/**
 * Calculates winning chances for all gamblers
 */
void Jackpot::calculatePercent() {
    this->preorderPercentages.clear();
    int currentSum = 0;
    for (auto &i: this->gamblersPlaying) {
        currentSum += this->currentBets[i];
        preorderPercentages.push_back(double(currentSum) / double(this->totalBet));
    }
}

/**
 * Chooses a winner randomly based on the calculated chances
 */
std::vector<Gambler*> Jackpot::chooseTheWinners() noexcept {
    double random = double(rand()) / double(RAND_MAX);
    int i = 0;
    while (random > preorderPercentages[i] && i < preorderPercentages.size()) {
        ++i;
    }
    return {this->gamblersPlaying[i]};
}

/**
 * Advances the game by telling bots to bet
 */
void Jackpot::advanceGame(int millisecondsPassed) {
    Game::advanceGame(millisecondsPassed);
    if (this->inProgress) {
        if (this->targetTime <= millisecondsPassed) { // time for betting ended
            this->calculatePercent();
            this->lastGameWinners = this->chooseTheWinners();
            this->payTheWinners(this->lastGameWinners);
            this->removeBankruptPlayers();
            this->totalBet = 0;
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
            if(this->gamblersPlaying.size() >= 2) {
                this->startGame();
                // collect a minimum bet from everyone
                for (auto &gambler: this->gamblersPlaying) {
                    this->bet(gambler, this->minimumEntry / 100);
                }
                // give everyone 30 seconds for betting
                this->targetTime = millisecondsPassed + 30000;
            } else {
                this->targetTime = millisecondsPassed + 10000; // wait another 10 s for players
            }
        }
    }

}

/**
 * Removes a gambler from players and places them on the spectators list when they
 * run out of credits
 */
void Jackpot::removeBankruptPlayers() noexcept {
    for (auto &gambler: this->gamblersPlaying) {
        if (this->inGameMoney[gambler] < this->minimumEntry / 100) {
            gambler->leaveGame();
            gambler->spectate(this);
        }
    }
}

/**
 * Method used by the test Jackpot UI application to display current chances of winning for every gambler,
 * further improved with the getSortedPercentages() method defined below, which is used in the final Casino UI
 * @return map of Gambler* (s) and chances of winning corresponding to each of them in the game joining order
 */
std::map<Gambler *, double> Jackpot::getPercentages() noexcept {
    std::map<Gambler *, double> percentages;
    for (auto &gambler: this->gamblersPlaying) {
        if(this->totalBet == 0) {
            percentages[gambler] = 0.0;
        } else {
            percentages[gambler] = double(this->currentBets[gambler]) / double(this->totalBet) * 100.0;
        }
    }
    return percentages;
}

/**
 * Method used by the final Casino UI and CasinoWindow to display current chances of winning for every gambler,
 * which sorts the map received from getPercentages() by the percentage descending
 * @return vector of pairs of Gambler* (s) and their corresponding winning chances, sorted by percentage
 */
std::vector<std::pair<Gambler *, double>> Jackpot::getSortedPercentages() noexcept {
    std::map<Gambler *, double> percentages = this->getPercentages();
    std::vector<std::pair<Gambler*, double>> sortedPerecentages;
    for (auto &gamblerPercentagePair: percentages) {
        sortedPerecentages.emplace_back(gamblerPercentagePair.first, gamblerPercentagePair.second);
    }
    std::sort(sortedPerecentages.begin(), sortedPerecentages.end(),
         [](const std::pair<Gambler*, double> &one, const std::pair<Gambler*, double> &two) {
             return one.second > two.second;
         });
    return sortedPerecentages;
}


