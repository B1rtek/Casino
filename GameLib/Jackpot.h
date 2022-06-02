#ifndef CASINOGAME_JACKPOT_H
#define CASINOGAME_JACKPOT_H

#include "Game.h"

/**
 * The Jackpot game class, manages and represents a game of jackpot between Gamblers
 */
class Jackpot : public Game {
    std::vector<double> preorderPercentages;

    void calculatePercent();

    void removeBankruptPlayers() noexcept override;

    std::vector<Gambler*> chooseTheWinners() noexcept override;

public:
    explicit Jackpot(int minimumEntry, const std::string &name = "");

    Jackpot(Gambler *gambler, int minimumEntry, const std::string &name = "");

    Jackpot(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name = "");

    void advanceGame(int millisecondsPassed) override;

    std::map<Gambler*, double> getPercentages() noexcept;

    std::vector<std::pair<Gambler*, double>> getSortedPercentages() noexcept;
};


#endif //CASINOGAME_JACKPOT_H
