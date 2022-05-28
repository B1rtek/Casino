#ifndef CASINOGAME_ROULETTE_H
#define CASINOGAME_ROULETTE_H

#include "Game.h"

class Roulette : public Game {
public:
    explicit Roulette(int minimumEntry, const std::string &name = "");

    Roulette(Gambler *gambler, int minimumEntry, const std::string &name = "");

    Roulette(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name = "");
};


#endif //CASINOGAME_ROULETTE_H
