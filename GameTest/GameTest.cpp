#include <gtest/gtest.h>

#include "Game.h"

using namespace std;

TEST(GameTest, GameCreate) {
    Game game = Game(1);
    ASSERT_EQ(game.getCurrentBets().size(), 0);
    ASSERT_EQ(game.getInGameMoney().size(), 0);
    ASSERT_EQ(game.getPlayers().size(), 0);
    ASSERT_EQ(game.getSpectators().size(), 0);
    ASSERT_EQ(game.getMinimumEntry(), 1);
    ASSERT_EQ(game.getName(), "");
    ASSERT_FALSE(game.isInProgress());
    ASSERT_EQ(game.getTotalBet(), 0);
    game = Game(1, "Game 1");
    ASSERT_EQ(game.getCurrentBets().size(), 0);
    ASSERT_EQ(game.getInGameMoney().size(), 0);
    ASSERT_EQ(game.getPlayers().size(), 0);
    ASSERT_EQ(game.getSpectators().size(), 0);
    ASSERT_EQ(game.getMinimumEntry(), 1);
    ASSERT_EQ(game.getName(), "Game 1");
    ASSERT_FALSE(game.isInProgress());
    ASSERT_EQ(game.getTotalBet(), 0);
}

TEST(GameTest, GameCreateWithGambler) {
    auto *gambler = new Gambler(), *gambler2 = new Gambler(10);
    Game *game = new Game(gambler, 1, "Game 1");
    //not enough balance to join
    ASSERT_EQ(game->getCurrentBets().size(), 0);
    ASSERT_EQ(game->getInGameMoney().size(), 0);
    ASSERT_EQ(game->getPlayers().size(), 0);
    ASSERT_EQ(game->getSpectators().size(), 0);
    ASSERT_EQ(game->getMinimumEntry(), 1);
    ASSERT_EQ(game->getName(), "Game 1");
    ASSERT_EQ(gambler->getBalance(), 0);
    ASSERT_EQ(gambler->getCurrentGame(), nullptr);
    ASSERT_FALSE(game->isInProgress());
    ASSERT_EQ(game->getTotalBet(), 0);
    delete game;
    game = new Game(gambler2, 1);
    // enough balance to join
    ASSERT_EQ(game->getCurrentBets().size(), 1);
    ASSERT_EQ(game->getCurrentBets()[gambler2], 0);
    ASSERT_EQ(game->getInGameMoney().size(), 1);
    ASSERT_EQ(game->getInGameMoney()[gambler2], 1);
    ASSERT_EQ(game->getPlayers().size(), 1);
    ASSERT_EQ(game->getSpectators().size(), 0);
    ASSERT_EQ(game->getMinimumEntry(), 1);
    ASSERT_EQ(game->getName(), "");
    ASSERT_EQ(gambler2->getBalance(), 9);
    ASSERT_EQ(gambler2->getCurrentGame(), game);
    ASSERT_FALSE(game->isInProgress());
    ASSERT_EQ(game->getTotalBet(), 0);
    delete game;
    delete gambler;
    delete gambler2;
}

TEST(GameTest, GameCreateWithGamblers) {
    auto *gambler1 = new Gambler(5), *gambler2 = new Gambler(420);
    vector<Gambler *> gamblers = {gambler1, gambler2};
    Game *game = new Game(gamblers, 10);
    // gambler1 couldn't join the game due to not having enough balance
    ASSERT_EQ(game->getCurrentBets().size(), 1);
    ASSERT_EQ(game->getCurrentBets()[gambler2], 0);
    ASSERT_EQ(game->getInGameMoney().size(), 1);
    ASSERT_EQ(game->getInGameMoney()[gambler2], 10);
    ASSERT_EQ(game->getPlayers().size(), 1);
    ASSERT_EQ(game->getSpectators().size(), 0);
    ASSERT_EQ(game->getMinimumEntry(), 10);
    ASSERT_EQ(game->getName(), "");
    ASSERT_EQ(gambler2->getBalance(), 410);
    ASSERT_EQ(gambler2->getCurrentGame(), game);
    ASSERT_FALSE(game->isInProgress());
    ASSERT_EQ(game->getTotalBet(), 0);
    delete gambler1;
    delete gambler2;
    delete game;
}

TEST(GameTest, StartGame) {
    Game game = Game(7);
    game.startGame();
    ASSERT_TRUE(game.isInProgress());
    ASSERT_EQ(game.getTotalBet(), 0);
}

TEST(GameTest, Bet) {
    auto *gambler = new Gambler(20);
    Game *game = new Game(5);
    // make them bet without joining the game
    ASSERT_FALSE(game->bet(gambler, 2));
    ASSERT_EQ(game->getPlayers().size(), 0);
    ASSERT_EQ(game->getCurrentBets().size(), 0);
    ASSERT_EQ(gambler->getBalance(), 20);
    ASSERT_EQ(game->getTotalBet(), 0);
    delete game;
    game = new Game(gambler, 5);
    // make them join the game
    ASSERT_EQ(game->getPlayers().size(), 1);
    ASSERT_EQ(game->getPlayers()[0], gambler);
    ASSERT_EQ(gambler->getBalance(), 15);
    ASSERT_EQ(game->getInGameMoney()[gambler], 5);
    ASSERT_EQ(game->getCurrentBets()[gambler], 0);
    ASSERT_EQ(game->getTotalBet(), 0);
    // make them bet without starting the game
    ASSERT_FALSE(game->bet(gambler, 3));
    ASSERT_EQ(gambler->getBalance(), 15);
    ASSERT_EQ(game->getInGameMoney()[gambler], 5);
    ASSERT_EQ(game->getCurrentBets()[gambler], 0);
    ASSERT_EQ(game->getTotalBet(), 0);
    game->startGame();
    // make them bet
    ASSERT_TRUE(game->bet(gambler, 3));
    ASSERT_EQ(gambler->getBalance(), 15);
    ASSERT_EQ(game->getInGameMoney()[gambler], 2);
    ASSERT_EQ(game->getCurrentBets()[gambler], 3);
    ASSERT_EQ(game->getTotalBet(), 3);
    // make them bet more than they have
    ASSERT_FALSE(game->bet(gambler, 5));
    ASSERT_EQ(gambler->getBalance(), 15);
    ASSERT_EQ(game->getInGameMoney()[gambler], 2);
    ASSERT_EQ(game->getCurrentBets()[gambler], 3);
    ASSERT_EQ(game->getTotalBet(), 3);
    delete gambler;
    delete game;
}

TEST(GameTest, PayTheWinner) {
    auto *gambler1 = new Gambler(15), *gambler2 = new Gambler(20);
    vector<Gambler *> gamblers = {gambler1, gambler2};
    Game *game = new Game(gamblers, 10);
    // both joined
    ASSERT_EQ(game->getCurrentBets().size(), 2);
    ASSERT_EQ(game->getInGameMoney()[gambler1], 10);
    ASSERT_EQ(game->getInGameMoney()[gambler2], 10);
    ASSERT_EQ(gambler1->getBalance(), 5);
    ASSERT_EQ(gambler2->getBalance(), 10);
    game->startGame();
    // make them both bet some
    ASSERT_TRUE(game->bet(gambler1, 5));
    ASSERT_TRUE(game->bet(gambler2, 5));
    ASSERT_EQ(game->getTotalBet(), 10);
    // choose the winner (gambler1) and award them
    game->payTheWinner(gambler1);
    ASSERT_FALSE(game->isInProgress());
    ASSERT_EQ(game->getInGameMoney()[gambler1], 15);
    ASSERT_EQ(game->getInGameMoney()[gambler2], 5);
    ASSERT_EQ(game->getTotalBet(), 0);
    // their balances shouldn't change
    ASSERT_EQ(gambler1->getBalance(), 5);
    ASSERT_EQ(gambler2->getBalance(), 10);
    delete gambler1;
    delete gambler2;
    delete game;
}

TEST(GameTest, AddPlayer) {
    auto *gambler1 = new Gambler(4), *gambler2 = new Gambler(7);
    Game *game = new Game(5);
    // adding player with not enough credits doesn't work
    ASSERT_FALSE(game->addPlayer(gambler1));
    ASSERT_EQ(game->getPlayers().size(), 0);
    ASSERT_EQ(gambler1->getBalance(), 4);
    ASSERT_EQ(gambler1->getCurrentGame(), nullptr);
    // adding a player with enough credits works partially, as stated in the method's documentation
    gambler1->addBalance(3);
    ASSERT_TRUE(game->addPlayer(gambler1));
    ASSERT_EQ(game->getPlayers().size(), 1);
    ASSERT_EQ(game->getInGameMoney()[gambler1], 5);
    ASSERT_EQ(gambler1->getBalance(), 2);
    // by adding them in this way, Gambler doesn't know that they are playing a game
    // Game shouldn't add a Gambler to itself, Gambler should instead join it, and that
    // action should be initiated by the Gambler
    ASSERT_EQ(gambler1->getCurrentGame(), nullptr);
    // A player cannot be added when the game is in progress
    game->startGame();
    ASSERT_TRUE(game->isInProgress());
    ASSERT_FALSE(game->addPlayer(gambler2));
    ASSERT_EQ(game->getPlayers().size(), 1);
    delete gambler1;
    delete gambler2;
    delete game;
}

TEST(GameTest, RemovePlayer) {
    auto *gambler = new Gambler(8);
    Game *game = new Game(gambler, 5);
    ASSERT_EQ(game->getPlayers().size(), 1);
    ASSERT_EQ(game->getInGameMoney()[gambler], 5);
    ASSERT_EQ(game->getCurrentBets()[gambler], 0);
    ASSERT_EQ(gambler->getBalance(), 3);
    ASSERT_EQ(gambler->getCurrentGame(), game);
    // gamblers can't leave after the game starts
    game->startGame();
    ASSERT_FALSE(game->removePlayer(gambler));
    // gamblers can't leave the game while they're betting
    ASSERT_TRUE(game->bet(gambler, 4));
    ASSERT_EQ(game->getCurrentBets()[gambler], 4);
    ASSERT_EQ(game->getInGameMoney()[gambler], 1);
    ASSERT_FALSE(game->removePlayer(gambler));
    ASSERT_EQ(game->getPlayers()[0], gambler);
    ASSERT_EQ(gambler->getCurrentGame(), game);
    // they win so they can leave later
    game->payTheWinner(gambler);
    // make them leave the game (not by calling Gambler's method)
    ASSERT_TRUE(game->removePlayer(gambler));
    ASSERT_EQ(game->getPlayers().size(), 0);
    ASSERT_EQ(game->getCurrentBets().size(), 0);
    ASSERT_EQ(game->getInGameMoney().size(), 0);
    ASSERT_EQ(gambler->getBalance(), 8);
    // because the incorrect method was used, Gambler still thinks that they are in game
    ASSERT_EQ(gambler->getCurrentGame(), game);
    // let's get a new gambler
    delete gambler;
    gambler = new Gambler(10);
    ASSERT_TRUE(gambler->joinGame(game));
    ASSERT_TRUE(gambler->leaveGame());
    // removing a gambler from a game that they aren't in makes no sense, the method returns true but it doesn't mean anything
    delete gambler;
    delete game;
}

TEST(GameTest, AddSpectator) {
    auto *gambler1 = new Gambler(13), *gambler2 = new Gambler(5);
    Game *game = new Game(3);
    // if the gambler isn't in game, they can be added as a spectator
    ASSERT_TRUE(game->addSpectator(gambler1));
    ASSERT_EQ(game->getSpectators().size(), 1);
    // since the gambler didn't initiate the action, they don't know that they are spectating
    ASSERT_EQ(gambler1->getSpectatedGame(), nullptr);
    // they can't spectate twice
    gambler1->spectate(game);
    ASSERT_FALSE(game->addSpectator(gambler1));
    ASSERT_EQ(game->getSpectators().size(), 1);
    // they can't join a game while spectating
    ASSERT_FALSE(game->addPlayer(gambler1));
    // they can't spectate while playing a game
    gambler2->joinGame(game);
    ASSERT_FALSE(game->addSpectator(gambler2));
    delete gambler1;
    delete gambler2;
    delete game;
}

TEST(GameTest, RemoveSpectator) {
    auto *gambler = new Gambler(17);
    Game *game = new Game(6);
    ASSERT_TRUE(gambler->spectate(game));
    ASSERT_EQ(game->getSpectators().size(), 1);
    ASSERT_EQ(game->getPlayers().size(), 0);
    ASSERT_EQ(gambler->getSpectatedGame(), game);
    // removing a spectator the incorrect way
    game->removeSpectator(gambler);
    ASSERT_EQ(game->getSpectators().size(), 0);
    ASSERT_EQ(gambler->getSpectatedGame(), game);
    delete gambler;
    delete game;
    // quitting spectating doesn't do anything else than removing the
    // gambler from the spectators list, so it doesn't cause any issues if
    // a gambler gets removed from that list if they aren't there
    // because they wouldn't be spectating in the first place
}