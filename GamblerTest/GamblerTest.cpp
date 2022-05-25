#include <gtest/gtest.h>

#include "Gambler.h"

using namespace std;

TEST(GamblerTest, GamblerCreate) {
    Gambler gambler = Gambler();
    ASSERT_EQ(gambler.getBalance(), 0);
    ASSERT_TRUE(gambler.getDeposits().empty());
    ASSERT_EQ(gambler.getCurrentGame(), nullptr);
    ASSERT_EQ(gambler.getName(), "");
    ASSERT_FALSE(gambler.isBot());
}

TEST(GamblerTest, GamblerCreateWithName) {
    Gambler gambler = Gambler("Marcus Weir");
    ASSERT_EQ(gambler.getBalance(), 0);
    ASSERT_TRUE(gambler.getDeposits().empty());
    ASSERT_EQ(gambler.getCurrentGame(), nullptr);
    ASSERT_EQ(gambler.getName(), "Marcus Weir");
    ASSERT_FALSE(gambler.isBot());
}

TEST(GamblerTest, GamblerCreateWithBalance) {
    Gambler gambler = Gambler(23);
    ASSERT_EQ(gambler.getBalance(), 23);
    ASSERT_EQ(gambler.getDeposits()[0], 23);
    ASSERT_EQ(gambler.getCurrentGame(), nullptr);
    ASSERT_FALSE(gambler.isBot());
}

TEST(GamblerTest, GamblerCreateWithBalanceAndName) {
    Gambler gambler = Gambler(23, "Marcus Weir");
    ASSERT_EQ(gambler.getBalance(), 23);
    ASSERT_EQ(gambler.getDeposits()[0], 23);
    ASSERT_EQ(gambler.getCurrentGame(), nullptr);
    ASSERT_EQ(gambler.getName(), "Marcus Weir");
    ASSERT_FALSE(gambler.isBot());
}

TEST(GamblerTest, GamblerCreateWithBalanceAndGame) {
    Game *game = new Game(0);
    Gambler gambler = Gambler(23, game);
    ASSERT_EQ(gambler.getBalance(), 23);
    ASSERT_EQ(gambler.getDeposits()[0], 23);
    ASSERT_EQ(gambler.getCurrentGame(), game);
    ASSERT_FALSE(gambler.isBot());
    delete game;
}

TEST(GamblerTest, GamblerCreateWithBalanceGameAndName) {
    Game *game = new Game(0);
    Gambler gambler = Gambler(23, game, "Marcus Weir");
    ASSERT_EQ(gambler.getBalance(), 23);
    ASSERT_EQ(gambler.getDeposits()[0], 23);
    ASSERT_EQ(gambler.getCurrentGame(), game);
    ASSERT_EQ(gambler.getName(), "Marcus Weir");
    ASSERT_FALSE(gambler.isBot());
    delete game;
}

TEST(GamblerTest, GamblerAddAndSubstractBalance) {
    Game* game1 = new Game(0, "Game 1"), *game2 = new Game(0);
    Gambler gambler = Gambler(23, game1, "Marcus Weir");
    gambler.addBalance(3);
    ASSERT_EQ(gambler.getBalance(), 26);
    gambler.subtractBalance(12);
    ASSERT_EQ(gambler.getBalance(), 14);
    gambler.subtractBalance(250);
    ASSERT_EQ(gambler.getBalance(), 0);
    ASSERT_EQ(gambler.getTransactions()[1].first, 3);
    ASSERT_EQ(gambler.getTransactions()[1].second, "Game 1");
    ASSERT_EQ(gambler.getTransactions()[2].first, -12);
    ASSERT_EQ(gambler.getTransactions()[3].first, -14);
    ASSERT_EQ(gambler.totalProfit(), -23);

    gambler.leaveGame();
    gambler.depositBalance(5);
    gambler.joinGame(game2);
    gambler.addBalance(4);
    ASSERT_EQ(gambler.getBalance(), 9);
    ASSERT_EQ(gambler.specificTransactions(game1->getName())[1], -12);
    ASSERT_EQ(gambler.specificTransactions(game2->getName())[0], 4);

    delete game1;
    delete game2;
}

TEST(GamblerTest, TestGamblerDepositBalanceToEmptyAcc) {
    Gambler gracz("Kamil");
    gracz.depositBalance(2);
    ASSERT_EQ(gracz.getBalance(), 2);
    ASSERT_EQ(gracz.getDeposits()[0], 2);
}

TEST(GamblerTest, TestGamblerDepositBalance) {
    Gambler gracz(5, "Kamil");
    gracz.depositBalance(2);
    ASSERT_EQ(gracz.getBalance(), 7);
    ASSERT_EQ(gracz.getDeposits()[0], 5);
    ASSERT_EQ(gracz.getDeposits()[1], 2);
}

TEST(GamblerTest, TestGamblerWithdrawBalance) {
    Gambler gracz(5, "Kamil");
    gracz.withdrawBalance(2);
    ASSERT_EQ(gracz.getBalance(), 3);
    ASSERT_EQ(gracz.getWithdrawals()[0], 2);
}

TEST(GamblerTest, TestGamblerWithdrawTooManyBalance) {
    Gambler gracz(5, "Kamil");
    gracz.withdrawBalance(20);
    ASSERT_EQ(gracz.getBalance(), 5);
    ASSERT_TRUE(gracz.getWithdrawals().empty());
}

TEST(GamblerTest, TestGamblerALotTransactions) {
    Gambler gracz(5, "Kamil");
    gracz.depositBalance(2);
    gracz.withdrawBalance(3);
    gracz.depositBalance(8);
    gracz.withdrawBalance(5);

    ASSERT_EQ(gracz.totalDeposited(), 15);
    ASSERT_EQ(gracz.totalWithdrawed(), 8);
    ASSERT_EQ(gracz.totalProfit(), -7);
}


TEST(GamblerTest, GamblerJoinAndLeaveGame) {
    Game *game1 = new Game(0), *game2 = new Game(0);
    Gambler gambler = Gambler();
    //a gambler can join and leave a game as long as he has enough credits
    ASSERT_FALSE(gambler.leaveGame());
    ASSERT_FALSE(gambler.joinGame(game1));
    ASSERT_EQ(gambler.getCurrentGame(), nullptr);
    gambler.depositBalance(1);
    ASSERT_TRUE(gambler.joinGame(game1));
    ASSERT_EQ(gambler.getCurrentGame(), game1);
    //they can't join two games at once unless they leave
    gambler = Gambler(54, game2);
    ASSERT_FALSE(gambler.joinGame(game1));
    ASSERT_EQ(gambler.getCurrentGame(), game2);
    ASSERT_TRUE(gambler.leaveGame());
    ASSERT_TRUE(gambler.joinGame(game1));
    ASSERT_EQ(gambler.getCurrentGame(), game1);
    //they can't join a game when they are spectating
    gambler.leaveGame();
    gambler.spectate(game1);
    ASSERT_FALSE(gambler.joinGame(game1));
    delete game1;
    delete game2;
}

TEST(GamblerTest, GamblerSetBot) {
    Gambler gambler = Gambler();
    gambler.setBot(true);
    ASSERT_TRUE(gambler.isBot());
    gambler.setBot(false);
    ASSERT_FALSE(gambler.isBot());
}

TEST(GamblerTest, GamblerSetName) {
    Gambler gambler = Gambler();
    ASSERT_EQ(gambler.getName(), "");
    gambler.setName("Marcus Weir");
    ASSERT_EQ(gambler.getName(), "Marcus Weir");
}

TEST(GamblerTest, GamblerSpectateAndStop) {
    Game *game1 = new Game(0), *game2 = new Game(0);
    Gambler gambler = Gambler();
    //gambler can spectate a game
    ASSERT_TRUE(gambler.spectate(game1));
    ASSERT_EQ(gambler.getSpectatedGame(), game1);
    //they can stop spectating
    ASSERT_TRUE(gambler.stopSpectating());
    ASSERT_EQ(gambler.getSpectatedGame(), nullptr);
    //they can change the spectated game
    gambler.spectate(game1);
    ASSERT_TRUE(gambler.spectate(game2));
    ASSERT_EQ(gambler.getSpectatedGame(), game2);
    //they can't stop spectating if they aren't spectating
    ASSERT_TRUE(gambler.stopSpectating());
    ASSERT_EQ(gambler.getSpectatedGame(), nullptr);
    ASSERT_FALSE(gambler.stopSpectating());
    //they can't spectate a game if they are playing
    gambler.depositBalance(1);
    gambler.joinGame(game1);
    ASSERT_FALSE(gambler.spectate(game1));
}

TEST(GuestTest, TestGuestCreate) {
    Guest gosc(5, "Kamil");
    ASSERT_EQ(gosc.getName(), "Kamil");
    ASSERT_EQ(gosc.getBalance(), 5);

    Guest gosc2;
    ASSERT_EQ(gosc2.getName(), "");
    ASSERT_EQ(gosc2.getBalance(), 0);
}

TEST(GuestTest, TestGuestDepositWithdrawTooMany) {
    Guest gosc(1500, "Kamil");
    gosc.depositBalance(110000);
    ASSERT_EQ(gosc.getBalance(), 1500);
    gosc.withdrawBalance(1200);
    ASSERT_EQ(gosc.getBalance(), 1500);
}

TEST(VIPTest, TestVIPCheckPlayerBalance) {
    Guest gosc(150, "Kamil");
    VIP vip(25000, "Elon");
    ASSERT_EQ(vip.checkGamblerBalance(gosc), 150);
}

TEST(VIPTest, TestVIPUsingSafe) {
    VIP vip(25000, "Elon");
    vip.depositToSafe(1000);
    vip.withdrawFromSafe(200);
    ASSERT_EQ(vip.getBalance(), 24200);
    ASSERT_EQ(vip.getSafeValue(), 800);
}

TEST(VIPTest, TestVIPResetStats) {
    VIP vip(25000, "Elon");
    vip.depositBalance(100);
    vip.withdrawBalance(200);
    vip.depositBalance(300);
    vip.withdrawBalance(400);
    vip.resetStats();
    ASSERT_TRUE(vip.getDeposits().empty());
    ASSERT_TRUE(vip.getWithdrawals().empty());
}

TEST(ShopTest, TestShopRemoveItem) {
    Shop shop;
    shop.removeItem("Yacht");
    ASSERT_EQ(shop.getItems()[0].first, "Car");
}