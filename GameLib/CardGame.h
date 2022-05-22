#ifndef CASINOGAME_CARDGAME_H
#define CASINOGAME_CARDGAME_H

#include "Game.h"
#include "Card.h"

/**
 * CardGame class, represents a game which is played with cards, subclass of Game
 */
class CardGame : public Game {
protected:
    // this instance's deck
    std::vector<Card *> gameDeck;
    std::map<Gambler *, std::vector<Card *>> gamblersCards;
public:
    // all cards
    const static std::vector<Card *> deck;
    // game specific decks
    const static std::vector<Card *> russianSchnapsenDeck;
    // none card
    static Card * noneCard;

    explicit CardGame(int minimumEntry, std::vector<Card *> gameDeck = deck, const std::string &name = "") noexcept;

    CardGame(Gambler *gambler, int minimumEntry, std::vector<Card *> gameDeck = deck,
             const std::string &name = "") noexcept;

    CardGame(const std::vector<Gambler *> &gamblers, int minimumEntry, std::vector<Card *> gameDeck = deck,
             const std::string &name = "") noexcept;

    virtual void deal();

    bool addPlayer(Gambler *gambler) noexcept override;

    bool removePlayer(Gambler *gambler) noexcept override;

    std::vector<Card *> getDeck() const noexcept;

    virtual std::map<Gambler*, std::vector<Card *>> getGamblersCards() noexcept;
};


#endif //CASINOGAME_CARDGAME_H
