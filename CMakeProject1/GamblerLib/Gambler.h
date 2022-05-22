#pragma once
#include <string>
#include <utility>
#include <vector>
#include <cmath>
#include <iostream>
#include <vector>

class Game;

class Shop
{
private:
    std::vector <std::pair<std::string, double>> items;
public:
    Shop() noexcept;
    std::vector <std::pair<std::string, double>> getItems() noexcept { return this->items; }
    void addItem(std::pair<std::string, double> item) noexcept { this->items.push_back(item); }
    void removeItem(std::string itemName) noexcept;
    double findItemValue(std::string itemName) noexcept;

    friend std::ostream& operator<<(std::ostream& os, const Shop& shop) noexcept;
};

class Player
{
protected:
    std::string name;
    double balance;
    std::vector<double> deposits;
    std::vector<double> withdrawals;
    std::vector<std::pair<double, std::string>> transactions;
    Game* playingGame{};
    Game* watchingGame{};
    bool bot = false;

public:
    Player() noexcept;
    Player(std::string name, double balance = 0) noexcept;

    std::string getName() const noexcept { return name; }
    double getBalance() const noexcept { return balance; }
    virtual std::vector<double> getDeposits() noexcept { return deposits; }
    virtual std::vector<double> getWithdrawals() noexcept { return withdrawals; }
    virtual std::vector<std::pair<double, std::string>> getTransactions() noexcept { return transactions; }
    Game* getGame() const noexcept { return this->playingGame; }
    Game* getWatchedGame() const noexcept { return this->watchingGame; }
    bool isBot() const noexcept { return this->bot; }

    bool joinGame(Game* game) noexcept;
    bool leaveGame() noexcept;

    bool watch(Game* game) noexcept;
    bool stopWatching() noexcept;

    void changeName(std::string name) noexcept { this->name = name; }
    virtual void setBot(bool setted) noexcept { this->bot = setted; }

    virtual void depositBalance(double amount) noexcept;
    virtual void withdrawBalance(double amount) noexcept;

    virtual double totalDeposited() noexcept;
    virtual double totalWithdrawed() noexcept;
    virtual double totalProfit() noexcept { return totalWithdrawed() - totalDeposited(); }

    std::vector<double> specificTransactions(std::string game) noexcept;
};

class Guest : public Player
{
private:
    double min_bet = 0.01;
    double max_bet = 10000;
public:
    // deposit max 100000
    // wyp³aty do max 1000 w jednej transakcji
    // ograniczenie widocznosci ostatnich wp³at do 10 (i wyp³at)
    // zablokowaæ dostêp do totalProfit(), totaldeposited(), totalwithdrawed()

    Guest() noexcept;
    Guest(std::string name, double balance = 0) noexcept;

    void depositBalance(double amount) noexcept override;
    void withdrawBalance(double amount) noexcept override;

    std::vector<double> getDeposits() noexcept override;
    std::vector<double> getWithdrawals() noexcept override;

    double totalDeposited() noexcept override { return -1; }
    double totalWithdrawed() noexcept override { return -1; }
    double totalProfit() noexcept override { return -1; }
};

class VIP : public Player
{
private:
    double min_bet = 1000;
    double max_bet = 100000;
    double safe = 0;
    std::vector<std::string> items;
public:
    // dostêp do statystyk innych osób (iloœæ balansu)
    // mo¿liwoœæ wp³acania i wyp³acania pieniêdzy do sejfu (brak œladu)
    // mo¿liwoœæ resetowania statystyk (zacieranie œladów)
    // mo¿liwoœæ kupowania ze sklepu nagród rzeczowych (bêdzie mo¿na je stawiaæ)

    VIP() noexcept;
    VIP(std::string name, double balance = 0) noexcept;

    double checkPlayerBalance(Player gracz) noexcept { return gracz.getBalance(); }

    std::vector<std::string> getItems() noexcept { return this->items; }
    void buyItem(Shop* shop, std::string itemName) noexcept;
    void sellItem(Shop* shop, std::string itemName) noexcept;

    void depositToSafe(double amount) noexcept;
    void withdrawFromSafe(double amount) noexcept;
    double getSafeValue() noexcept { return safe; }

    void resetStats() noexcept;
};

class TrialMode : public Player
{
private:
    double min_bet = 0.01;
    double max_bet = 100000;
    bool bot = true;
public:
    // brak mo¿liwoœci wyp³at
    // mo¿e tylko byæ botem i graæ z botami <- g³êbsza implementajca na póŸniejszym etapie projektu
    TrialMode() noexcept;
    TrialMode(std::string name, double balance = 0) noexcept;

    void setBot(bool setted) noexcept override {}
    void withdrawBalance(double amount) noexcept override {}
};

class SafePlayer : public Player
{
private:
    double min_bet = 0.01;
    double max_bet = 100;
public:
    // max deposit 300
    // max withdraw 100
    // ograniczenie widocznosci ostatnich wp³at do 5 (i wyp³at)
    // zablokowaæ dostêp do totalProfit(), totaldeposited(), totalwithdrawed()
    // mo¿liwoœæ zablokowania grania

    SafePlayer() noexcept;
    SafePlayer(std::string name, double balance = 0) noexcept;

    void depositBalance(double amount) noexcept override;
    void withdrawBalance(double amount) noexcept override;

    std::vector<double> getDeposits() noexcept override;
    std::vector<double> getWithdrawals() noexcept override;

    double totalDeposited() noexcept override { return -1; }
    double totalWithdrawed() noexcept override { return -1; }
    double totalProfit() noexcept override { return -1; }
};