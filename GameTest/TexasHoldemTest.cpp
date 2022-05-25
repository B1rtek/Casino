#include <gtest/gtest.h>

#include "TexasHoldem.h"
#include "TexasBot.h"

using namespace std;

TEST(TexasHoldemTest, TexasHoldemCreate) {
    TexasHoldem texasHoldem = TexasHoldem(1000, "Texas for newbies");
    ASSERT_EQ(texasHoldem.getCurrentBets().size(), 0);
    ASSERT_EQ(texasHoldem.getInGameMoney().size(), 0);
    ASSERT_EQ(texasHoldem.getPlayers().size(), 0);
    ASSERT_EQ(texasHoldem.getSpectators().size(), 0);
    ASSERT_EQ(texasHoldem.getMinimumEntry(), 1000);
    ASSERT_EQ(texasHoldem.getName(), "Texas for newbies");
    ASSERT_FALSE(texasHoldem.isInProgress());
    ASSERT_EQ(texasHoldem.getDeck(), CardGame::deck);
    ASSERT_EQ(texasHoldem.getGamblersCards().size(), 0);
    ASSERT_EQ(texasHoldem.getNotFolded().size(), 0);
    ASSERT_EQ(texasHoldem.getCurrentPlayer(), nullptr);
    ASSERT_EQ(texasHoldem.getCurrentDealtCards().size(), 5);
    ASSERT_THROW(TexasHoldem(420), std::invalid_argument);
}

TEST(TexasHoldemTest, TexasHoldemCreateWithGambler) {
    auto *gambler = new Gambler(999), *gambler2 = new Gambler(1001);
    auto *pTexasHoldem = new TexasHoldem(gambler, 1000);
    //not enough balance to join
    ASSERT_EQ(pTexasHoldem->getCurrentBets().size(), 0);
    ASSERT_EQ(pTexasHoldem->getInGameMoney().size(), 0);
    ASSERT_EQ(pTexasHoldem->getPlayers().size(), 0);
    ASSERT_EQ(pTexasHoldem->getSpectators().size(), 0);
    ASSERT_EQ(pTexasHoldem->getMinimumEntry(), 1000);
    ASSERT_EQ(pTexasHoldem->getName(), "");
    ASSERT_EQ(gambler->getBalance(), 999);
    ASSERT_EQ(gambler->getCurrentGame(), nullptr);
    ASSERT_FALSE(pTexasHoldem->isInProgress());
    ASSERT_EQ(pTexasHoldem->getDeck(), CardGame::deck);
    ASSERT_EQ(pTexasHoldem->getGamblersCards().size(), 0);
    ASSERT_EQ(pTexasHoldem->getNotFolded().size(), 0);
    ASSERT_EQ(pTexasHoldem->getCurrentPlayer(), nullptr);
    ASSERT_EQ(pTexasHoldem->getCurrentDealtCards().size(), 5);
    delete pTexasHoldem;
    pTexasHoldem = new TexasHoldem(gambler2, 1000);
    // enough balance to join
    ASSERT_EQ(pTexasHoldem->getCurrentBets().size(), 1);
    ASSERT_EQ(pTexasHoldem->getCurrentBets()[gambler2], 0);
    ASSERT_EQ(pTexasHoldem->getInGameMoney().size(), 1);
    ASSERT_EQ(pTexasHoldem->getInGameMoney()[gambler2], 1000);
    ASSERT_EQ(pTexasHoldem->getPlayers().size(), 1);
    ASSERT_EQ(pTexasHoldem->getSpectators().size(), 0);
    ASSERT_EQ(pTexasHoldem->getMinimumEntry(), 1000);
    ASSERT_EQ(pTexasHoldem->getName(), "");
    ASSERT_EQ(gambler2->getBalance(), 1);
    ASSERT_EQ(gambler2->getCurrentGame(), pTexasHoldem);
    ASSERT_FALSE(pTexasHoldem->isInProgress());
    ASSERT_EQ(pTexasHoldem->getDeck(), CardGame::deck);
    ASSERT_EQ(pTexasHoldem->getGamblersCards().size(), 1);
    ASSERT_EQ(pTexasHoldem->getNotFolded().size(), 1);
    ASSERT_EQ(pTexasHoldem->getCurrentPlayer(), nullptr);
    ASSERT_EQ(pTexasHoldem->getCurrentDealtCards().size(), 5);
    ASSERT_THROW(TexasHoldem(gambler, 999), std::invalid_argument);
    delete pTexasHoldem;
    delete gambler;
    delete gambler2;
}

TEST(TexasHoldemTest, TexasHoldemCreateWithGamblers) {
    auto *gambler1 = new Gambler(5), *gambler2 = new Gambler(4200);
    vector<Gambler *> gamblers = {gambler1, gambler2};
    auto *pTexasHoldem = new TexasHoldem(gamblers, 1000);
    // gambler1 couldn't join the game due to not having enough balance
    ASSERT_EQ(pTexasHoldem->getCurrentBets().size(), 1);
    ASSERT_EQ(pTexasHoldem->getCurrentBets()[gambler2], 0);
    ASSERT_EQ(pTexasHoldem->getInGameMoney().size(), 1);
    ASSERT_EQ(pTexasHoldem->getInGameMoney()[gambler2], 1000);
    ASSERT_EQ(pTexasHoldem->getPlayers().size(), 1);
    ASSERT_EQ(pTexasHoldem->getSpectators().size(), 0);
    ASSERT_EQ(pTexasHoldem->getMinimumEntry(), 1000);
    ASSERT_EQ(pTexasHoldem->getName(), "");
    ASSERT_EQ(gambler2->getBalance(), 3200);
    ASSERT_EQ(gambler2->getCurrentGame(), pTexasHoldem);
    ASSERT_FALSE(pTexasHoldem->isInProgress());
    ASSERT_EQ(pTexasHoldem->getDeck(), CardGame::deck);
    ASSERT_EQ(pTexasHoldem->getGamblersCards().size(), 1);
    ASSERT_EQ(pTexasHoldem->getNotFolded().size(), 1);
    ASSERT_EQ(pTexasHoldem->getCurrentPlayer(), nullptr);
    ASSERT_EQ(pTexasHoldem->getCurrentDealtCards().size(), 5);
    ASSERT_THROW(TexasHoldem(gamblers, 997), std::invalid_argument);
    delete gambler1;
    delete gambler2;
    delete pTexasHoldem;
}

TEST(TexasHoldemTest, AddPlayer) {
    auto *texasHoldem = new TexasHoldem(1000);
    auto *gambler = new Gambler(999);
    ASSERT_FALSE(gambler->joinGame(texasHoldem));
    ASSERT_EQ(texasHoldem->getPlayers().size(), 0);
    ASSERT_EQ(texasHoldem->getNotFolded().size(), 0);
    ASSERT_EQ(texasHoldem->getGamblersCards().size(), 0);
    gambler->addBalance(2);
    ASSERT_TRUE(gambler->joinGame(texasHoldem));
    ASSERT_EQ(texasHoldem->getPlayers().size(), 1);
    ASSERT_EQ(texasHoldem->getNotFolded().size(), 1);
    ASSERT_EQ(texasHoldem->getGamblersCards().size(), 1);
    // add until max players
    std::vector<Gambler *> moreGamblers;
    for (int i = 2; i <= 10; i++) {
        auto *gambler2 = new Gambler(10000);
        ASSERT_TRUE(gambler2->joinGame(texasHoldem));
        moreGamblers.push_back(gambler2);
        ASSERT_EQ(texasHoldem->getPlayers().size(), i);
        ASSERT_EQ(texasHoldem->getNotFolded().size(), i);
        ASSERT_EQ(texasHoldem->getGamblersCards().size(), i);
    }
    // trying to add any more gamblers will fail {
    for (int i = 0; i < 50; i++) {
        auto *gambler2 = new Gambler(10000);
        ASSERT_FALSE(gambler2->joinGame(texasHoldem));
        delete gambler2;
    }
    // spectators can still join
    auto *gambler2 = new Gambler();
    ASSERT_TRUE(gambler2->spectate(texasHoldem));
    ASSERT_EQ(texasHoldem->getSpectators().size(), 1);
    ASSERT_TRUE(gambler2->stopSpectating());
    ASSERT_EQ(texasHoldem->getSpectators().size(), 0);
    for (auto &mgambler: moreGamblers) {
        delete mgambler;
    }
    delete gambler;
    delete texasHoldem;
}

TEST(TexasHoldemTest, RemovePlayer) {
    auto *texasHoldem = new TexasHoldem(1000);
    auto *gambler = new Gambler(1001), *gambler2 = new Gambler(1002);
    ASSERT_TRUE(gambler->joinGame(texasHoldem));
    ASSERT_TRUE(gambler2->joinGame(texasHoldem));
    ASSERT_EQ(texasHoldem->getPlayers().size(), 2);
    ASSERT_EQ(texasHoldem->getNotFolded().size(), 2);
    ASSERT_EQ(texasHoldem->getGamblersCards().size(), 2);
    ASSERT_TRUE(gambler->leaveGame());
    ASSERT_EQ(texasHoldem->getPlayers().size(), 1);
    ASSERT_EQ(texasHoldem->getNotFolded().size(), 1);
    ASSERT_EQ(texasHoldem->getGamblersCards().size(), 1);
    std::map<Gambler *, bool> notFolded = texasHoldem->getNotFolded();
    ASSERT_TRUE(notFolded.find(gambler) == notFolded.end());
    delete gambler;
    delete gambler2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, CalculateHand) {
    // best possible combination - AKQJ10 HEARTS
    std::vector<Card *> hand = {CardGame::deck[39], CardGame::deck[51], CardGame::deck[49], CardGame::deck[50],
                                CardGame::deck[48]};
    std::pair<TexasHoldemHand, Card *> calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, STRAIGHT_FLUSH);
    ASSERT_EQ(calculatedBest.second, CardGame::deck[39]);
    // other straight flush - 23456 CLUBS
    hand = {CardGame::deck[1], CardGame::deck[2], CardGame::deck[3], CardGame::deck[4], CardGame::deck[5]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, STRAIGHT_FLUSH);
    ASSERT_EQ(calculatedBest.second, CardGame::deck[5]);
    // four of a kind - ACE of every color + random other
    hand = {CardGame::deck[0], CardGame::deck[13], CardGame::deck[35], CardGame::deck[26], CardGame::deck[39]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, FOUR_OF_A_KIND);
    ASSERT_EQ(calculatedBest.second->getValue(), ACE);
    // lowest four of a kind
    hand = {CardGame::deck[1], CardGame::deck[14], CardGame::deck[39], CardGame::deck[27], CardGame::deck[40]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, FOUR_OF_A_KIND);
    ASSERT_EQ(calculatedBest.second->getValue(), N2);
    // highest full house
    hand = {CardGame::deck[39], CardGame::deck[38], CardGame::deck[26], CardGame::deck[25], CardGame::deck[13]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, FULL_HOUSE);
    ASSERT_EQ(calculatedBest.second->getValue(), ACE);
    // lowest full house
    hand = {CardGame::deck[1], CardGame::deck[38], CardGame::deck[14], CardGame::deck[25], CardGame::deck[27]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, FULL_HOUSE);
    ASSERT_EQ(calculatedBest.second->getValue(), N2);
    // flush
    hand = {CardGame::deck[1], CardGame::deck[2], CardGame::deck[5], CardGame::deck[12], CardGame::deck[3]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, FLUSH);
    ASSERT_EQ(calculatedBest.second, CardGame::deck[12]);
    // lowest straight
    hand = {CardGame::deck[1], CardGame::deck[15], CardGame::deck[43], CardGame::deck[29], CardGame::deck[44]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, STRAIGHT);
    ASSERT_EQ(calculatedBest.second, CardGame::deck[44]);
    // higher (not necessarily est) straight
    hand = {CardGame::deck[0], CardGame::deck[24], CardGame::deck[38], CardGame::deck[22], CardGame::deck[10]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, STRAIGHT);
    ASSERT_EQ(calculatedBest.second, CardGame::deck[0]);
    // three of a kind
    hand = {CardGame::deck[0], CardGame::deck[13], CardGame::deck[38], CardGame::deck[26], CardGame::deck[10]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, THREE_OF_A_KIND);
    ASSERT_EQ(calculatedBest.second->getValue(), ACE);
    // three of a kind where three has lower value than high card
    hand = {CardGame::deck[1], CardGame::deck[14], CardGame::deck[0], CardGame::deck[27], CardGame::deck[10]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, THREE_OF_A_KIND);
    ASSERT_EQ(calculatedBest.second->getValue(), N2);
    // two pairs
    hand = {CardGame::deck[1], CardGame::deck[2], CardGame::deck[14], CardGame::deck[15], CardGame::deck[0]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, TWO_PAIRS);
    ASSERT_EQ(calculatedBest.second->getValue(), N3);
    // one pair
    hand = {CardGame::deck[1], CardGame::deck[24], CardGame::deck[14], CardGame::deck[38], CardGame::deck[0]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, ONE_PAIR);
    ASSERT_EQ(calculatedBest.second->getValue(), N2);
    // high card
    hand = {CardGame::deck[0], CardGame::deck[14], CardGame::deck[29], CardGame::deck[49], CardGame::deck[44]};
    calculatedBest = TexasHoldem::calculateHand(hand);
    ASSERT_EQ(calculatedBest.first, HIGH_CARD);
    ASSERT_EQ(calculatedBest.second, CardGame::deck[0]);
}

TEST(TexasHoldemTest, AdvanceGameStart) {
    auto *gambler1 = new Gambler(1337), *gambler2 = new Gambler(1338), *gambler3 = new Gambler(1339);
    auto *texasHoldem = new TexasHoldem(gambler1, 1000);
    ASSERT_EQ(texasHoldem->getPlayers().size(), 1);
    ASSERT_EQ(texasHoldem->getInGameMoney()[gambler1], 1000);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), nullptr);
    ASSERT_FALSE(texasHoldem->isInProgress());
    texasHoldem->advanceGame(30000);
    // game didn't start because there isn't enough players to start
    ASSERT_EQ(texasHoldem->getTargetTime(), 60000);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getInGameMoney()[gambler1], 1000);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), nullptr);
    ASSERT_TRUE(gambler2->joinGame(texasHoldem));
    texasHoldem->advanceGame(60000);
    // game should start now, state should be set to SMALL_BLIND
    // current player should be the dealer, which is the first player
    ASSERT_TRUE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getGameState(), SMALL_BLIND);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), gambler1);
    ASSERT_EQ(texasHoldem->getTargetTime(), 60000); // no target specified
    delete gambler1;
    delete gambler2;
    delete texasHoldem;
    gambler1 = new Gambler(1337);
    gambler2 = new Gambler(1338);
    texasHoldem = new TexasHoldem(1000);
    ASSERT_TRUE(gambler1->joinGame(texasHoldem));
    ASSERT_TRUE(gambler2->joinGame(texasHoldem));
    ASSERT_TRUE(gambler3->joinGame(texasHoldem));
    texasHoldem->advanceGame(30000);
    // game should start now, state should be set to SMALL_BLIND
    // current player should be the player to the left of the dealer, which is the second player
    ASSERT_TRUE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getGameState(), SMALL_BLIND);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), gambler2);
    ASSERT_EQ(texasHoldem->getTargetTime(), 30000); // no target specified
    delete gambler1;
    delete gambler2;
    delete gambler3;
    delete texasHoldem;
}

TEST(TexasHoldemTest, AdvanceGameBlindsAndPreflop) {
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new TexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    ASSERT_FALSE(texasHoldem->call(gambler1)); // it's not gambler's turn, so it shouldn't work
    for (auto &gambler: texasHoldem->getPlayers()) {
        vector<Card *> gamblersCards = texasHoldem->getGamblersCards()[gambler];
        for (auto &card: gamblersCards) {
            ASSERT_EQ(*card, Card()); // all cards should be NONE cards during blinds
        }
    }
    for (auto &card: texasHoldem->getCurrentDealtCards()) {
        ASSERT_EQ(*card, Card()); // all cards should be NONE cards during blinds
    }
    ASSERT_EQ(texasHoldem->getGameState(), SMALL_BLIND);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot1);
    texasHoldem->advanceGame(30001); // bot1 should call, which means that they should pay the small blind
    for (auto &gambler: texasHoldem->getPlayers()) {
        vector<Card *> gamblersCards = texasHoldem->getGamblersCards()[gambler];
        for (auto &card: gamblersCards) {
            ASSERT_EQ(*card, Card()); // all cards should be NONE cards during blinds
        }
    }
    for (auto &card: texasHoldem->getCurrentDealtCards()) {
        ASSERT_EQ(*card, Card()); // all cards should be NONE before flop
    }
    ASSERT_EQ(texasHoldem->getGameState(), BIG_BLIND);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 1);
    texasHoldem->advanceGame(30002); // bot 2 should try to raise, which can't be done during big blind
    for (auto &gambler: texasHoldem->getPlayers()) {
        vector<Card *> gamblersCards = texasHoldem->getGamblersCards()[gambler];
        for (auto &card: gamblersCards) {
            ASSERT_EQ(*card, Card()); // all cards should be NONE cards during blinds
        }
    }
    for (auto &card: texasHoldem->getCurrentDealtCards()) {
        ASSERT_EQ(*card, Card()); // all cards should be NONE before flop
    }
    ASSERT_EQ(texasHoldem->getGameState(), BIG_BLIND);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot2], 0);
    texasHoldem->advanceGame(30003); // bot 2 should try to fold, it can't be done during blinds
    for (auto &gambler: texasHoldem->getPlayers()) {
        vector<Card *> gamblersCards = texasHoldem->getGamblersCards()[gambler];
        for (auto &card: gamblersCards) {
            ASSERT_EQ(*card, Card()); // all cards should be NONE cards during blinds
        }
    }
    for (auto &card: texasHoldem->getCurrentDealtCards()) {
        ASSERT_EQ(*card, Card()); // all cards should be NONE before flop
    }
    ASSERT_TRUE(texasHoldem->getNotFolded()[bot2]);
    ASSERT_EQ(texasHoldem->getGameState(), BIG_BLIND);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot2], 0);
    texasHoldem->advanceGame(30004); // bot 2 should call, which translates to big blind
    for (auto &gambler: texasHoldem->getPlayers()) {
        vector<Card *> gamblersCards = texasHoldem->getGamblersCards()[gambler];
        for (auto &card: gamblersCards) {
            ASSERT_FALSE(*card == Card()); // all cards should be NONE cards during blinds
        }
    }
    for (auto &card: texasHoldem->getCurrentDealtCards()) {
        ASSERT_EQ(*card, Card()); // all cards should be NONE before flop
    }
    ASSERT_EQ(texasHoldem->getGameState(), PREFLOP);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), gambler1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot2], 2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[gambler1], 0);
    ASSERT_TRUE(texasHoldem->fold(gambler1)); // now gambler should be able to fold
    for (auto &card: texasHoldem->getCurrentDealtCards()) {
        ASSERT_EQ(*card, Card()); // all cards should be NONE before flop
    }
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot2], 2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[gambler1], 0);
    ASSERT_EQ(texasHoldem->getGameState(), PREFLOP); // bot 1 still needs to call 1
    texasHoldem->advanceGame(30005); // but they decide to raise 2
    for (auto &card: texasHoldem->getCurrentDealtCards()) {
        ASSERT_EQ(*card, Card()); // all cards should be NONE before flop
    }
    ASSERT_EQ(texasHoldem->getGameState(), PREFLOP);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 3);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot2], 2);
    texasHoldem->advanceGame(30006); // bot 2 decides to fold because of that, game ends
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getInGameMoney()[gambler1], 1000);
    ASSERT_EQ(texasHoldem->getInGameMoney()[bot1], 1002);
    ASSERT_EQ(texasHoldem->getInGameMoney()[bot2], 998);
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_TRUE(bot2->leaveGame()); // bot 2 decides to leave after that devastating loss
    texasHoldem->advanceGame(60010); // next game starts
    ASSERT_EQ(texasHoldem->getCurrentPlayer(),
              bot1); // because bot1 is the dealer now - when 2 people play, dealer starts
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, GameEndInFlop) {
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new TexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    ASSERT_EQ(texasHoldem->getGameState(), FLOP);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot2], 2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[gambler1], 2);
    for (unsigned int i = 0; i < 3; i++) {
        ASSERT_FALSE(*texasHoldem->getCurrentDealtCards()[i] == Card()); // first 3 cards should be visible
    }
    for (unsigned int i = 3; i < 5; i++) {
        ASSERT_EQ(*texasHoldem->getCurrentDealtCards()[i], Card());
    }
    texasHoldem->advanceGame(30010); // bot2 checks
    ASSERT_EQ(texasHoldem->getGameState(), FLOP);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), gambler1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot2], 2);
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    ASSERT_EQ(texasHoldem->getGameState(), FLOP);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[gambler1], 4);
    texasHoldem->advanceGame(30012); // bot1 folds
    ASSERT_EQ(texasHoldem->getGameState(), FLOP);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 2);
    texasHoldem->advanceGame(30015); // bot2 folds
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN); // game ends
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getInGameMoney()[gambler1], 1004);
    ASSERT_EQ(texasHoldem->getInGameMoney()[bot1], 998);
    ASSERT_EQ(texasHoldem->getInGameMoney()[bot2], 998);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, GameEndInTurn) {
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new TexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls
    ASSERT_EQ(texasHoldem->getGameState(), TURN);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), gambler1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 4);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot2], 4);
    ASSERT_EQ(texasHoldem->getCurrentBets()[gambler1], 4);
    for (unsigned int i = 0; i < 4; i++) {
        ASSERT_FALSE(*texasHoldem->getCurrentDealtCards()[i] == Card()); // first 4 cards should be visible
    }
    for (unsigned int i = 4; i < 5; i++) {
        ASSERT_EQ(*texasHoldem->getCurrentDealtCards()[i], Card());
    }
    texasHoldem->call(gambler1); // gambler1 checks
    ASSERT_EQ(texasHoldem->getGameState(), TURN);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[gambler1], 4);
    texasHoldem->advanceGame(30016); // bot1 checks
    ASSERT_EQ(texasHoldem->getGameState(), TURN);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 4);
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    ASSERT_EQ(texasHoldem->getGameState(), TURN);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), gambler1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot2], 6);
    texasHoldem->fold(gambler1); // gambler1 folds
    ASSERT_EQ(texasHoldem->getGameState(), TURN);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[gambler1], 4);
    ASSERT_FALSE(texasHoldem->getNotFolded()[gambler1]);
    texasHoldem->advanceGame(30018); // bot1 folds, game ends
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getInGameMoney()[gambler1], 996);
    ASSERT_EQ(texasHoldem->getInGameMoney()[bot1], 996);
    ASSERT_EQ(texasHoldem->getInGameMoney()[bot2], 1008);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, GameEndInRiverByFold) {
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new TexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    ASSERT_EQ(texasHoldem->getGameState(), RIVER);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 6);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot2], 6);
    ASSERT_EQ(texasHoldem->getCurrentBets()[gambler1], 6);
    for (unsigned int i = 0; i < 5; i++) {
        ASSERT_FALSE(*texasHoldem->getCurrentDealtCards()[i] == Card()); // all cards should be visible
    }
    texasHoldem->advanceGame(30020); // bot 2 raises
    ASSERT_EQ(texasHoldem->getGameState(), RIVER);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), gambler1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot2], 8);
    texasHoldem->raise(gambler1, 4); // gambler1 raises even more
    ASSERT_EQ(texasHoldem->getGameState(), RIVER);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot1);
    ASSERT_EQ(texasHoldem->getCurrentBets()[gambler1], 10);
    texasHoldem->advanceGame(30021); // bot 1 folds
    ASSERT_EQ(texasHoldem->getGameState(), RIVER);
    ASSERT_EQ(texasHoldem->getCurrentPlayer(), bot2);
    ASSERT_EQ(texasHoldem->getCurrentBets()[bot1], 6);
    texasHoldem->advanceGame(30024); // bot 2 folds as well, game ends
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getInGameMoney()[gambler1], 1014);
    ASSERT_EQ(texasHoldem->getInGameMoney()[bot1], 994);
    ASSERT_EQ(texasHoldem->getInGameMoney()[bot2], 992);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, GameEndInRiver) {
    class FakeTexasHoldem : public TexasHoldem {
        public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
        TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override {
            this->gameDeck = {CardGame::deck[39], CardGame::deck[51], CardGame::deck[49], CardGame::deck[0], CardGame::deck[1],
                              CardGame::deck[50], CardGame::deck[48], //gambler1's cards (royal straight flush)
                              CardGame::deck[40], CardGame::deck[41], //bot1's cards (flush)
                              CardGame::deck[10], CardGame::deck[15]}; //bot2's cards (something random)
        }
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getInGameMoney()[gambler1], 1016); // should win with the straight flush
    ASSERT_EQ(texasHoldem->getInGameMoney()[bot1], 992);
    ASSERT_EQ(texasHoldem->getInGameMoney()[bot2], 992);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, StraightFlushTripleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 7 C, 6 C, 5 C, 3 C, 4 C
            this->gameDeck = {CardGame::deck[6], CardGame::deck[5], CardGame::deck[4], CardGame::deck[3], CardGame::deck[2],
                              CardGame::deck[14], CardGame::deck[21], //gambler1's cards (2 D, 9 D)
                              CardGame::deck[34], CardGame::deck[27], //bot1's cards (9 S, 2 S)
                              CardGame::deck[49], CardGame::deck[17]}; //bot2's cards (J H, 5 D)
        } // expected: everyone wins because a straight flush is already on the table
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 3);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, StraightFlush) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 7 D, 6 C, 5 C, 3 C, 4 C
            this->gameDeck = {CardGame::deck[19], CardGame::deck[5], CardGame::deck[4], CardGame::deck[3], CardGame::deck[2],
                              CardGame::deck[2], CardGame::deck[21], //gambler1's cards (2 C, 9 D)
                              CardGame::deck[34], CardGame::deck[27], //bot1's cards (9 S, 2 S)
                              CardGame::deck[49], CardGame::deck[6]}; //bot2's cards (J H, 7 C)
        } // expected: bot2 wins with a higher straight flush than gambler1
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 1);
    ASSERT_EQ(texasHoldem->getLastGameWinners()[0], bot2);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}


TEST(TexasHoldemTest, FourOfAKindTripleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // A H, 3 H, 3 S, 3 D, 3 C
            this->gameDeck = {CardGame::deck[39], CardGame::deck[41], CardGame::deck[28], CardGame::deck[15], CardGame::deck[2],
                              CardGame::deck[21], CardGame::deck[40], //gambler1's cards (2 H, 9 D)
                              CardGame::deck[34], CardGame::deck[27], //bot1's cards (9 S, 2 S)
                              CardGame::deck[49], CardGame::deck[9]}; //bot2's cards (J H, 10 C)
        } // expected: everyone wins because a four of a kind is already on the table with a kicker ace hearts
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 3);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, FourOfAKindDoubleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 4 H, 3 H, 3 S, 3 D, 3 C
            this->gameDeck = {CardGame::deck[42], CardGame::deck[41], CardGame::deck[28], CardGame::deck[15], CardGame::deck[2],
                              CardGame::deck[21], CardGame::deck[40], //gambler1's cards (2 H, 9 D)
                              CardGame::deck[35], CardGame::deck[27], //bot1's cards (10 S, 2 S)
                              CardGame::deck[47], CardGame::deck[9]}; //bot2's cards (9 H, 10 C)
        } // expected: bot1 and bot2 win by kicker 10s
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 2);
    ASSERT_TRUE(texasHoldem->getLastGameWinners()[0] == bot2 || texasHoldem->getLastGameWinners()[1] == bot2);
    ASSERT_TRUE(texasHoldem->getLastGameWinners()[0] == bot1 || texasHoldem->getLastGameWinners()[1] == bot1);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, FullHouseTripleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 2 C, 2 D, 3 S, 3 D, 3 C
            this->gameDeck = {CardGame::deck[1], CardGame::deck[14], CardGame::deck[28], CardGame::deck[15], CardGame::deck[2],
                              CardGame::deck[21], CardGame::deck[40], //gambler1's cards (2 H, 9 D)
                              CardGame::deck[34], CardGame::deck[27], //bot1's cards (9 S, 2 S)
                              CardGame::deck[49], CardGame::deck[9]}; //bot2's cards (J H, 10 C)
        } // expected: everyone wins because a full house is already on the table and gamblers can't make it better
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 3);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, FullHouseDoubleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 4 C, 2 D, 3 S, 3 D, 3 C
            this->gameDeck = {CardGame::deck[3], CardGame::deck[14], CardGame::deck[28], CardGame::deck[15], CardGame::deck[2],
                              CardGame::deck[14], CardGame::deck[40], //gambler1's cards (2 H, 9 D)
                              CardGame::deck[34], CardGame::deck[27], //bot1's cards (9 S, 2 S)
                              CardGame::deck[49], CardGame::deck[9]}; //bot2's cards (J H, 10 C)
        } // expected: gambler1 and bot1 win because they can complete the full house
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 2);
    ASSERT_TRUE(texasHoldem->getLastGameWinners()[0] == gambler1 || texasHoldem->getLastGameWinners()[1] == gambler1);
    ASSERT_TRUE(texasHoldem->getLastGameWinners()[0] == bot1 || texasHoldem->getLastGameWinners()[1] == bot1);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, FullHouseDoubleTie2) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 2 C, 2 D, 4 S, 3 D, 3 C
            this->gameDeck = {CardGame::deck[1], CardGame::deck[14], CardGame::deck[29], CardGame::deck[15], CardGame::deck[2],
                              CardGame::deck[21], CardGame::deck[41], //gambler1's cards (3 H, 9 D)
                              CardGame::deck[34], CardGame::deck[28], //bot1's cards (9 S, 3 S)
                              CardGame::deck[49], CardGame::deck[9]}; //bot2's cards (J H, 10 C)
        } // expected: both gambler1 and bot1 win because they can complete the full house
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 2);
    ASSERT_TRUE(texasHoldem->getLastGameWinners()[0] == gambler1 || texasHoldem->getLastGameWinners()[1] == gambler1);
    ASSERT_TRUE(texasHoldem->getLastGameWinners()[0] == bot1 || texasHoldem->getLastGameWinners()[1] == bot1);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, FlushTripleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // K C, 6 C, 5 C, 4 C, 3 C
            this->gameDeck = {CardGame::deck[12], CardGame::deck[5], CardGame::deck[4], CardGame::deck[3], CardGame::deck[2],
                              CardGame::deck[14], CardGame::deck[21], //gambler1's cards (2 D, 9 D)
                              CardGame::deck[34], CardGame::deck[27], //bot1's cards (9 S, 2 S)
                              CardGame::deck[49], CardGame::deck[9]}; //bot2's cards (J H, 10 C)
        } // expected: everyone wins because a flush is already on the table
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 3);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, FlushDoubleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // K C, 6 C, 5 C, 4 C, 9 D
            this->gameDeck = {CardGame::deck[12], CardGame::deck[5], CardGame::deck[4], CardGame::deck[3], CardGame::deck[21],
                              CardGame::deck[14], CardGame::deck[2], //gambler1's cards (2 D, 3 C)
                              CardGame::deck[34], CardGame::deck[27], //bot1's cards (9 S, 2 S)
                              CardGame::deck[49], CardGame::deck[9]}; //bot2's cards (J H, 10 C)
        } // expected: gambler1 and bot2 tie with a clubs flush with king being the highest card
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 2);
    ASSERT_TRUE(texasHoldem->getLastGameWinners()[0] == gambler1 || texasHoldem->getLastGameWinners()[1] == gambler1);
    ASSERT_TRUE(texasHoldem->getLastGameWinners()[0] == bot2 || texasHoldem->getLastGameWinners()[1] == bot2);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, StraightTripleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 7 C, 6 D, 5 H, 3 S, 4 C
            this->gameDeck = {CardGame::deck[6], CardGame::deck[18], CardGame::deck[43], CardGame::deck[3], CardGame::deck[28],
                              CardGame::deck[14], CardGame::deck[21], //gambler1's cards (2 D, 9 D)
                              CardGame::deck[34], CardGame::deck[27], //bot1's cards (9 S, 2 S)
                              CardGame::deck[49], CardGame::deck[4]}; //bot2's cards (J H, 5 C)
        } // expected: everyone wins because a straight is already on the table
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 3);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, StraightDoubleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 7 C, 7 D, 7 H, 3 S, K C
            this->gameDeck = {CardGame::deck[6], CardGame::deck[19], CardGame::deck[45], CardGame::deck[28], CardGame::deck[12],
                              CardGame::deck[22], CardGame::deck[20], //gambler1's cards (10 D, 8 D)
                              CardGame::deck[34], CardGame::deck[33], //bot1's cards (9 S, 8 S)
                              CardGame::deck[49], CardGame::deck[3]}; //bot2's cards (J H, 4 C)
        } // expected: triple tie because every player choose K C as kicker
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 3);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, ThreeOfAKindTripleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 7 C, 7 D, 7 H, 3 S, K C
            this->gameDeck = {CardGame::deck[6], CardGame::deck[19], CardGame::deck[45], CardGame::deck[28], CardGame::deck[12],
                              CardGame::deck[22], CardGame::deck[20], //gambler1's cards (10 D, 8 D)
                              CardGame::deck[34], CardGame::deck[33], //bot1's cards (9 S, 8 S)
                              CardGame::deck[49], CardGame::deck[3]}; //bot2's cards (J H, 4 C)
        } // expected: triple tie because every player choose K C as kicker
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 3);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, ThreeOfAKind) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 7 C, 7 D, 10 D, 3 S, 8 D
            this->gameDeck = {CardGame::deck[6], CardGame::deck[19], CardGame::deck[22], CardGame::deck[28], CardGame::deck[20],
                              CardGame::deck[45], CardGame::deck[12], //gambler1's cards (7 H, K C)
                              CardGame::deck[32], CardGame::deck[34], //bot1's cards (7 S, 9 S)
                              CardGame::deck[49], CardGame::deck[3]}; //bot2's cards (J H, 4 C)
        } // expected: gambler1 wins with K C as kicker
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 1);
    ASSERT_EQ(texasHoldem->getLastGameWinners()[0], gambler1);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, DoublePairTripleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 7 C, 7 D, 3 H, 3 S, K C
            this->gameDeck = {CardGame::deck[6], CardGame::deck[19], CardGame::deck[41], CardGame::deck[28], CardGame::deck[12],
                              CardGame::deck[22], CardGame::deck[20], //gambler1's cards (10 D, 8 D)
                              CardGame::deck[34], CardGame::deck[33], //bot1's cards (9 S, 8 S)
                              CardGame::deck[49], CardGame::deck[3]}; //bot2's cards (J H, 4 C)
        } // expected: triple tie because every player choose K C as kicker
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 3);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, DoublePairTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // 4 C, 7 D, 3 H, 3 S, 7 C
            this->gameDeck = {CardGame::deck[3], CardGame::deck[19], CardGame::deck[41], CardGame::deck[28], CardGame::deck[6],
                              CardGame::deck[22], CardGame::deck[20], //gambler1's cards (10 D, 8 D)
                              CardGame::deck[34], CardGame::deck[33], //bot1's cards (9 S, 8 S)
                              CardGame::deck[49], CardGame::deck[12]}; //bot2's cards (J H, K C)
        } // expected: bot 2 wins by king kicker with double pair
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 1);
    ASSERT_EQ(texasHoldem->getLastGameWinners()[0], bot2);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, SinglePairTripleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // A S, A H, K C, Q C, J C
            this->gameDeck = {CardGame::deck[26], CardGame::deck[39], CardGame::deck[12], CardGame::deck[11], CardGame::deck[10],
                              CardGame::deck[34], CardGame::deck[33], //gambler1's cards (9 S, 8 S)
                              CardGame::deck[47], CardGame::deck[46], //bot1's cards (9 H, 8 H)
                              CardGame::deck[21], CardGame::deck[20]}; //bot2's cards (9 D, 8 D)
        } // expected: threefold tie - all players choose the pair of aces and king kicker
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 3); // everyone wins because the kicker is on the table
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, SinglePairTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // A S, A H, 2 C, 3 C, 4 C
            this->gameDeck = {CardGame::deck[26], CardGame::deck[39], CardGame::deck[1], CardGame::deck[2], CardGame::deck[3],
                              CardGame::deck[34], CardGame::deck[33], //gambler1's cards (9 S, 8 S)
                              CardGame::deck[47], CardGame::deck[46], //bot1's cards (9 H, 8 H)
                              CardGame::deck[21], CardGame::deck[22]}; //bot2's cards (9 D, 10 D)
        } // expected: bot2 wins by 10 D kicker
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 1); // bot 2 wins by 10 D kicker
    ASSERT_EQ(texasHoldem->getLastGameWinners()[0], bot2);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}

TEST(TexasHoldemTest, HighCardDoubleTie) {
    class FakeTexasHoldem : public TexasHoldem {
    public:
        FakeTexasHoldem(const vector<Gambler *> &gamblers, int minimumEntry, const string &name="") :
                TexasHoldem(gamblers, minimumEntry, name) {};
    private:
        void shuffleCards() override { // A S, 5 C, 2 C, 3 C, 4 C
            this->gameDeck = {CardGame::deck[26], CardGame::deck[4], CardGame::deck[1], CardGame::deck[2], CardGame::deck[3],
                              CardGame::deck[34], CardGame::deck[33], //gambler1's cards (9 S, 8 S)
                              CardGame::deck[47], CardGame::deck[48], //bot1's cards (9 H, 10 H)
                              CardGame::deck[21], CardGame::deck[22]}; //bot2's cards (9 D, 10 D)
        } // expected: bot 1 and bot 2 tie with high card A S and their kicker 10s
    };
    auto *gambler1 = new Gambler(1337);
    auto *bot1 = new TexasBot(1338), *bot2 = new TexasBot(1339);
    vector<Gambler *> gamblers = {gambler1, bot1, bot2};
    auto *texasHoldem = new FakeTexasHoldem(gamblers, 1000);
    texasHoldem->advanceGame(30000); // game starts
    texasHoldem->advanceGame(30001); // bot1's small blind
    texasHoldem->advanceGame(30004); // bot2's big blind
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30007); // bot1's call to make all bets equal, flop should happen now
    texasHoldem->advanceGame(30010); // bot2 checks
    texasHoldem->raise(gambler1, 2); // gambler1 raises
    texasHoldem->advanceGame(30013); // bot1 calls
    texasHoldem->advanceGame(30016); // bot2 calls, turn starts
    texasHoldem->call(gambler1); // gambler1 checks
    texasHoldem->advanceGame(30016); // bot1 checks
    texasHoldem->advanceGame(30017); // bot2 raises by 2
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30019); // bot1 calls, river should start
    texasHoldem->advanceGame(30020); // bot 2 raises
    texasHoldem->call(gambler1); // gambler1 calls
    texasHoldem->advanceGame(30022); // bot 1 calls, the game should end
    ASSERT_EQ(texasHoldem->getGameState(), SHOWDOWN);
    ASSERT_FALSE(texasHoldem->isInProgress());
    ASSERT_EQ(texasHoldem->getLastGameWinners().size(), 2);
    ASSERT_TRUE(texasHoldem->getLastGameWinners()[0] == bot1 || texasHoldem->getLastGameWinners()[1] == bot1);
    ASSERT_TRUE(texasHoldem->getLastGameWinners()[0] == bot2 || texasHoldem->getLastGameWinners()[1] == bot2);
    delete gambler1;
    delete bot1;
    delete bot2;
    delete texasHoldem;
}