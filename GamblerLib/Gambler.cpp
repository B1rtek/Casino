#include "Gambler.h"

/**
 * Creates a Gambler with 0 balance
 * @param name name of the Gambler, optional
 */
Gambler::Gambler(std::string name) noexcept: balance(0), name(std::move(name)) {}

/**
 * Creates a Gambler with the provided balance
 * @param balance balance with which the gambler will be created
 * @param name name of the Gambler, optional
 */
Gambler::Gambler(int balance, std::string name) noexcept: balance(balance), name(std::move(name)) {
    if (balance > 0) this->deposits.push_back(balance);
}

/**
 * Creates a Gambler with the provided balance and adds him to the provided game
 * @param balance balance with which the gambler will be created
 * @param game game that the Gambler will immediately join after creation
 * @param name name of the Gambler, optional
 */
Gambler::Gambler(int balance, Game *game, std::string name) noexcept {
    this->balance = balance;
    if (balance > 0) this->deposits.push_back(balance);
    this->name = std::move(name);
    this->joinGame(game);
}

/**
 * Method used by bots to move in games
 * @param millisecondsPassed milliseconds passed since the last time the manager class
 * sent an advancement message to all games
 */
void Gambler::makeAMove(int millisecondsPassed) noexcept {}

/**
 * Adds balance to the gambler's account
 * @param amount amount of balance to add
 */
void Gambler::addBalance(int amount) noexcept {
    std::string gameName = this->gamePlayed == nullptr ? "Balance added" : this->gamePlayed->getName();
    this->transactions.emplace_back(amount, gameName);
    this->balance += amount;
}

/**
 * Subtracts balance from the gambler's account
 * @param amount amount of balance to remove, the balance will be subtracted until it reaches zero
 */
void Gambler::subtractBalance(int amount) noexcept {
    std::string gameName = this->gamePlayed == nullptr ? "Joined Game" : this->gamePlayed->getName();
    this->transactions.emplace_back(-std::min(amount, this->balance), gameName);
    this->balance = std::max(this->balance - amount, 0);
}

/**
 * Depositing balance by the gambler
 * @param amount amount of balance to deposit
 */
void Gambler::depositBalance(int amount) noexcept {
    this->balance += abs(amount);
    deposits.push_back(abs(amount));
}

/**
 * Withdrawing balance by the gambler
 * @param amount amount of balance to withdraw, must be lower than Gambler balance
 */
void Gambler::withdrawBalance(int amount) noexcept {
    if (abs(amount) <= this->balance) {
        this->balance -= abs(amount);
        withdrawals.push_back(abs(amount));
    }
}

/**
 * Makes the gambler join the provided game
 * @param game game to join
 * @return true if the game has been successfully joined, false otherwise
 */
bool Gambler::joinGame(Game *game) noexcept {
    if (game == nullptr || this->gamePlayed != nullptr || this->gameSpectated != nullptr) {
        return false;
    }
    if (game->addPlayer(this)) {
        this->gamePlayed = game;
        return true;
    }
    return false;
}

/**
 * Makes the gambler leave the current game
 * @return true if the gambler successfully leaves the game, false otherwise
 */
bool Gambler::leaveGame() noexcept {
    if (this->gamePlayed != nullptr) {
        if (this->gamePlayed->removePlayer(this)) {
            this->gamePlayed = nullptr;
            return true;
        }
    }
    return false;
}

/**
 * Makes the gambler spectate a game
 * @param game game to join as spectator
 * @return true if the gambler successfully became a spectator, false otherwise
 */
bool Gambler::spectate(Game *game) noexcept {
    if (this->gamePlayed == nullptr && game != nullptr) {
        if (this->gameSpectated != nullptr) {
            this->stopSpectating();
        }
        game->addSpectator(this);
        this->gameSpectated = game;
        return true;
    }
    return false;
}

/**
 * Makes the gambler stop spectating the current game
 * @return true if the game wass successfully left, false otherwise
 */
bool Gambler::stopSpectating() noexcept {
    if (this->gameSpectated != nullptr) {
        this->gameSpectated->removeSpectator(this);
        this->gameSpectated = nullptr;
        return true;
    }
    return false;
}

/**
 * Method that will be used by bot subclasses to set themselves as bots
 * @param toSet value that will be assigned to field bot
 * It is defined in the base class because advanceGame() will be checking isBot() to
 * determine what happens next
 */
void Gambler::setBot(bool toSet) noexcept {
    this->bot = toSet;
}

void Gambler::setName(std::string newName) noexcept {
    this->name = std::move(newName);
}

std::string Gambler::getName() const noexcept {
    return this->name;
}

int Gambler::getBalance() const noexcept {
    return this->balance;
}

std::vector<int> Gambler::getDeposits() const noexcept {
    return this->deposits;
}

int Gambler::totalDeposited() const noexcept {
    int sum = 0;
    for (int i = 0; i < deposits.size(); i++) sum += deposits[i];
    return sum;
}

std::vector<int> Gambler::getWithdrawals() const noexcept {
    return this->withdrawals;
}

int Gambler::totalWithdrawed() const noexcept {
    int sum = 0;
    for (int i = 0; i < withdrawals.size(); i++) sum += withdrawals[i];
    return sum;
}

int Gambler::totalProfit() const noexcept {
    return this->totalWithdrawed() - this->totalDeposited();
}

std::vector<std::pair<int, std::string>> Gambler::getTransactions() const noexcept {
    return this->transactions;
}

/**
 * Method that returns vector of transactions in the selected game
 * @param game name of the game (string)
 * @return vector of ints (transactions' values)
 */
std::vector<int> Gambler::specificTransactions(std::string game) noexcept {
    std::vector<int> specific_transactions;
    for (int i = 0; i < transactions.size(); i++)
        if (transactions[i].second == game) specific_transactions.push_back(transactions[i].first);
    return specific_transactions;
}

Game *Gambler::getCurrentGame() const noexcept {
    return this->gamePlayed;
}

Game *Gambler::getSpectatedGame() const noexcept {
    return this->gameSpectated;
}

bool Gambler::isBot() const noexcept {
    return this->bot;
}

// Guest
Guest::Guest(const std::string& name) noexcept : Gambler(name) {}

Guest::Guest(int balance, const std::string& name) noexcept : Gambler(balance, name) {}

Guest::Guest(int balance, Game* game, const std::string& name) noexcept : Gambler(balance, game, name) {}

void Guest::depositBalance(int amount) noexcept {
    if (abs(amount) <= 100000) {
        this->balance += abs(amount);
        deposits.push_back(abs(amount));
    }
}

void Guest::withdrawBalance(int amount) noexcept {
    if (abs(amount) <= this->balance && abs(amount) <= 1000) {
        this->balance -= abs(amount);
        withdrawals.push_back(abs(amount));
    }
}

std::vector<int> Guest::getDeposits() const noexcept {
    std::vector<int> deposits;
    for (int i = 0; i < this->deposits.size(); i++) {
        deposits.push_back(this->deposits[i]);
        if (i == 10) break;
    }
    return deposits;
}

std::vector<int> Guest::getWithdrawals() const noexcept {
    std::vector<int> withdrawals;
    for (int i = 0; i < this->withdrawals.size(); i++) {
        withdrawals.push_back(this->withdrawals[i]);
        if (i == 10) break;
    }
    return withdrawals;
}

// VIP
VIP::VIP(const std::string& name) noexcept : Gambler(name) {}

VIP::VIP(int balance, const std::string& name) noexcept : Gambler(balance, name) {}

VIP::VIP(int balance, Game* game, const std::string& name) noexcept : Gambler(balance, game, name) {}

void VIP::buyItem(Shop *shop, std::string itemName) noexcept {
    int itemValue = shop->findItemValue(itemName);
    if (itemValue != 0 && itemValue < this->balance) {
        this->items.push_back(itemName);
        this->balance -= itemValue;
    }
}

void VIP::sellItem(Shop *shop, std::string itemName) noexcept {
    int itemValue = shop->findItemValue(itemName);
    if (itemValue == 0) return;
    for (int i = 0; i < this->items.size(); i++) {
        if (this->items[i] == itemName) {
            this->items.erase(this->items.begin() + i);
            this->balance += itemValue * 0.9;
            return;
        }
    }
}

void VIP::depositToSafe(int amount) noexcept {
    if (abs(amount) <= this->balance) {
        this->safe += abs(amount);
        this->balance -= abs(amount);
    }
}

void VIP::withdrawFromSafe(int amount) noexcept {
    if (abs(amount) <= this->safe) {
        this->safe -= abs(amount);
        this->balance += abs(amount);
    }
}

void VIP::resetStats() noexcept {
    this->deposits = {};
    this->withdrawals = {};
    this->transactions = {};
}

// SafeGambler
SafeGambler::SafeGambler(const std::string& name) noexcept : Gambler(name) {}

SafeGambler::SafeGambler(int balance, const std::string& name) noexcept : Gambler(balance, name) {}

SafeGambler::SafeGambler(int balance, Game* game, const std::string& name) noexcept : Gambler(balance, game, name) {}

void SafeGambler::depositBalance(int amount) noexcept {
    if (abs(amount) <= 300) {
        this->balance += abs(amount);
        deposits.push_back(abs(amount));
    }
}

void SafeGambler::withdrawBalance(int amount) noexcept {
    if (abs(amount) <= this->balance && abs(amount) <= 100) {
        this->balance -= abs(amount);
        withdrawals.push_back(abs(amount));
    }
}

std::vector<int> SafeGambler::getDeposits() const noexcept {
    std::vector<int> deposits;
    for (int i = 0; i < this->deposits.size(); i++) {
        deposits.push_back(this->deposits[i]);
        if (i == 5) break;
    }
    return deposits;
}

std::vector<int> SafeGambler::getWithdrawals() const noexcept {
    std::vector<int> withdrawals;
    for (int i = 0; i < this->withdrawals.size(); i++) {
        withdrawals.push_back(this->withdrawals[i]);
        if (i == 5) break;
    }
    return withdrawals;
}
