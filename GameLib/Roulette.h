#ifndef CASINOGAME_ROULETTE_H
#define CASINOGAME_ROULETTE_H

#include "Game.h"

enum RouletteBetType {
    COLOR,
    EVENODD,
    HALF,
    TWELVE,
    COLUMN,
    NUMBER
};

struct RouletteBet {
    RouletteBet(RouletteBetType type, int number, int amount) : type(type), number(number), amount(amount) {};

    RouletteBetType type;
    Gambler *gambler;
    int number, amount;
    bool successful = false;

    std::string getBetStringRepresentation() {
        std::string representation = this->gambler->getName() + ": ";
        switch (type) {
            case COLOR: {
                representation = number == 1 ? "Black, " : "Red, ";
            }
                break;
            case EVENODD: {
                representation = number == 1 ? "Odd, " : "Even, ";
            }
                break;
            case HALF: {
                representation = number == 1 ? "1 to 18, " : "19 to 36, ";
            }
                break;
            case TWELVE: {
                if (number == 1) representation = "1st 12, ";
                if (number == 13) representation = "2nd 12, ";
                if (number == 25) representation = "3rd 12, ";
            }
                break;
            case COLUMN: {
                if (number == 1) representation = "Column 1, ";
                if (number == 2) representation = "Column 2, ";
                if (number == 3) representation = "Column 3, ";
            }
                break;
            case NUMBER: {
                representation = "Number " + std::to_string(number) + ", ";
            }
                break;
        }
        representation += std::to_string(amount);
        return representation;
    }
};

class Roulette : public Game {
    int lastNumberRolled = 0;
    std::vector<RouletteBet> bets;

    void rollTheNumber() noexcept;

    void checkAndPayBets() noexcept;

public:
    void startGame() noexcept override;

public:
    explicit Roulette(int minimumEntry, const std::string &name = "") noexcept;

    Roulette(Gambler *gambler, int minimumEntry, const std::string &name = "") noexcept;

    Roulette(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name = "") noexcept;

    void advanceGame(int millisecondsPassed) override;


};


#endif //CASINOGAME_ROULETTE_H
