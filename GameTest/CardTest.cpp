#include <gtest/gtest.h>

#include "Card.h"

using namespace std;

TEST(CardTest, CardCreate) {
    Card card = Card();
    ASSERT_EQ(card.getColor(), NOCOLOR);
    ASSERT_EQ(card.getValue(), NOVALUE);
}

TEST(CardTest, CardCreateWithValue) {
    Card card = Card(N2, HEARTS);
    ASSERT_EQ(card.getColor(), HEARTS);
    ASSERT_EQ(card.getValue(), N2);
}

TEST(CardTest, CardOperatorGreater) {
    Card card1 = Card(), card2 = Card(JACK, CLUBS), card3 = Card(JACK, SPADES);
    ASSERT_TRUE(card2 > card1);
    ASSERT_FALSE(card1 > card2);
    ASSERT_TRUE(card3 > card2);
    ASSERT_TRUE(card3 > card1);
    ASSERT_FALSE(card2 > card3);
    ASSERT_FALSE(card1 > card3);
}

TEST(CardTest, CardOperatorSmaller) {
    Card card1 = Card(), card2 = Card(JACK, CLUBS), card3 = Card(JACK, SPADES);
    ASSERT_FALSE(card2 < card1);
    ASSERT_TRUE(card1 < card2);
    ASSERT_FALSE(card3 < card2);
    ASSERT_FALSE(card3 < card1);
    ASSERT_TRUE(card2 < card3);
    ASSERT_TRUE(card1 < card3);
}

TEST(CardTest, CardOperatorEqualsEquals) {
    Card card1 = Card(), card2 = Card(N2, HEARTS), card3 = Card(N2, SPADES), card4 = Card(N2, SPADES);
    ASSERT_FALSE(card1 == card2);
    ASSERT_FALSE(card2 == card3);
    ASSERT_TRUE(card3 == card4);
}

TEST(CardTest, CardOperatorOstream) {
    Card card1 = Card(), card2 = Card(JACK, CLUBS), card3 = Card(N3, HEARTS);
    stringstream out, out2, out3;
    out << card1;
    ASSERT_EQ(out.str(), "[Hidden] [Hidden]");
    out2 << card2;
    ASSERT_EQ(out2.str(), "J Clubs");
    out3 << card3;
    ASSERT_EQ(out3.str(), "3 Hearts");
}
