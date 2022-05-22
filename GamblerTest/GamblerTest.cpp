#include <gtest/gtest.h>

#include "Gambler.h"

using namespace std;

TEST(GamblerTest, GamblerCreate) {
    Gambler gambler = Gambler();
    ASSERT_EQ(gambler.getBalance(), 0);
    ASSERT_EQ(gambler.getCurrentGame(), nullptr);
    ASSERT_EQ(gambler.getName(), "");
    ASSERT_FALSE(gambler.isBot());
}

TEST(GamblerTest, GamblerCreateWithName) {
    Gambler gambler = Gambler("Marcus Weir");
    ASSERT_EQ(gambler.getBalance(), 0);
    ASSERT_EQ(gambler.getCurrentGame(), nullptr);
    ASSERT_EQ(gambler.getName(), "Marcus Weir");
    ASSERT_FALSE(gambler.isBot());
}

TEST(GamblerTest, GamblerCreateWithBalance) {
    Gambler gambler = Gambler(23);
    ASSERT_EQ(gambler.getBalance(), 23);
    ASSERT_EQ(gambler.getCurrentGame(), nullptr);
    ASSERT_FALSE(gambler.isBot());
}

TEST(GamblerTest, GamblerCreateWithBalanceAndName) {
    Gambler gambler = Gambler(23, "Marcus Weir");
    ASSERT_EQ(gambler.getBalance(), 23);
    ASSERT_EQ(gambler.getCurrentGame(), nullptr);
    ASSERT_EQ(gambler.getName(), "Marcus Weir");
    ASSERT_FALSE(gambler.isBot());
}

TEST(GamblerTest, GamblerCreateWithBalanceAndGame) {
    Game *game = new Game(0);
    Gambler gambler = Gambler(23, game);
    ASSERT_EQ(gambler.getBalance(), 23);
    ASSERT_EQ(gambler.getCurrentGame(), game);
    ASSERT_FALSE(gambler.isBot());
    delete game;
}

TEST(GamblerTest, GamblerCreateWithBalanceGameAndName) {
    Game *game = new Game(0);
    Gambler gambler = Gambler(23, game, "Marcus Weir");
    ASSERT_EQ(gambler.getBalance(), 23);
    ASSERT_EQ(gambler.getCurrentGame(), game);
    ASSERT_EQ(gambler.getName(), "Marcus Weir");
    ASSERT_FALSE(gambler.isBot());
    delete game;
}

TEST(GamblerTest, GamblerAddBalance) {
    Gambler gambler = Gambler();
    gambler.addBalance(3);
    ASSERT_EQ(gambler.getBalance(), 3);
    gambler = Gambler(45);
    gambler.addBalance(5);
    ASSERT_EQ(gambler.getBalance(), 50);
}

TEST(GamblerTest, GamblerSubtractBalance) {
    Gambler gambler = Gambler(20);
    gambler.subtractBalance(4);
    ASSERT_EQ(gambler.getBalance(), 16);
    gambler = Gambler();
    gambler.subtractBalance(45);
    ASSERT_EQ(gambler.getBalance(), 0);
}

TEST(GamblerTest, GamblerJoinAndLeaveGame) {
    Game *game1 = new Game(0), *game2 = new Game(0);
    Gambler gambler = Gambler();
    //a gambler can join and leave a game as long as he has enough credits
    ASSERT_FALSE(gambler.leaveGame());
    ASSERT_FALSE(gambler.joinGame(game1));
    ASSERT_EQ(gambler.getCurrentGame(), nullptr);
    gambler.addBalance(1);
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
    gambler.addBalance(1);
    gambler.joinGame(game1);
    ASSERT_FALSE(gambler.spectate(game1));
}


TEST(PlayerTest, TestPlayerCreateEmpty)
{
    Player gracz;
    ASSERT_EQ("Player", gracz.getName());
    ASSERT_DOUBLE_EQ(0, gracz.getBalance());
}

TEST(PlayerTest, TestPlayerCreateOnlyName)
{
    Player gracz("Kamil");
    ASSERT_EQ(gracz.getName(), "Kamil");
    ASSERT_DOUBLE_EQ(gracz.getBalance(), 0);
    ASSERT_TRUE(gracz.getDeposits().empty());
}

TEST(PlayerTest, TestPlayerCreate)
{
    Player gracz("Kamil", 5.50);
    ASSERT_EQ(gracz.getName(), "Kamil");
    ASSERT_DOUBLE_EQ(gracz.getBalance(), 5.5);
    ASSERT_DOUBLE_EQ(gracz.getDeposits()[0], 5.5);
}

TEST(PlayerTest, TestPlayerChangeName)
{
    Player gracz("Kamil", 5.50);
    gracz.changeName("Piotrek");
    ASSERT_EQ(gracz.getName(), "Piotrek");
}

TEST(PlayerTest, TestPlayerDepositBalanceToEmptyAcc)
{
    Player gracz("Kamil");
    gracz.depositBalance(2.22);
    ASSERT_DOUBLE_EQ(gracz.getBalance(), 2.22);
    ASSERT_DOUBLE_EQ(gracz.getDeposits()[0], 2.22);
}

TEST(PlayerTest, TestPlayerDepositBalance)
{
    Player gracz("Kamil", 5.50);
    gracz.depositBalance(2.22);
    ASSERT_DOUBLE_EQ(gracz.getBalance(), 7.72);
    ASSERT_DOUBLE_EQ(gracz.getDeposits()[0], 5.50);
    ASSERT_DOUBLE_EQ(gracz.getDeposits()[1], 2.22);
}

TEST(PlayerTest, TestPlayerWithdrawBalance)
{
    Player gracz("Kamil", 5.50);
    gracz.withdrawBalance(2.20);
    ASSERT_DOUBLE_EQ(gracz.getBalance(), 3.30);
    ASSERT_DOUBLE_EQ(gracz.getWithdrawals()[0], 2.20);
}

TEST(PlayerTest, TestPlayerWithdrawTooManyBalance)
{
    Player gracz("Kamil", 5.50);
    gracz.withdrawBalance(20.11);
    ASSERT_DOUBLE_EQ(gracz.getBalance(), 5.50);
    ASSERT_TRUE(gracz.getWithdrawals().empty());
}

TEST(PlayerTest, TestPlayerALotTransactions)
{
    Player gracz("Kamil", 5.50);
    gracz.depositBalance(2.10);
    gracz.withdrawBalance(3.10);
    gracz.depositBalance(8.50);
    gracz.withdrawBalance(5.50);

    ASSERT_DOUBLE_EQ(gracz.totalDeposited(), 16.10);
    ASSERT_DOUBLE_EQ(gracz.totalWithdrawed(), 8.60);
    ASSERT_DOUBLE_EQ(gracz.totalProfit(), -7.50);
}

TEST(PlayerTest, TestGuestCreate)
{
    Guest gosc("Kamil", 5.5);
    ASSERT_EQ("Kamil", gosc.getName());
    ASSERT_DOUBLE_EQ(5.5, gosc.getBalance());

    Guest gosc2;
    ASSERT_EQ("Player", gosc2.getName());
    ASSERT_DOUBLE_EQ(0, gosc2.getBalance());
}

TEST(PlayerTest, TestGuestDepositWithdrawTooMany)
{
    Guest gosc("Kamil", 1500);
    gosc.depositBalance(110000);
    ASSERT_DOUBLE_EQ(1500, gosc.getBalance());
    gosc.withdrawBalance(1200);
    ASSERT_DOUBLE_EQ(1500, gosc.getBalance());
}

TEST(PlayerTest, TestVIPCheckPlayerBalance)
{
    Guest gosc("Kamil", 150);
    VIP vip("Elon", 25000);
    ASSERT_DOUBLE_EQ(150, vip.checkPlayerBalance(gosc));
}

TEST(PlayerTest, TestVIPUsingSafe)
{
    VIP vip("Elon", 25000);
    vip.depositToSafe(1000);
    vip.withdrawFromSafe(200);
    ASSERT_DOUBLE_EQ(24200, vip.getBalance());
    ASSERT_DOUBLE_EQ(800, vip.getSafeValue());
}

TEST(PlayerTest, TestVIPResetStats)
{
    VIP vip("Elon", 25000);
    vip.depositBalance(100);
    vip.withdrawBalance(200);
    vip.depositBalance(300);
    vip.withdrawBalance(400);
    vip.resetStats();
    ASSERT_TRUE(vip.getDeposits().empty());
    ASSERT_TRUE(vip.getWithdrawals().empty());
}

TEST(PlayerTest, TestShopRemoveItem)
{
    Shop shop;
    shop.removeItem("Yacht");
    ASSERT_EQ(shop.getItems()[0].first, "Car");
}