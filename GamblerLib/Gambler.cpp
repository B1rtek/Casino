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
    this->balance += amount;
    this->transactions.emplace_back(amount, this->getCurrentGame()->getName());
}

/**
 * Subtracts balance from the gambler's account
 * @param amount amount of balance to remove, the balance will be subtracted until it reaches zero
 */
void Gambler::subtractBalance(int amount) noexcept {
    this->transactions.emplace_back(-std::min(amount, this->balance), this->getCurrentGame()->getName());
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

// Shop
Shop::Shop() noexcept {
    this->items = {{"Yacht",     50000},
                   {"Car",       20000},
                   {"Apartment", 100000},
                   {"Motor",     5000}};
}

void Shop::removeItem(std::string itemName) noexcept {
    for (int i = 0; i < this->items.size(); i++) {
        if (this->items[i].first == itemName) this->items.erase(items.begin() + i);
        return;
    }
}

int Shop::findItemValue(std::string itemName) noexcept {
    for (int i = 0; i < this->items.size(); i++) {
        if (this->items[i].first == itemName) return this->items[i].second;
    }
    return 0;
}

std::ostream &operator<<(std::ostream &os, Shop &shop) noexcept {
    for (int i = 0; i < shop.getItems().size(); i++)
        os << shop.getItems()[i].first << " " << shop.getItems()[i].second << std::endl;
    return os;
}


// Player
Player::Player() noexcept {
    name = "Player";
    balance = 0.0;
}

Player::Player(std::string name, int balance) noexcept {
    this->name = name;
    if (balance <= 0) this->balance = 0;
    else {
        this->balance = balance;
        this->deposits.push_back(balance);
    }
}

void Player::depositBalance(int amount) noexcept {
    this->balance += abs(amount);
    deposits.push_back(abs(amount));
}

void Player::withdrawBalance(int amount) noexcept {
    if (abs(amount) <= this->balance) {
        this->balance -= abs(amount);
        withdrawals.push_back(abs(amount));
    }
}

int Player::totalDeposited() noexcept {
    int sum = 0;
    for (int i = 0; i < deposits.size(); i++) sum += deposits[i];
    return sum;
}

int Player::totalWithdrawed() noexcept {
    int sum = 0;
    for (int i = 0; i < withdrawals.size(); i++) sum += withdrawals[i];
    return sum;
}

std::vector<int> Player::specificTransactions(std::string game) noexcept {
    std::vector<int> specific_transactions;
    for (int i = 0; i < transactions.size(); i++)
        if (transactions[i].second == game) specific_transactions.push_back(transactions[i].first);
    return specific_transactions;
}

bool Player::joinGame(Game *game) noexcept {
    // na etapie projektu -> sprawdzić warunek, czy gra pozwala na dostęp użytkownikowi
    this->playingGame = game;
    return true;
}

bool Player::leaveGame() noexcept {
    if (this->playingGame != nullptr) {
        this->playingGame = nullptr;
        return true;
    }
    return false;
}

bool Player::watch(Game *game) noexcept {
    if (this->playingGame == nullptr) {
        this->watchingGame = game;
        return true;
    }
    return false;
}

bool Player::stopWatching() noexcept {
    if (this->watchingGame != nullptr) {
        this->watchingGame = nullptr;
        return true;
    }
    return false;
}


// Guest
Guest::Guest() noexcept: Player() {}

Guest::Guest(std::string name, int balance) noexcept: Player(name, balance) {}

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

std::vector<int> Guest::getDeposits() noexcept {
    std::vector<int> deposits;
    for (int i = 0; i < this->deposits.size(); i++) {
        deposits.push_back(this->deposits[i]);
        if (i == 10) break;
    }
    return deposits;
}

std::vector<int> Guest::getWithdrawals() noexcept {
    std::vector<int> withdrawals;
    for (int i = 0; i < this->withdrawals.size(); i++) {
        withdrawals.push_back(this->withdrawals[i]);
        if (i == 10) break;
    }
    return withdrawals;
}

// VIP
VIP::VIP() noexcept: Player() {}

VIP::VIP(std::string name, int balance) noexcept: Player(name, balance) {}

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

// TrialMode
TrialMode::TrialMode() noexcept: Player() {}

TrialMode::TrialMode(std::string name, int balance) noexcept: Player(name, balance) {}

// SafePlayer
SafePlayer::SafePlayer() noexcept: Player() {}

SafePlayer::SafePlayer(std::string name, int balance) noexcept: Player(name, balance) {}

void SafePlayer::depositBalance(int amount) noexcept {
    if (abs(amount) <= 300) {
        this->balance += abs(amount);
        deposits.push_back(abs(amount));
    }
}

void SafePlayer::withdrawBalance(int amount) noexcept {
    if (abs(amount) <= this->balance && abs(amount) <= 100) {
        this->balance -= abs(amount);
        withdrawals.push_back(abs(amount));
    }
}

std::vector<int> SafePlayer::getDeposits() noexcept {
    std::vector<int> deposits;
    for (int i = 0; i < this->deposits.size(); i++) {
        deposits.push_back(this->deposits[i]);
        if (i == 5) break;
    }
    return deposits;
}

std::vector<int> SafePlayer::getWithdrawals() noexcept {
    std::vector<int> withdrawals;
    for (int i = 0; i < this->withdrawals.size(); i++) {
        withdrawals.push_back(this->withdrawals[i]);
        if (i == 5) break;
    }
    return withdrawals;
}
