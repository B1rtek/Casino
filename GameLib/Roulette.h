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

    std::string getBetTypeString() {
        switch (type) {
            case COLOR: {
                return number % 2 == 1 ? "Black" : "Red";
            }
            case EVENODD: {
                return number % 2 == 1 ? "Odd" : "Even";
            }
            case HALF: {
                return number <= 18 ? "1 to 18" : "19 to 36";
            }
            case TWELVE: {
                if (number <= 12) return "1st 12";
                else if (number >= 25) return "3rd 12";
                else return "2nd 12";
            }
            case COLUMN: {
                if (number % 3 == 1) return "Column 1";
                if (number % 3 == 2) return "Column 2";
                if (number % 3 == 0) return "Column 3";
            }
            case NUMBER: {
                return "Number " + std::to_string(number);
            }
        }
        return {};
    }

    std::string getAmountString() {
        return std::to_string(amount);
    }

    std::string getSuccessString() {
        return successful ? "WON" : "LOST";
    }

    std::string getBetStringRepresentation() {
        std::string representation = this->gambler->getName() + ": ";
        representation += this->getBetTypeString() + ", ";
        representation += std::to_string(amount);
        if (successful) {
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

    void removeBankruptPlayers() noexcept override;

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
