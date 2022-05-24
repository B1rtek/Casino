#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "Jackpot.h"
#include "JackpotBot.h"

using namespace std;

TEST(JackpotTest, JackpotCreate) {
    Jackpot jackpot = Jackpot(100);
    ASSERT_EQ(jackpot.getCurrentBets().size(), 0);
    ASSERT_EQ(jackpot.getInGameMoney().size(), 0);
    ASSERT_EQ(jackpot.getPlayers().size(), 0);
    ASSERT_EQ(jackpot.getSpectators().size(), 0);
    ASSERT_EQ(jackpot.getMinimumEntry(), 100);
    ASSERT_EQ(jackpot.getName(), "");
    ASSERT_FALSE(jackpot.isInProgress());
    ASSERT_EQ(jackpot.getTotalBet(), 0);
    ASSERT_EQ(jackpot.getLastGameWinners().size(), 0);
    jackpot = Jackpot(100, "Jackpot");
    ASSERT_EQ(jackpot.getCurrentBets().size(), 0);
    ASSERT_EQ(jackpot.getInGameMoney().size(), 0);
    ASSERT_EQ(jackpot.getPlayers().size(), 0);
    ASSERT_EQ(jackpot.getSpectators().size(), 0);
    ASSERT_EQ(jackpot.getMinimumEntry(), 100);
    ASSERT_EQ(jackpot.getName(), "Jackpot");
    ASSERT_FALSE(jackpot.isInProgress());
    ASSERT_EQ(jackpot.getTotalBet(), 0);
    ASSERT_EQ(jackpot.getLastGameWinners().size(), 0);
    ASSERT_THROW(Jackpot(99), std::invalid_argument);
}

TEST(JackpotTest, JackpotCreateWithGambler) {
    auto *gambler = new Gambler(50);
    auto *jackpot = new Jackpot(gambler, 100, "Jackpot");
    ASSERT_EQ(jackpot->getCurrentBets().size(), 0);
    ASSERT_EQ(jackpot->getInGameMoney().size(), 0);
    ASSERT_EQ(jackpot->getPlayers().size(), 0);
    ASSERT_EQ(jackpot->getSpectators().size(), 0);
    ASSERT_EQ(jackpot->getMinimumEntry(), 100);
    ASSERT_EQ(jackpot->getName(), "Jackpot");
    ASSERT_FALSE(jackpot->isInProgress());
    ASSERT_EQ(jackpot->getTotalBet(), 0);
    ASSERT_EQ(jackpot->getLastGameWinners().size(), 0);
    delete jackpot;
    gambler->addBalance(100);
    jackpot = new Jackpot(gambler, 100);
    ASSERT_EQ(jackpot->getCurrentBets().size(), 1);
    ASSERT_EQ(jackpot->getCurrentBets()[gambler], 0);
    ASSERT_EQ(jackpot->getInGameMoney().size(), 1);
    ASSERT_EQ(jackpot->getInGameMoney()[gambler], 100);
    ASSERT_EQ(jackpot->getPlayers().size(), 1);
    ASSERT_EQ(jackpot->getSpectators().size(), 0);
    ASSERT_EQ(jackpot->getMinimumEntry(), 100);
    ASSERT_EQ(jackpot->getName(), "");
    ASSERT_FALSE(jackpot->isInProgress());
    ASSERT_EQ(jackpot->getTotalBet(), 0);
    ASSERT_EQ(jackpot->getLastGameWinners().size(), 0);
    delete jackpot;
    ASSERT_THROW(Jackpot(gambler, 78), std::invalid_argument);
    delete gambler;
}

TEST(JackpotTest, JackpotCreateWithGamblers) {
    auto *gambler1 = new Gambler(5), *gambler2 = new Gambler(420);
    vector<Gambler *> gamblers = {gambler1, gambler2};
    auto *jackpot = new Jackpot(gamblers, 100);
    // gambler1 couldn't join the game due to not having enough balance
    ASSERT_EQ(jackpot->getCurrentBets().size(), 1);
    ASSERT_EQ(jackpot->getCurrentBets()[gambler2], 0);
    ASSERT_EQ(jackpot->getInGameMoney().size(), 1);
    ASSERT_EQ(jackpot->getInGameMoney()[gambler2], 100);
    ASSERT_EQ(jackpot->getPlayers().size(), 1);
    ASSERT_EQ(jackpot->getSpectators().size(), 0);
    ASSERT_EQ(jackpot->getMinimumEntry(), 100);
    ASSERT_EQ(jackpot->getName(), "");
    ASSERT_EQ(gambler2->getBalance(), 320);
    ASSERT_EQ(gambler2->getCurrentGame(), jackpot);
    ASSERT_FALSE(jackpot->isInProgress());
    ASSERT_EQ(jackpot->getTotalBet(), 0);
    ASSERT_THROW(Jackpot(gamblers, 3214), std::invalid_argument);
    delete gambler1;
    delete gambler2;
    delete jackpot;
}

TEST(JackpotTest, AdvanceGameStart) {
    auto *gambler1 = new Gambler(500), *gambler2 = new Gambler(420);
    vector<Gambler *> gamblers = {gambler1, gambler2};
    auto *jackpot = new Jackpot(gamblers, 100);
    // timer is set to 30 seconds initially to allow players to join, so calling advance with less than that does nothing
    ASSERT_EQ(jackpot->getTargetTime(), 30000);
    ASSERT_FALSE(jackpot->isInProgress());
    jackpot->advanceGame(5000);
    ASSERT_FALSE(jackpot->isInProgress());
    ASSERT_FALSE(jackpot->bet(gambler1, 3));
    ASSERT_EQ(jackpot->getCurrentBets()[gambler1], 0);
    ASSERT_EQ(jackpot->getCurrentBets()[gambler2], 0);
    // finally at 30000 somerthing happens
    jackpot->advanceGame(30000);
    ASSERT_TRUE(jackpot->isInProgress());
    ASSERT_EQ(jackpot->getCurrentBets()[gambler1], 1);
    ASSERT_EQ(jackpot->getCurrentBets()[gambler2], 1);
    ASSERT_EQ(jackpot->getTargetTime(), 90000);
    // game doesn't start twice
    jackpot->advanceGame(40000);
    ASSERT_TRUE(jackpot->isInProgress());
    ASSERT_EQ(jackpot->getCurrentBets()[gambler1], 1);
    ASSERT_EQ(jackpot->getCurrentBets()[gambler2], 1);
    ASSERT_EQ(jackpot->getTargetTime(), 90000);
    ASSERT_TRUE(jackpot->bet(gambler1, 3));
    ASSERT_EQ(jackpot->getCurrentBets()[gambler1], 4);
    delete gambler1;
    delete gambler2;
    delete jackpot;
}

TEST(JackpotTest, AdvanceGameBotBet) {
    auto *bot1 = new JackpotBot(500), *bot2 = new JackpotBot(420);
    auto *gambler = new Gambler(400);
    vector<Gambler *> gamblers = {bot1, bot2, gambler};
    auto *jackpot = new Jackpot(gamblers, 100);
    jackpot->advanceGame(9); // nothing happens
    ASSERT_FALSE(jackpot->isInProgress());
    ASSERT_EQ(jackpot->getCurrentBets()[bot1], 0);
    ASSERT_EQ(jackpot->getCurrentBets()[bot2], 0);
    jackpot->advanceGame(30000); // game starts
    ASSERT_TRUE(jackpot->isInProgress());
    ASSERT_EQ(jackpot->getCurrentBets()[bot1], 1);
    ASSERT_EQ(jackpot->getCurrentBets()[bot2], 1);
    ASSERT_EQ(jackpot->getTotalBet(), jackpot->getPlayers().size() * jackpot->getMinimumEntry() / 100);
    jackpot->advanceGame(30001); // bots can bet (and they do!)
    ASSERT_TRUE(jackpot->isInProgress());
    ASSERT_EQ(jackpot->getCurrentBets()[bot1], 3);
    ASSERT_EQ(jackpot->getCurrentBets()[bot2], 3);
    ASSERT_EQ(jackpot->getCurrentBets()[gambler], 1);
    ASSERT_EQ(jackpot->getTotalBet(), 7);
    ASSERT_TRUE(jackpot->bet(gambler, 50));
    ASSERT_EQ(jackpot->getCurrentBets()[gambler], 51);
    ASSERT_EQ(jackpot->getTotalBet(), 57);
    delete bot1;
    delete bot2;
    delete gambler;
    delete jackpot;
}

TEST(JackpotTest, AdvanceGameFinishGame) {
    auto *bot1 = new JackpotBot(500), *bot2 = new JackpotBot(420);
    vector<Gambler *> gamblers = {bot1, bot2};
    auto *jackpot = new Jackpot(gamblers, 100);
    jackpot->advanceGame(30000); // game starts
    ASSERT_TRUE(jackpot->isInProgress());
    ASSERT_EQ(jackpot->getCurrentBets()[bot1], 1);
    ASSERT_EQ(jackpot->getCurrentBets()[bot2], 1);
    ASSERT_EQ(jackpot->getTotalBet(), jackpot->getPlayers().size() * jackpot->getMinimumEntry() / 100);
    jackpot->advanceGame(30001); // bots can bet (and they do!)
    ASSERT_TRUE(jackpot->isInProgress());
    ASSERT_EQ(jackpot->getCurrentBets()[bot1], 3);
    ASSERT_EQ(jackpot->getCurrentBets()[bot2], 3);
    int totalBet = jackpot->getTotalBet();
    jackpot->advanceGame(90000); //game ends
    vector<Gambler *> lastWinners = jackpot->getLastGameWinners();
    for (auto &gambler: jackpot->getPlayers()) {
        if (std::find(lastWinners.begin(), lastWinners.end(), gambler) == lastWinners.end()) {
            ASSERT_EQ(jackpot->getInGameMoney()[gambler], 97);
        } else {
            ASSERT_EQ(jackpot->getInGameMoney()[gambler], 97 + totalBet);
        }
    }
    // game ended, no betting now
    ASSERT_FALSE(jackpot->bet(bot1, 1));
    // next game starts and the cycle continues
    jackpot->advanceGame(120000);
    for (auto &gambler: jackpot->getPlayers()) {
        if (std::find(lastWinners.begin(), lastWinners.end(), gambler) == lastWinners.end()) {
            ASSERT_EQ(jackpot->getInGameMoney()[gambler], 96);
        } else {
            ASSERT_EQ(jackpot->getInGameMoney()[gambler], 96 + totalBet);
        }
        ASSERT_EQ(jackpot->getCurrentBets()[gambler], 1);
    }
    delete bot1;
    delete bot2;
    delete jackpot;
}

TEST(JackpotTest, AdvanceGameRemoveBankrupt) {
    class MockJackpot : public Jackpot {
        public:
        MockJackpot(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
        Jackpot(gamblers, minimumEntry, name) {}
        MOCK_METHOD(vector<Gambler*>, chooseTheWinners, (), (noexcept, override));

        MockJackpot(MockJackpot const &jackpot);
    };
    auto *bot1 = new JackpotBot(200);
    auto *gambler = new Gambler(500);
    vector<Gambler *> gamblers = {gambler, bot1};
    vector<Gambler *> winners = {gambler};
    auto jackpot = MockJackpot(gamblers, 100);
    EXPECT_CALL(jackpot, chooseTheWinners()).WillRepeatedly(testing::Return(winners));
    jackpot.advanceGame(30000); // game starts, bots bet
    jackpot.bet(bot1, 99); // bot is all in
    jackpot.advanceGame(90000); // game ends, winner is chosen
    // due to mocking, gambler wins and bankrupt bot leaves the game and becomes a spectator
    ASSERT_EQ(jackpot.getSpectators().size(), 1);
    ASSERT_EQ(jackpot.getInGameMoney()[gambler], 200);
    delete bot1;
    delete gambler;
}

TEST(JackpotTest, GetPercentages) {
    auto *bot1 = new JackpotBot(500), *bot2 = new JackpotBot(700), *bot3 = new JackpotBot(200);
    vector<Gambler *> gamblers = {bot1, bot2, bot3};
    Jackpot jackpot = Jackpot(gamblers, 100);
    jackpot.advanceGame(30000);
    jackpot.advanceGame(35000);
    jackpot.bet(bot1, 8);
    jackpot.bet(bot2, 3);
    auto percentages = jackpot.getPercentages();
    ASSERT_DOUBLE_EQ(jackpot.getPercentages()[bot1], 55);
    ASSERT_DOUBLE_EQ(jackpot.getPercentages()[bot2], 30);
    ASSERT_DOUBLE_EQ(jackpot.getPercentages()[bot3], 15);
}
