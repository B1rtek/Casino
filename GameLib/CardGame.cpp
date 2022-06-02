#include "CardGame.h"

#include <utility>

/**
 * Defines the 52-card french deck used in many games, including the implemented TexasHoldem class
 */
const std::vector<Card *> CardGame::deck = {
        new Card(ACE, CLUBS), new Card(N2, CLUBS), new Card(N3, CLUBS), new Card(N4, CLUBS), new Card(N5, CLUBS),
        new Card(N6, CLUBS), new Card(N7, CLUBS), new Card(N8, CLUBS), new Card(N9, CLUBS), new Card(N10, CLUBS),
        new Card(JACK, CLUBS), new Card(QUEEN, CLUBS), new Card(KING, CLUBS),
        new Card(ACE, DIAMONDS), new Card(N2, DIAMONDS), new Card(N3, DIAMONDS), new Card(N4, DIAMONDS),
        new Card(N5, DIAMONDS),
        new Card(N6, DIAMONDS), new Card(N7, DIAMONDS), new Card(N8, DIAMONDS), new Card(N9, DIAMONDS),
        new Card(N10, DIAMONDS),
        new Card(JACK, DIAMONDS), new Card(QUEEN, DIAMONDS), new Card(KING, DIAMONDS),
        new Card(ACE, SPADES), new Card(N2, SPADES), new Card(N3, SPADES), new Card(N4, SPADES), new Card(N5, SPADES),
        new Card(N6, SPADES), new Card(N7, SPADES), new Card(N8, SPADES), new Card(N9, SPADES), new Card(N10, SPADES),
        new Card(JACK, SPADES), new Card(QUEEN, SPADES), new Card(KING, SPADES),
        new Card(ACE, HEARTS), new Card(N2, HEARTS), new Card(N3, HEARTS), new Card(N4, HEARTS), new Card(N5, HEARTS),
        new Card(N6, HEARTS), new Card(N7, HEARTS), new Card(N8, HEARTS), new Card(N9, HEARTS), new Card(N10, HEARTS),
        new Card(JACK, HEARTS), new Card(QUEEN, HEARTS), new Card(KING, HEARTS)
};

/**
 * A subset of the french deck with all cards needed to play Russian Schnapsen
 */
const std::vector<Card *> CardGame::russianSchnapsenDeck = {
        deck[0], deck[8], deck[9], deck[10], deck[11], deck[12],
        deck[13], deck[21], deck[22], deck[23], deck[24], deck[25],
        deck[26], deck[34], deck[35], deck[36], deck[37], deck[38],
        deck[39], deck[47], deck[48], deck[49], deck[50], deck[51],
};

/**
 * Not-a-card, used in the TexasHoldem to indicate that a card does not exist or is currently not visible to the player
 */
Card* CardGame::noneCard = new Card(NOVALUE, NOCOLOR);

/**
 * Creates an empty CardGame
 * @param gameDeck deck of cards used in this game
 * @param minimumEntry minimum balance needed to enter the game
 * @param name name of the game
 */
CardGame::CardGame(int minimumEntry, std::vector<Card *> gameDeck, const std::string &name) noexcept:
        Game(minimumEntry, name), gameDeck(std::move(gameDeck)) {}

/**
 * Creates a CardGame with a gambler in it (or not if the provided gambler can't join the game)
 * @param gameDeck deck of cards used in this game
 * @param gambler gambler that will instantly join this game
 * @param minimumEntry minimum balance needed to enter the game
 * @param name name of the game
 */
CardGame::CardGame(Gambler *gambler, int minimumEntry, std::vector<Card *> gameDeck, const std::string &name) noexcept
        : Game(gambler, minimumEntry, name), gameDeck(std::move(gameDeck)) {}

/**
 * Creates a CardGame with gamblers in it (or some of them if a gambler from the list can't join the game)
 * @param gameDeck deck of cards used in this game
 * @param gamblers list of gamblers who will instantly join this game
 * @param minimumEntry minimum balance needed to enter the game
 * @param name name of the game
 */
CardGame::CardGame(const std::vector<Gambler *> &gamblers, int minimumEntry, std::vector<Card *> gameDeck,
                   const std::string &name) noexcept: Game(gamblers, minimumEntry, name),
                                                      gameDeck(std::move(gameDeck)) {}

/**
* Deals cards for the players, method to override by the subclasses
*/
void CardGame::deal() {}

std::vector<Card *> CardGame::getDeck() const noexcept {
    return this->gameDeck;
}

std::map<Gambler *, std::vector<Card *>> CardGame::getGamblersCards() noexcept {
    return this->gamblersCards;
}

/**
 * Overrides the default addPlayer by initializing gambler's cards vector
 * @param gambler gambler added to the game
 * @return true if the addition was successful, false otherwise
 */
bool CardGame::addPlayer(Gambler *gambler) noexcept {
    if(Game::addPlayer(gambler)) {
        this->gamblersCards[gambler] = std::vector<Card*>();
        return true;
    }
    return false;
}

/**
 * Overrides the default removePlayer by removing gambler's cards vector
 * @param gambler gambler removed from the game
 * @return true if the removal was successful, false otherwise
 */

bool CardGame::removePlayer(Gambler *gambler) noexcept {
    if(Game::removePlayer(gambler)) {
        this->gamblersCards.erase(this->gamblersCards.find(gambler));
        return true;
    }
    return false;
}

