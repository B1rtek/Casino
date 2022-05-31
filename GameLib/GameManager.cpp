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
            new TestJackpotBot(15000, "Aki Kimura"),
            new TestJackpotBot(15000, "Brad Rogers"),
            new TestJackpotBot(15000, "Carmen Mendez"),
            new TestJackpotBot(15000, "Murff"),
            new TestJackpotBot(15000, "Neville"),
            new TestJackpotBot(15000, "Nikki Morris"),
            new TestJackpotBot(15000, "Dirt"),
            new TestJackpotBot(15000, "Manu"),
            new TestJackpotBot(15000, "GMAC"),
            new TestJackpotBot(15000, "Wolf"),
            new TestJackpotBot(15000, "Yumi"),
            new TestJackpotBot(15000, "Udo Roth"),
            new TestJackpotBot(15000, "Tommy"),
            new TestJackpotBot(15000, "Samson"),
            new TestJackpotBot(15000, "Ray Krieger"),
            new TexasBot(15000, "Chase Linh"),
            new TexasBot(15000, "Chau Wu"),
            new TexasBot(15000, "Big Lou"),
            new TexasBot(15000, "Eugene James"),
            new TexasBot(15000, "Gallo Rivera"),
            new TexasBot(15000, "Hector Maio"),
            new TexasBot(15000, "Ho Seun"),
            new TexasBot(15000, "Isabel Diaz"),
            new TexasBot(15000, "Jack Rourke"),
            new TexasBot(15000, "Taz"),
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
            new RouletteBot(15000, "Darius")
    };
    this->player = new Gambler(15000, "YOU");
    for(auto &bot: bots) {
        this->assignGameToBot(bot);
    }
}

void GameManager::assignGameToBot(GamblerBot *bot) noexcept {
    int gameNumber;
    switch(bot->getGamblerType()) {
        case ROULETTE_BOT: gameNumber = rand() % 3 + 6;
            break;
        case JACKPOT_BOT: gameNumber = rand() % 3;
            break;
        case TEXAS_BOT: gameNumber = rand() % 3 + 3;
            break;
    }
    bot->scheduleGameJoin(this->games[gameNumber]);
}

void GameManager::advanceCasino(int millisecondsPassed) {
    for(auto &bot: this->bots) {
        if(bot->getCurrentGame() == nullptr) {
            if(bot->isMoveScheduled()) {
                bot->leaveOrJoin(millisecondsPassed);
            } else {
                this->assignGameToBot(bot);
            }
        }
    }
    for(auto &game: this->games) {
        game->advanceGame(millisecondsPassed);
    }
}

GameManager::~GameManager() {
    for(auto &bot: this->bots) {
        delete bot;
    }
    for(auto &game: this->games) {
        delete game;
    }
}
