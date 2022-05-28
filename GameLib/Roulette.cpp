#include "Roulette.h"

Roulette::Roulette(int minimumEntry, const std::string &name) : Game(minimumEntry, name) {}

Roulette::Roulette(Gambler *gambler, int minimumEntry, const std::string &name) : Game(gambler, minimumEntry, name) {}

Roulette::Roulette(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name) :
        Game(gamblers, minimumEntry, name) {}
