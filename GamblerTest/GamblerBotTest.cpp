#include <gtest/gtest.h>

#include "GamblerBot.h"

using namespace std;

TEST(GamblerBotTest, GamblerBotCreate) {
    GamblerBot gamblerBot = GamblerBot();
    ASSERT_EQ(gamblerBot.getBalance(), 0);
    ASSERT_EQ(gamblerBot.getCurrentGame(), nullptr);
    ASSERT_EQ(gamblerBot.getName(), "");
    ASSERT_TRUE(gamblerBot.isBot());
    ASSERT_EQ(gamblerBot.getTargetTime(), 0);
}

TEST(GamblerBotTest, GamblerBotCreateWithName) {
    GamblerBot gamblerBot = GamblerBot("The Collector");
    ASSERT_EQ(gamblerBot.getBalance(), 0);
    ASSERT_EQ(gamblerBot.getCurrentGame(), nullptr);
    ASSERT_EQ(gamblerBot.getName(), "The Collector");
    ASSERT_TRUE(gamblerBot.isBot());
    ASSERT_EQ(gamblerBot.getTargetTime(), 0);
}

TEST(GamblerBotTest, GamblerBotCreateWithBalance) {
    GamblerBot gamblerBot = GamblerBot(23, "Tyler Morgan");
    ASSERT_EQ(gamblerBot.getBalance(), 23);
    ASSERT_EQ(gamblerBot.getCurrentGame(), nullptr);
    ASSERT_EQ(gamblerBot.getName(), "Tyler Morgan");
    ASSERT_TRUE(gamblerBot.isBot());
    ASSERT_EQ(gamblerBot.getTargetTime(), 0);
}

TEST(GamblerBotTest, GamblerBotCreateWithBalanceAndGame) {
    Game *game = new Game(10);
    GamblerBot gamblerBot = GamblerBot(23, game, "Tyler Morgan");
    ASSERT_EQ(gamblerBot.getBalance(), 13);
    ASSERT_EQ(gamblerBot.getCurrentGame(), game);
    ASSERT_EQ(gamblerBot.getName(), "Tyler Morgan");
    ASSERT_TRUE(gamblerBot.isBot());
    ASSERT_EQ(gamblerBot.getTargetTime(), 0);
    delete game;
}

TEST(GamblerBotTest, GamblerBotCreateWithBalanceAndGameNoJoin) {
    Game *game = new Game(50);
    GamblerBot gamblerBot = GamblerBot(23, game, "Tyler Morgan");
    ASSERT_EQ(gamblerBot.getBalance(), 23);
    ASSERT_EQ(gamblerBot.getCurrentGame(), nullptr);
    ASSERT_EQ(gamblerBot.getName(), "Tyler Morgan");
    ASSERT_TRUE(gamblerBot.isBot());
    ASSERT_EQ(gamblerBot.getTargetTime(), 0);
    delete game;
}