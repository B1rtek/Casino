#ifndef CASINOGAME_GAMBLERBOT_H
#define CASINOGAME_GAMBLERBOT_H

#include "Gambler.h"

/**
 * Class adding features used exclusively by bots to the Gambler class
 */
class GamblerBot : public Gambler {
protected:
    int targetTime = 0;
    bool moveScheduled = false;
    Game *gameToJoin = nullptr;
public:
    explicit GamblerBot(const std::string &name="") noexcept;

    explicit GamblerBot(int balance, const std::string &name="") noexcept;

    GamblerBot(int balance, Game *game, const std::string &name="") noexcept;

    int getTargetTime() const noexcept;

    void scheduleGameJoin(Game *game) noexcept;

    void withdrawBalance(int amount) noexcept override {}

    void leaveOrJoin(int millisecondsPassed) noexcept;

    bool isMoveScheduled() const noexcept;
};


#endif //CASINOGAME_GAMBLERBOT_H
