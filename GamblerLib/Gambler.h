#ifndef PROI_4_KASYNO_GRA_GAMBLER_H
#define PROI_4_KASYNO_GRA_GAMBLER_H

class Game;

#include <string>

#include "Game.h"

/**
 * Gambler class, represents a base casino player, bots and human player classes inherit from it
 */
class Gambler {
protected:
    int balance;
    std::string name;
    Game *gamePlayed{}, *gameSpectated{};
    bool bot = false;
public:
    explicit Gambler(std::string name = "") noexcept;

    explicit Gambler(int balance, std::string name = "") noexcept;

    Gambler(int balance, Game *game, std::string name = "") noexcept;

    virtual void makeAMove(int millisecondsPassed) noexcept;

    void addBalance(int amount) noexcept;

    void subtractBalance(int amount) noexcept;

    bool joinGame(Game *game) noexcept;

    bool leaveGame() noexcept;

    bool spectate(Game *game) noexcept;

    bool stopSpectating() noexcept;

    void setName(std::string newName) noexcept;

    void setBot(bool toSet) noexcept;

    std::string getName() const noexcept;

    int getBalance() const noexcept;

    Game *getCurrentGame() const noexcept;

    Game *getSpectatedGame() const noexcept;

    bool isBot() const noexcept;
};

#pragma once

#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <iostream>
#include <vector>

class Game;

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

class Player {
protected:
    std::string name;
    int balance;
    std::vector<int> deposits;
    std::vector<int> withdrawals;
    std::vector<std::pair<int, std::string>> transactions;
    Game *playingGame{};
    Game *watchingGame{};
    bool bot = false;

public:
    Player() noexcept;

    Player(std::string name, int balance = 0) noexcept;

    std::string getName() const noexcept { return name; }

    int getBalance() const noexcept { return balance; }

    virtual std::vector<int> getDeposits() noexcept { return deposits; }

    virtual std::vector<int> getWithdrawals() noexcept { return withdrawals; }

    virtual std::vector<std::pair<int, std::string>> getTransactions() noexcept { return transactions; }

    Game *getGame() const noexcept { return this->playingGame; }

    Game *getWatchedGame() const noexcept { return this->watchingGame; }

    bool isBot() const noexcept { return this->bot; }

    bool joinGame(Game *game) noexcept;

    bool leaveGame() noexcept;

    bool watch(Game *game) noexcept;

    bool stopWatching() noexcept;

    void changeName(std::string name) noexcept { this->name = name; }

    virtual void setBot(bool setted) noexcept { this->bot = setted; }

    virtual void depositBalance(int amount) noexcept;

    virtual void withdrawBalance(int amount) noexcept;

    virtual int totalDeposited() noexcept;

    virtual int totalWithdrawed() noexcept;

    virtual int totalProfit() noexcept { return totalWithdrawed() - totalDeposited(); }

    std::vector<int> specificTransactions(std::string game) noexcept;
};

class Guest : public Player {
private:
    int min_bet = 0.01;
    int max_bet = 10000;
public:
    // deposit max 100000
    // wypłaty do max 1000 w jednej transakcji
    // ograniczenie widocznosci ostatnich wpłat do 10 (i wypłat)
    // zablokować dostęp do totalProfit(), totaldeposited(), totalwithdrawed()

    Guest() noexcept;

    Guest(std::string name, int balance = 0) noexcept;

    void depositBalance(int amount) noexcept override;

    void withdrawBalance(int amount) noexcept override;

    std::vector<int> getDeposits() noexcept override;

    std::vector<int> getWithdrawals() noexcept override;

    int totalDeposited() noexcept override { return -1; }

    int totalWithdrawed() noexcept override { return -1; }

    int totalProfit() noexcept override { return -1; }
};

class VIP : public Player {
private:
    int min_bet = 1000;
    int max_bet = 100000;
    int safe = 0;
    std::vector<std::string> items;
public:
    // dostęp do statystyk innych osób (ilość balansu)
    // możliwość wpłacania i wypłacania pieniędzy do sejfu (brak śladu)
    // możliwość resetowania statystyk (zacieranie śladów)
    // możliwość kupowania ze sklepu nagród rzeczowych (będzie można je stawiać)

    VIP() noexcept;

    VIP(std::string name, int balance = 0) noexcept;

    int checkPlayerBalance(Player gracz) noexcept { return gracz.getBalance(); }

    std::vector<std::string> getItems() noexcept { return this->items; }

    void buyItem(Shop *shop, std::string itemName) noexcept;

    void sellItem(Shop *shop, std::string itemName) noexcept;

    void depositToSafe(int amount) noexcept;

    void withdrawFromSafe(int amount) noexcept;

    int getSafeValue() noexcept { return safe; }

    void resetStats() noexcept;
};

class TrialMode : public Player {
private:
    int min_bet = 0.01;
    int max_bet = 100000;
    bool bot = true;
public:
    // brak możliwości wypłat
    // może tylko być botem i grać z botami <- głębsza implementajca na późniejszym etapie projektu
    TrialMode() noexcept;

    TrialMode(std::string name, int balance = 0) noexcept;

    void setBot(bool setted) noexcept override {}

    void withdrawBalance(int amount) noexcept override {}
};

class SafePlayer : public Player {
private:
    int min_bet = 0.01;
    int max_bet = 100;
public:
    // max deposit 300
    // max withdraw 100
    // ograniczenie widocznosci ostatnich wpłat do 5 (i wypłat)
    // zablokować dostęp do totalProfit(), totaldeposited(), totalwithdrawed()
    // możliwość zablokowania grania

    SafePlayer() noexcept;

    SafePlayer(std::string name, int balance = 0) noexcept;

    void depositBalance(int amount) noexcept override;

    void withdrawBalance(int amount) noexcept override;

    std::vector<int> getDeposits() noexcept override;

    std::vector<int> getWithdrawals() noexcept override;

    int totalDeposited() noexcept override { return -1; }

    int totalWithdrawed() noexcept override { return -1; }

    int totalProfit() noexcept override { return -1; }
};

#endif //PROI_4_KASYNO_GRA_GAMBLER_H
