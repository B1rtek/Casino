#ifndef CASINOGAME_JACKPOT_H
#define CASINOGAME_JACKPOT_H

#include "Game.h"

class Jackpot : public Game {
    std::vector<double> preorderPercentages;

    void calculatePercent();

    void removeBankruptPlayers() noexcept override;

    Gambler* chooseTheWinner() noexcept override;

public:
    explicit Jackpot(int minimumEntry, const std::string &name = "");

    Jackpot(Gambler *gambler, int minimumEntry, const std::string &name = "");

    Jackpot(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name = "");

    void advanceGame(int millisecondsPassed) override;

    Gambler* getLastGameWinner() const noexcept;

    std::map<Gambler*, double> getPercentages() noexcept;
};


#endif //CASINOGAME_JACKPOT_H
