#include "GameManager.h"

GameManager::GameManager() = default;

void GameManager::start() {
    this->games = {
            new Jackpot(1000, "Jackpot"),
            new Jackpot(5000, "Jackpot++"),
            new Jackpot(10000, "Jackpot#"),
            new TexasHoldem(1000, "Texas Holdem"),
            new TexasHoldem(5000, "Texas Holdem++"),
            new TexasHoldem(10000, "Texas Holdem#"),
            new Roulette(1000, "Roulette"),
            new Roulette(5000, "Roulette++"),
            new Roulette(10000, "Roulette#")
    };
    // there will be 5 gamblers per each game at the start, all players start with 15k
    this->bots = {
            new JackpotBot(15000, "Aki Kimura"),
            new JackpotBot(15000, "Brad Rogers"),
            new JackpotBot(15000, "Carmen Mendez"),
            new JackpotBot(15000, "Murff"),
            new JackpotBot(15000, "Neville"),
            new JackpotBot(15000, "Nikki Morris"),
            new JackpotBot(15000, "Dirt"),
            new JackpotBot(15000, "Manu"),
            new JackpotBot(15000, "GMAC"),
            new JackpotBot(15000, "Wolf"),
            new JackpotBot(15000, "Yumi"),
            new JackpotBot(15000, "Udo Roth"),
            new JackpotBot(15000, "Tommy"),
            new JackpotBot(15000, "Samson"),
            new JackpotBot(15000, "Ray Krieger"),
            new TexasBot(15000, "Chase Linh"),
            new TexasBot(15000, "Chau Wu"),
            new TexasBot(15000, "Big Lou"),
            new TexasBot(15000, "Eugene James"),
            new TexasBot(15000, "Gallo Rivera"),
            new TexasBot(15000, "Hector Maio"),
            new TexasBot(15000, "Ho Seun"),
            new TexasBot(15000, "Isabel Diaz"),
            new TexasBot(15000, "Jack Rourke"),
            new TexasBot(15000, "Vince Kilic"),
            new TexasBot(15000, "Sal Mustela"),
            new TexasBot(15000, "Rachel Teller"),
            new TexasBot(15000, "Nate Denver"),
            new TexasBot(15000, "Natalia Nova"),
            new TexasBot(15000, "Marcus Blackwell"),
            new RouletteBot(15000, "Clarence Callahan"),
            new RouletteBot(15000, "Eva Torres"),
            new RouletteBot(15000, "Frank Mercer"),
            new RouletteBot(15000, "Hector Domingo"),
            new RouletteBot(15000, "Ryan Cooper"),
            new RouletteBot(15000, "Jonathan Cross"),
            new RouletteBot(15000, "Kenji"),
            new RouletteBot(15000, "Lina Navarro"),
            new RouletteBot(15000, "Marcus Weir"),
            new RouletteBot(15000, "Tyler Morgan"),
            new RouletteBot(15000, "Nakai-San"),
            new RouletteBot(15000, "Toru Sato"),
            new RouletteBot(15000, "Ryo Watanabe"),
            new RouletteBot(15000, "Nikki"),
            new RouletteBot(15000, "Darius"),
            new JackpotBot(15000, "Amy"),
            new TexasBot(15000, "Mia Townsend"),
            new JackpotBot(15000, "Dino Brewster"),
            new RouletteBot(15000, "JessicaMiller"),
            new TexasBot(15000, "Rog"),
            new JackpotBot(15000, "Ravindra Chaudhry"),
            new RouletteBot(15000, "Shinichi Morohoshi"),
            new JackpotBot(15000, "Robyn"),
            new TexasBot(15000, "Jaimin Shah"),
            new RouletteBot(15000, "Rose Largo"),
            new TexasBot(15000, "Wes Allen"),
            new RouletteBot(15000, "Travis"),
            new JackpotBot(15000, "Tobey Marshall"),
            new TexasBot(15000, "Keira Harrison"),
            new RouletteBot(15000, "Mitko Vasilev"),
            new TexasBot(15000, "Ronald McCrea"),
            new JackpotBot(15000, "Colin"),
            new RouletteBot(15000, "Zack Maio"),
            new JackpotBot(15000, "Izzy"),
            new TexasBot(15000, "Caleb Reece"),
            new JackpotBot(15000, "Danny Shaw"),
            new TexasBot(15000, "Victor Vasquez"),
            new RouletteBot(15000, "Alex Strachan"),
            new JackpotBot(15000, "Angie"),
            new RouletteBot(15000, "Spike"),
            new JackpotBot(15000, "Sean McAlister"),
            new TexasBot(15000, "Karl Smit"),
            new RouletteBot(15000, "Frankie Beaumont"),
            new RouletteBot(15000, "Rebecca Dawson"),
            new TexasBot(15000, "Kira Nakazato")
    };
    this->player = new Gambler(15000, "YOU");
    for (auto &bot: bots) {
        this->assignGameToBot(bot);
    }
}

void GameManager::assignGameToBot(GamblerBot *bot) noexcept {
    int gameNumber;
    switch (bot->getGamblerType()) {
        case ROULETTE_BOT:
            gameNumber = rand() % 3 + 6;
            break;
        case JACKPOT_BOT:
            gameNumber = rand() % 3;
            break;
        case TEXAS_BOT:
            gameNumber = rand() % 3 + 3;
            break;
    }
    bot->scheduleGameJoin(this->games[gameNumber], this->lastMillis);
}

void GameManager::advanceCasino(int millisecondsPassed) {
    this->lastMillis = millisecondsPassed;
    for (auto &bot: this->bots) {
        if (bot->getCurrentGame() == nullptr) {
            if (bot->isMoveScheduled()) {
                bot->leaveOrJoin(millisecondsPassed);
            } else {
                this->assignGameToBot(bot);
            }
        }
    }
    for (auto &game: this->games) {
        game->advanceGame(millisecondsPassed);
        if (game->unjammingPerformed(this->player)) { // game had jammed, so it ended itself, and now it'll be restarted
            GameType gameType = game->getGameType();
            int entry = game->getMinimumEntry();
            std::string name = game->getName();
            delete game;
            switch (gameType) {
                case TEXAS_HOLDEM: {
                    game = new TexasHoldem(entry, name);
                }
                    break;
                case ROULETTE: {
                    game = new Roulette(entry, name);
                }
                    break;
                case JACKPOT: {
                    game = new Jackpot(entry, name);
                }
                    break;
            }
        }
    }
}

GameManager::~GameManager() {
    for (auto &bot: this->bots) {
        delete bot;
    }
    for (auto &game: this->games) {
        delete game;
    }
}

std::vector<Game *> GameManager::getGames() const noexcept {
    return this->games;
}

Gambler *GameManager::getPlayer() const noexcept {
    return this->player;
}

bool GameManager::joinGame(int gameIndex) {
    return this->player->joinGame(this->games[gameIndex]);
}

bool GameManager::spectateGame(int gameIndex) {
    return this->player->spectate(this->games[gameIndex]);
}

bool GameManager::leaveGame() {
    return this->player->leaveGame();
}

bool GameManager::stopSpectating() {
    return this->player->stopSpectating();
}

bool GameManager::jackpotBet(int amount) {
    return dynamic_cast<Jackpot *>(this->player->getCurrentGame())->bet(this->player, amount);
}

bool GameManager::texasHoldemFold() {
    return dynamic_cast<TexasHoldem *>(this->player->getCurrentGame())->fold(this->player);
}

bool GameManager::texasHoldemCall() {
    return dynamic_cast<TexasHoldem *>(this->player->getCurrentGame())->call(this->player);
}

bool GameManager::texasHoldemRaise(int amount) {
    return dynamic_cast<TexasHoldem *>(this->player->getCurrentGame())->raise(this->player, amount);
}

bool GameManager::rouletteBet(RouletteBetType betType, int number, int amount) {
    return dynamic_cast<Roulette *>(this->player->getCurrentGame())->rouletteBet(this->player, betType, amount, number);
}
