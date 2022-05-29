#include <gtest/gtest.h>

#include "Roulette.h"
#include "RouletteBot.h"

using namespace std;

TEST(RouletteTest, RouletteBetTest) {
    auto *gambler = new Gambler(1000, "Marcus");
    RouletteBet bet = RouletteBet(COLOR, 17, 100, gambler);
    ASSERT_EQ(bet.getBetStringRepresentation(), "Marcus: Black, 100");
    bet = RouletteBet(EVENODD, 26, 101, gambler);
    ASSERT_EQ(bet.getBetStringRepresentation(), "Marcus: Even, 101");
    bet = RouletteBet(HALF, 7, 65, gambler);
    bet.successful = true;
    ASSERT_EQ(bet.getBetStringRepresentation(), "Marcus: 1 to 18, 65 [WON]");
    bet = RouletteBet(TWELVE, 23, 567, gambler);
    ASSERT_EQ(bet.getBetStringRepresentation(), "Marcus: 2nd 12, 567");
    bet = RouletteBet(COLUMN, 24, 568, gambler);
    ASSERT_EQ(bet.getBetStringRepresentation(), "Marcus: Column 3, 568");
    bet = RouletteBet(NUMBER, 2, 34, gambler);
    ASSERT_EQ(bet.getBetStringRepresentation(), "Marcus: Number 2, 34");
    bet = RouletteBet(NUMBER, 0, 1000, gambler);
    bet.successful = true;
    ASSERT_EQ(bet.getBetStringRepresentation(), "Marcus: Number 0, 1000 [WON]");
}

TEST(RouletteTest, RouletteCreate) {
    auto *gambler = new Gambler(1337);
    vector<Gambler *> gamblers = {gambler, new RouletteBot(999), new RouletteBot(1001)};
    auto *roulette = new Roulette(gamblers, 1000);
    ASSERT_EQ(roulette->getPlayers().size(), 2);
}

TEST(RouletteTest, Start) {
    auto *gambler = new Gambler(1337);
    vector<Gambler *> gamblers = {gambler, new RouletteBot(1338), new RouletteBot(1339)};
    auto *roulette = new Roulette(gamblers, 1000);
    ASSERT_EQ(roulette->getPlayers().size(), 3);
    ASSERT_FALSE(roulette->isInProgress());
    roulette->advanceGame(30000);
    ASSERT_TRUE(roulette->isInProgress());
}

TEST(RouletteTest, RouletteBet) {
    auto *gambler = new Gambler(1337, "Marcus");
    vector<Gambler *> gamblers = {gambler, new RouletteBot(1338), new RouletteBot(1339)};
    auto *roulette = new Roulette(gamblers, 1000);
    roulette->advanceGame(30000);
    ASSERT_TRUE(roulette->rouletteBet(gambler, COLOR, 100, 1));
    ASSERT_EQ(roulette->getRouletteBets()[0].getBetStringRepresentation(), "Marcus: Black, 100");
}

TEST(RouletteTest, CheckAndPayBets) {
    class FakeRoulette : public Roulette {
    public:
        FakeRoulette(const vector<Gambler *> &gamblers, int minimumEntry, const string &name = "") : Roulette(gamblers,
                                                                                                              minimumEntry,
                                                                                                              name) {}

    private:
        void rollTheNumber() noexcept override {
            this->lastNumberRolled = 3;
        }
    };
    auto *gambler = new Gambler(1337, "Marcus");
    vector<Gambler *> gamblers = {gambler, new RouletteBot(1338), new RouletteBot(1339)};
    auto *roulette = new FakeRoulette(gamblers, 1000);
    ASSERT_FALSE(roulette->rouletteBet(gambler, COLOR, 100, 1));
    roulette->advanceGame(30000);
    ASSERT_EQ(roulette->getInGameMoney()[gambler], 1000);
    ASSERT_TRUE(roulette->rouletteBet(gambler, COLOR, 100, 1));
    ASSERT_EQ(roulette->getRouletteBets()[0].getBetStringRepresentation(), "Marcus: Black, 100");
    roulette->advanceGame(90001); // betting ends
    ASSERT_EQ(roulette->getInGameMoney()[gambler], 1100);
}