#include <gtest/gtest.h>

#include "CardGame.h"

using namespace std;

TEST(CardGameTest, CardGameCreate) {
    CardGame game = CardGame(10);
    ASSERT_EQ(game.getCurrentBets().size(), 0);
    ASSERT_EQ(game.getInGameMoney().size(), 0);
    ASSERT_EQ(game.getPlayers().size(), 0);
    ASSERT_EQ(game.getSpectators().size(), 0);
    ASSERT_EQ(game.getMinimumEntry(), 10);
    ASSERT_EQ(game.getName(), "");
    ASSERT_FALSE(game.isInProgress());
    ASSERT_EQ(game.getDeck(), CardGame::deck);
    ASSERT_EQ(game.getGamblersCards().size(), 0);
}

TEST(CardGameTest, CardGameCreateWithNameAndCustomDeck) {
    CardGame game = CardGame(10, CardGame::russianSchnapsenDeck, "1000");
    ASSERT_EQ(game.getCurrentBets().size(), 0);
    ASSERT_EQ(game.getInGameMoney().size(), 0);
    ASSERT_EQ(game.getPlayers().size(), 0);
    ASSERT_EQ(game.getSpectators().size(), 0);
    ASSERT_EQ(game.getMinimumEntry(), 10);
    ASSERT_EQ(game.getName(), "1000");
    ASSERT_FALSE(game.isInProgress());
    ASSERT_EQ(game.getDeck(), CardGame::russianSchnapsenDeck);
    ASSERT_EQ(game.getGamblersCards().size(), 0);
}

TEST(CardGameTest, CardGameCreateWithGambler) {
    auto *gambler = new Gambler(), *gambler2 = new Gambler(10);
    CardGame *game = new CardGame(gambler, 10, CardGame::deck, "Blackjack");
    //not enough balance to join
    ASSERT_EQ(game->getCurrentBets().size(), 0);
    ASSERT_EQ(game->getInGameMoney().size(), 0);
    ASSERT_EQ(game->getPlayers().size(), 0);
    ASSERT_EQ(game->getSpectators().size(), 0);
    ASSERT_EQ(game->getMinimumEntry(), 10);
    ASSERT_EQ(game->getName(), "Blackjack");
    ASSERT_EQ(gambler->getBalance(), 0);
    ASSERT_EQ(gambler->getCurrentGame(), nullptr);
    ASSERT_FALSE(game->isInProgress());
    ASSERT_EQ(game->getDeck(), CardGame::deck);
    ASSERT_EQ(game->getGamblersCards().size(), 0);
    game = new CardGame(gambler2, 1);
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
    ASSERT_EQ(game->getDeck(), CardGame::deck);
    ASSERT_EQ(game->getGamblersCards().size(), 0);
    delete game;
    delete gambler;
    delete gambler2;
}

TEST(CardGameTest, CreateCardGameWithGamblers) {
    auto *gambler1 = new Gambler(5), *gambler2 = new Gambler(420);
    vector<Gambler *> gamblers = {gambler1, gambler2};
    CardGame *game = new CardGame(gamblers, 10, CardGame::russianSchnapsenDeck);
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
    ASSERT_EQ(game->getDeck(), CardGame::russianSchnapsenDeck);
    ASSERT_EQ(game->getGamblersCards().size(), 0);
    delete gambler1;
    delete gambler2;
    delete game;
}

