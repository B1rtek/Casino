#ifndef CASINOGAME_CARDGAME_H
#define CASINOGAME_CARDGAME_H

#include "Game.h"
#include "Card.h"

/**
 * A deck of cards without colors, used to determine strength of a given hand in TexasHoldem
 */
const std::vector<Card *> uncoloredDeck = {
        new Card(), new Card(N2, NOCOLOR), new Card(N3, NOCOLOR), new Card(N4, NOCOLOR), new Card(N5, NOCOLOR),
        new Card(N6, NOCOLOR), new Card(N7, NOCOLOR), new Card(N8, NOCOLOR), new Card(N9, NOCOLOR),
        new Card(N10, NOCOLOR), new Card(JACK, NOCOLOR), new Card(QUEEN, NOCOLOR), new Card(KING, NOCOLOR),
        new Card(ACE, NOCOLOR)
};

/**
 * CardGame class, represents a game which is played with cards, subclass of Game
 */
class CardGame : public Game {
protected:
    // this instance's deck
    std::vector<Card *> gameDeck;
    std::map<Gambler *, std::vector<Card *>> gamblersCards;
public:
    const static std::vector<Card *> deck;
    const static std::vector<Card *> russianSchnapsenDeck;
    static Card *noneCard;

    explicit CardGame(int minimumEntry, std::vector<Card *> gameDeck = deck, const std::string &name = "") noexcept;

    CardGame(Gambler *gambler, int minimumEntry, std::vector<Card *> gameDeck = deck,
             const std::string &name = "") noexcept;

    CardGame(const std::vector<Gambler *> &gamblers, int minimumEntry, std::vector<Card *> gameDeck = deck,
             const std::string &name = "") noexcept;

    virtual void deal();

    bool addPlayer(Gambler *gambler) noexcept override;

    bool removePlayer(Gambler *gambler) noexcept override;

    std::vector<Card *> getDeck() const noexcept;

    virtual std::map<Gambler *, std::vector<Card *>> getGamblersCards() noexcept;
};


#endif //CASINOGAME_CARDGAME_H
