#ifndef PROI_4_KASYNO_GRA_GAMBLER_H
#define PROI_4_KASYNO_GRA_GAMBLER_H

#include <string>
#include <vector>
#include <cmath>
#include <utility>

class Game;

#include "Game.h"
#include "Shop.h"

enum GamblerType {
    PLAYER,
    ROULETTE_BOT,
    JACKPOT_BOT,
    TEXAS_BOT
};

/**
 * Gambler class, represents a base casino player, bots and human player classes inherit from it
 */
class Gambler {
protected:
    int balance;
    std::string name;
    std::vector<int> deposits;
    std::vector<int> withdrawals;
    std::vector<std::pair<int, std::string>> transactions;
    Game *gamePlayed = nullptr, *gameSpectated = nullptr;
    bool bot = false;
    GamblerType gamblerType = PLAYER;
public:
    explicit Gambler(std::string name = "") noexcept;

    explicit Gambler(int balance, std::string name = "") noexcept;

    Gambler(int balance, Game *game, std::string name = "") noexcept;

    virtual void makeAMove(int millisecondsPassed) noexcept;

    void addBalance(int amount) noexcept;

    void subtractBalance(int amount) noexcept;

    virtual void depositBalance(int amount) noexcept;

    virtual void withdrawBalance(int amount) noexcept;

    bool joinGame(Game *game) noexcept;

    bool leaveGame() noexcept;

    bool spectate(Game *game) noexcept;

    bool stopSpectating() noexcept;

    void setName(std::string newName) noexcept;

    void setBot(bool toSet) noexcept;

    std::string getName() const noexcept;

    int getBalance() const noexcept;

    virtual std::vector<int> getDeposits() const noexcept;

    virtual int totalDeposited() const noexcept;
    
    virtual std::vector<int> getWithdrawals() const noexcept;

    virtual int totalWithdrawed() const noexcept;
    
    virtual int totalProfit() const noexcept;
    
    virtual std::vector<std::pair<int, std::string>> getTransactions() const noexcept;

    std::vector<int> specificTransactions(std::string game) noexcept;
   
    Game *getCurrentGame() const noexcept;

    Game *getSpectatedGame() const noexcept;

    bool isBot() const noexcept;

    GamblerType getGamblerType() const noexcept;
};

/**
 * Guest class, represents a casino player with various limitations
 */
class Guest : public Gambler {
private:
    int max_bet = 10000;
public:
    // deposit max 100000
    // withdrawals max 1000 in one transaction
    // visibility of deposits and withdrawals to last 10
    // blocked access to totalProfit(), totalDeposited(), totalWithdrawed()

    explicit Guest(const std::string& name = "") noexcept;

    explicit Guest(int balance, const std::string& name = "") noexcept;

    Guest(int balance, Game* game, const std::string& name = "") noexcept;

    void depositBalance(int amount) noexcept override;

    void withdrawBalance(int amount) noexcept override;

    std::vector<int> getDeposits() const noexcept override;

    std::vector<int> getWithdrawals() const noexcept override;

    int totalDeposited() const noexcept override { return -1; }

    int totalWithdrawed() const noexcept override { return -1; }

    int totalProfit() const noexcept override { return -1; }
};

/**
 * VIP class, represents a VIP casino player with access to new things
 */
class VIP : public Gambler {
private:
    int safe = 0;
    std::vector<std::string> items;
public:
    // access to other people's balance visibility
    // access to safe (no traces)
    // ability to reset statistics (obliterating traces)
    // acces to the shop, with items VIP can play

    explicit VIP(const std::string &name = "") noexcept;

    explicit VIP(int balance, const std::string &name = "") noexcept;

    VIP(int balance, Game* game, const std::string &name = "") noexcept;

    int checkGamblerBalance(Gambler gracz) noexcept { return gracz.getBalance(); }

    std::vector<std::string> getItems() const noexcept { return this->items; }

    void buyItem(Shop *shop, std::string itemName) noexcept;

    void sellItem(Shop *shop, std::string itemName) noexcept;

    void depositToSafe(int amount) noexcept;

    void withdrawFromSafe(int amount) noexcept;

    int getSafeValue() const noexcept { return safe; }

    void resetStats() noexcept;
};

/**
 * SafeGambler class, represents a casino player who is afraid of big bets
 */
class SafeGambler : public Gambler {
private:
    int max_bet = 100;
public:
    // max deposit 300
    // max withdraw 100
    // limited visibility of recent deposits and withdrawals to 5
    // blocked access to totalProfit(), totalDeposited(), totalWithdrawed()
    // ability to block the account

    explicit SafeGambler(const std::string& name = "") noexcept;

    explicit SafeGambler(int balance, const std::string& name = "") noexcept;

    SafeGambler(int balance, Game* game, const std::string& name = "") noexcept;

    void depositBalance(int amount) noexcept override;

    void withdrawBalance(int amount) noexcept override;

    std::vector<int> getDeposits() const noexcept override;

    std::vector<int> getWithdrawals() const noexcept override;

    int totalDeposited() const noexcept override { return -1; }

    int totalWithdrawed() const noexcept override { return -1; }

    int totalProfit() const noexcept override { return -1; }
};

#endif //PROI_4_KASYNO_GRA_GAMBLER_H
