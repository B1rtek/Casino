#include <gtest/gtest.h>

#include "JackpotBot.h"

using namespace std;

class FakeJackpotBot : public GamblerBot {
public:
    explicit FakeJackpotBot(const std::string &name="") : GamblerBot(name) {}

    FakeJackpotBot(int balance, const std::string &name="") : GamblerBot(balance, name) {}

    FakeJackpotBot(int balance, Game *game, const std::string &name="") : GamblerBot(balance, game, name) {}

/**
 * Makes the bot bet additional money if the algorithm decides to do so
 * @param millisecondsPassed
 */
    void makeAMove(int millisecondsPassed) noexcept override {
        this->gamePlayed->bet(this, 2);
    }
};

TEST(JackpotBotTest, JackpotBotCreate) {
    auto jackpotBot = FakeJackpotBot();
    ASSERT_EQ(jackpotBot.getBalance(), 0);
    ASSERT_EQ(jackpotBot.getCurrentGame(), nullptr);
    ASSERT_EQ(jackpotBot.getName(), "");
    ASSERT_TRUE(jackpotBot.isBot());
    ASSERT_EQ(jackpotBot.getTargetTime(), 0);
}

TEST(JackpotBotTest, JackpotBotCreateWithName) {
    auto jackpotBot = FakeJackpotBot("Lina Navarro");
    ASSERT_EQ(jackpotBot.getBalance(), 0);
    ASSERT_EQ(jackpotBot.getCurrentGame(), nullptr);
    ASSERT_EQ(jackpotBot.getName(), "Lina Navarro");
    ASSERT_TRUE(jackpotBot.isBot());
    ASSERT_EQ(jackpotBot.getTargetTime(), 0);
}

TEST(JackpotBotTest, JackpotBotCreateWithBalance) {
    auto jackpotBot = FakeJackpotBot(15, "Lina Navarro");
    ASSERT_EQ(jackpotBot.getBalance(), 15);
    ASSERT_EQ(jackpotBot.getCurrentGame(), nullptr);
    ASSERT_EQ(jackpotBot.getName(), "Lina Navarro");
    ASSERT_TRUE(jackpotBot.isBot());
    ASSERT_EQ(jackpotBot.getTargetTime(), 0);
}

TEST(JackpotBotTest, JackpotBotCreateWithBalanceAndGame) {
    Game *game = new Game(5);
    auto jackpotBot = FakeJackpotBot(15, game,"Lina Navarro");
    ASSERT_EQ(jackpotBot.getBalance(), 10);
    ASSERT_EQ(jackpotBot.getCurrentGame(), game);
    ASSERT_EQ(jackpotBot.getName(), "Lina Navarro");
    ASSERT_TRUE(jackpotBot.isBot());
    ASSERT_EQ(jackpotBot.getTargetTime(), 0);
    delete game;
}

TEST(JackpotBotTest, JackpotBotCreateWithBalanceAndGameNoJoin) {
    Game *game = new Game(50);
    auto jackpotBot = FakeJackpotBot(15, game,"Lina Navarro");
    ASSERT_EQ(jackpotBot.getBalance(), 15);
    ASSERT_EQ(jackpotBot.getCurrentGame(), nullptr);
    ASSERT_EQ(jackpotBot.getName(), "Lina Navarro");
    ASSERT_TRUE(jackpotBot.isBot());
    ASSERT_EQ(jackpotBot.getTargetTime(), 0);
    delete game;
}