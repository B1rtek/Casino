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
    RouletteBet(RouletteBetType type, int number, int amount, Gambler *gambler) : type(type), number(number),
                                                                                  amount(amount), gambler(gambler), successful(false) {};

    RouletteBetType type;
    Gambler *gambler;
    int number, amount;
    bool successful = false;

    std::string getBetStringRepresentation() {
        std::string representation = this->gambler->getName() + ": ";
        switch (type) {
            case COLOR: {
                representation += number % 2 == 1 ? "Black, " : "Red, ";
            }
                break;
            case EVENODD: {
                representation += number % 2 == 1 ? "Odd, " : "Even, ";
            }
                break;
            case HALF: {
                representation += number <= 18 ? "1 to 18, " : "19 to 36, ";
            }
                break;
            case TWELVE: {
                if (number <= 12) representation += "1st 12, ";
                else if (number >= 25) representation += "3rd 12, ";
                else representation += "2nd 12, ";
            }
                break;
            case COLUMN: {
                if (number %3 == 1) representation += "Column 1, ";
                if (number %3 == 2) representation += "Column 2, ";
                if (number %3 == 0) representation += "Column 3, ";
            }
                break;
            case NUMBER: {
                representation += "Number " + std::to_string(number) + ", ";
            }
                break;
        }
        representation += std::to_string(amount);
        if(successful) {
            representation += " [WON]";
        }
        return representation;
    }
};

class Roulette : public Game {
    std::vector<RouletteBet> bets;

    virtual void rollTheNumber() noexcept;

    void checkAndPayBets() noexcept;

    void startGame() noexcept override;

protected:
    int lastNumberRolled = 0;

public:
    explicit Roulette(int minimumEntry, const std::string &name = "") noexcept;

    Roulette(Gambler *gambler, int minimumEntry, const std::string &name = "") noexcept;

    Roulette(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name = "") noexcept;

    void advanceGame(int millisecondsPassed) override;

    bool rouletteBet(Gambler *gambler, RouletteBetType betType, int amount, int number);

    std::vector<RouletteBet> getRouletteBets();

    int getLastRolledNumber() const noexcept;
};


#endif //CASINOGAME_ROULETTE_H
