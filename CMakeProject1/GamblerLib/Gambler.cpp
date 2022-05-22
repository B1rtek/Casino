#include "Gambler.h"

// Shop
Shop::Shop() noexcept
{
    this->items = { {"Yacht", 50000}, {"Car", 20000}, {"Apartment", 100000}, {"Motor", 5000} };
}

void Shop::removeItem(std::string itemName) noexcept
{
    for (int i = 0; i < this->items.size(); i++)
    {
        if (this->items[i].first == itemName) this->items.erase(items.begin() + i); return;
    }
}

double Shop::findItemValue(std::string itemName) noexcept
{
    for (int i = 0; i < this->items.size(); i++)
    {
        if (this->items[i].first == itemName) return this->items[i].second;
    }
    return 0;
}

std::ostream& operator<<(std::ostream& os, Shop& shop) noexcept
{
    for (int i = 0; i < shop.getItems().size(); i++)
        os << shop.getItems()[i].first << " " << shop.getItems()[i].second << std::endl;
    return os;
}


// Player
Player::Player() noexcept
{
    name = "Player";
    balance = 0.0;
}

Player::Player(std::string name, double balance) noexcept
{
    this->name = name;
    if (balance <= 0) this->balance = 0;
    else
    {
        this->balance = balance;
        this->deposits.push_back(balance);
    }
}

void Player::depositBalance(double amount) noexcept
{
    this->balance += abs(amount);
    deposits.push_back(abs(amount));
}

void Player::withdrawBalance(double amount) noexcept
{
    if (abs(amount) <= this->balance)
    {
        this->balance -= abs(amount);
        withdrawals.push_back(abs(amount));
    }
}

double Player::totalDeposited() noexcept
{
    double sum = 0;
    for (int i = 0; i < deposits.size(); i++) sum += deposits[i];
    return sum;
}

double Player::totalWithdrawed() noexcept
{
    double sum = 0;
    for (int i = 0; i < withdrawals.size(); i++) sum += withdrawals[i];
    return sum;
}

std::vector<double> Player::specificTransactions(std::string game) noexcept
{
    std::vector<double> specific_transactions;
    for (int i = 0; i < transactions.size(); i++)
        if (transactions[i].second == game) specific_transactions.push_back(transactions[i].first);
    return specific_transactions;
}

bool Player::joinGame(Game* game) noexcept
{
    // na etapie projektu -> sprawdziæ warunek, czy gra pozwala na dostêp u¿ytkownikowi
    this->playingGame = game;
    return true;
}

bool Player::leaveGame() noexcept
{
    if (this->playingGame != nullptr)
    {
        this->playingGame = nullptr;
        return true;
    }
    return false;
}

bool Player::watch(Game* game) noexcept
{
    if (this->playingGame == nullptr)
    {
        this->watchingGame = game;
        return true;
    }
    return false;
}

bool Player::stopWatching() noexcept
{
    if (this->watchingGame != nullptr)
    {
        this->watchingGame = nullptr;
        return true;
    }
    return false;
}


// Guest
Guest::Guest() noexcept : Player() {}
Guest::Guest(std::string name, double balance) noexcept : Player(name, balance) {}

void Guest::depositBalance(double amount) noexcept
{
    if (abs(amount) <= 100000)
    {
        this->balance += abs(amount);
        deposits.push_back(abs(amount));
    }
}

void Guest::withdrawBalance(double amount) noexcept
{
    if (abs(amount) <= this->balance && abs(amount) <= 1000)
    {
        this->balance -= abs(amount);
        withdrawals.push_back(abs(amount));
    }
}

std::vector<double> Guest::getDeposits() noexcept
{
    std::vector<double> deposits;
    for (int i = 0; i < this->deposits.size(); i++)
    {
        deposits.push_back(this->deposits[i]);
        if (i == 10) break;
    }
    return deposits;
}

std::vector<double> Guest::getWithdrawals() noexcept
{
    std::vector<double> withdrawals;
    for (int i = 0; i < this->withdrawals.size(); i++)
    {
        withdrawals.push_back(this->withdrawals[i]);
        if (i == 10) break;
    }
    return withdrawals;
}

// VIP
VIP::VIP() noexcept : Player() {}
VIP::VIP(std::string name, double balance) noexcept : Player(name, balance) {}

void VIP::buyItem(Shop* shop, std::string itemName) noexcept
{
    double itemValue = shop->findItemValue(itemName);
    if (itemValue != 0 && itemValue < this->balance)
    {
        this->items.push_back(itemName);
        this->balance -= itemValue;
    }
}

void VIP::sellItem(Shop* shop, std::string itemName) noexcept
{
    double itemValue = shop->findItemValue(itemName);
    if (itemValue == 0) return;
    for (int i = 0; i < this->items.size(); i++)
    {
        if (this->items[i] == itemName)
        {
            this->items.erase(this->items.begin() + i);
            this->balance += itemValue * 0.9;
            return;
        }
    }
}

void VIP::depositToSafe(double amount) noexcept
{
    if (abs(amount) <= this->balance)
    {
        this->safe += abs(amount);
        this->balance -= abs(amount);
    }
}

void VIP::withdrawFromSafe(double amount) noexcept
{
    if (abs(amount) <= this->safe)
    {
        this->safe -= abs(amount);
        this->balance += abs(amount);
    }
}

void VIP::resetStats() noexcept
{
    this->deposits = {};
    this->withdrawals = {};
    this->transactions = {};
}

// TrialMode
TrialMode::TrialMode() noexcept : Player() {}
TrialMode::TrialMode(std::string name, double balance) noexcept : Player(name, balance) {}

// SafePlayer
SafePlayer::SafePlayer() noexcept : Player() {}
SafePlayer::SafePlayer(std::string name, double balance) noexcept : Player(name, balance) {}

void SafePlayer::depositBalance(double amount) noexcept
{
    if (abs(amount) <= 300)
    {
        this->balance += abs(amount);
        deposits.push_back(abs(amount));
    }
}

void SafePlayer::withdrawBalance(double amount) noexcept
{
    if (abs(amount) <= this->balance && abs(amount) <= 100)
    {
        this->balance -= abs(amount);
        withdrawals.push_back(abs(amount));
    }
}

std::vector<double> SafePlayer::getDeposits() noexcept
{
    std::vector<double> deposits;
    for (int i = 0; i < this->deposits.size(); i++)
    {
        deposits.push_back(this->deposits[i]);
        if (i == 5) break;
    }
    return deposits;
}

std::vector<double> SafePlayer::getWithdrawals() noexcept
{
    std::vector<double> withdrawals;
    for (int i = 0; i < this->withdrawals.size(); i++)
    {
        withdrawals.push_back(this->withdrawals[i]);
        if (i == 5) break;
    }
    return withdrawals;
}