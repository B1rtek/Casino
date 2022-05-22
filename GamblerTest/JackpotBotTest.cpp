#include <gtest/gtest.h>

#include "JackpotBot.h"

using namespace std;

TEST(JackpotBotTest, JackpotBotCreate) {
    JackpotBot jackpotBot = JackpotBot();
    ASSERT_EQ(jackpotBot.getBalance(), 0);
    ASSERT_EQ(jackpotBot.getCurrentGame(), nullptr);
    ASSERT_EQ(jackpotBot.getName(), "");
    ASSERT_TRUE(jackpotBot.isBot());
    ASSERT_EQ(jackpotBot.getTargetTime(), 0);
}

TEST(JackpotBotTest, JackpotBotCreateWithName) {
    JackpotBot jackpotBot = JackpotBot("Lina Navarro");
    ASSERT_EQ(jackpotBot.getBalance(), 0);
    ASSERT_EQ(jackpotBot.getCurrentGame(), nullptr);
    ASSERT_EQ(jackpotBot.getName(), "Lina Navarro");
    ASSERT_TRUE(jackpotBot.isBot());
    ASSERT_EQ(jackpotBot.getTargetTime(), 0);
}

TEST(JackpotBotTest, JackpotBotCreateWithBalance) {
    JackpotBot jackpotBot = JackpotBot(15, "Lina Navarro");
    ASSERT_EQ(jackpotBot.getBalance(), 15);
    ASSERT_EQ(jackpotBot.getCurrentGame(), nullptr);
    ASSERT_EQ(jackpotBot.getName(), "Lina Navarro");
    ASSERT_TRUE(jackpotBot.isBot());
    ASSERT_EQ(jackpotBot.getTargetTime(), 0);
}

TEST(JackpotBotTest, JackpotBotCreateWithBalanceAndGame) {
    Game *game = new Game(5);
    JackpotBot jackpotBot = JackpotBot(15, game,"Lina Navarro");
    ASSERT_EQ(jackpotBot.getBalance(), 10);
    ASSERT_EQ(jackpotBot.getCurrentGame(), game);
    ASSERT_EQ(jackpotBot.getName(), "Lina Navarro");
    ASSERT_TRUE(jackpotBot.isBot());
    ASSERT_EQ(jackpotBot.getTargetTime(), 0);
    delete game;
}

TEST(JackpotBotTest, JackpotBotCreateWithBalanceAndGameNoJoin) {
    Game *game = new Game(50);
    JackpotBot jackpotBot = JackpotBot(15, game,"Lina Navarro");
    ASSERT_EQ(jackpotBot.getBalance(), 15);
    ASSERT_EQ(jackpotBot.getCurrentGame(), nullptr);
    ASSERT_EQ(jackpotBot.getName(), "Lina Navarro");
    ASSERT_TRUE(jackpotBot.isBot());
    ASSERT_EQ(jackpotBot.getTargetTime(), 0);
    delete game;
}