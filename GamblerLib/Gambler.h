#ifndef PROI_4_KASYNO_GRA_GAMBLER_H
#define PROI_4_KASYNO_GRA_GAMBLER_H

#include <string>
#include <vector>
#include <cmath>
#include <utility>
#include <iostream>

class Game;

#include "Game.h"

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
};

class Shop {
private:
    std::vector<std::pair<std::string, int>> items;
public:
    Shop() noexcept;

    std::vector<std::pair<std::string, int>> getItems() noexcept { return this->items; }

    void addItem(std::pair<std::string, int> item) noexcept { this->items.push_back(item); }

    void removeItem(std::string itemName) noexcept;

    int findItemValue(std::string itemName) noexcept;

    friend std::ostream &operator<<(std::ostream &os, const Shop &shop) noexcept;
};

class Guest : public Gambler {
private:
    int max_bet = 10000;
public:
    // deposit max 100000
    // wyplaty do max 1000 w jednej transakcji
    // ograniczenie widocznosci ostatnich wplat do 10 (i wyplat)
    // zablokowany dostep do totalProfit(), totalDeposited(), totalWithdrawed()

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

class VIP : public Gambler {
private:
    int max_bet = 100000;
    int safe = 0;
    std::vector<std::string> items;
public:
    // dostep do statystyk innych osob (ilosc balansu)
    // mozliwosc wplacania i wyplacania pieniedzy do sejfu (brak sladu)
    // mozliwosc resetowania statystyk (zacieranie sladow)
    // mozliwosc kupowania ze sklepu nagrod rzeczowych (bedzie mozna nimi grac <- do implementacji)

    explicit VIP(const std::string &name = "") noexcept;

    explicit VIP(int balance, const std::string &name = "") noexcept;

    VIP(int balance, Game* game, const std::string &name = "") noexcept;

    int checkGamblerBalance(Gambler gracz) noexcept { return gracz.getBalance(); }

    std::vector<std::string> getItems() noexcept { return this->items; }

    void buyItem(Shop *shop, std::string itemName) noexcept;

    void sellItem(Shop *shop, std::string itemName) noexcept;

    void depositToSafe(int amount) noexcept;

    void withdrawFromSafe(int amount) noexcept;

    int getSafeValue() noexcept { return safe; }

    void resetStats() noexcept;
};

class SafeGambler : public Gambler {
private:
    int max_bet = 100;
public:
    // max deposit 300
    // max withdraw 100
    // ograniczenie widocznosci ostatnich wplat do 5 (i wyplat)
    // zablokowany dostep do totalProfit(), totalDeposited(), totalWithdrawed()
    // mozliwosc zablokowania grania

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
