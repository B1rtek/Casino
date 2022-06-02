#ifndef PROI_4_KASYNO_GRA_TEXASHOLDEM_H
#define PROI_4_KASYNO_GRA_TEXASHOLDEM_H

#include "CardGame.h"

/**
 * Enum representing the state of the Texas Holdem game
 */
enum TexasHoldemState {
    SMALL_BLIND,
    BIG_BLIND,
    PREFLOP,
    FLOP,
    TURN,
    RIVER,
    SHOWDOWN
};

/**
 * Enum representing the strength of a hand in Texas Holdem
 */
enum TexasHoldemHand {
    HIGH_CARD,
    ONE_PAIR,
    TWO_PAIRS,
    THREE_OF_A_KIND,
    STRAIGHT,
    FLUSH,
    FULL_HOUSE,
    FOUR_OF_A_KIND,
    STRAIGHT_FLUSH
};

/**
 * The TexasHoldem class, manages and represents a Texas Hold'em game
 */
class TexasHoldem : public CardGame {
    std::vector<Card *> dealtCards;
    Gambler *current = nullptr, *dealer = nullptr;
    int dealerIndex = 0, currentPlayerIndex = 0, currentHighest = 0;
    TexasHoldemState state = SMALL_BLIND;
    std::map<Gambler *, bool> notFolded, movedDuringThisPhase;
    std::vector<Card*> lastWinningHand;

    std::string texasHoldemStateStrings[7] = {
            "Small blind",
            "Big blind",
            "Preflop",
            "Flop",
            "Turn",
            "River",
            "Showdown"
    };

    std::string texasHoldemHandStrings[9] = {
            "High card",
            "One pair",
            "Two pairs",
            "Three of a kind",
            "Straight",
            "Flush",
            "Full house",
            "Four of a kind",
            "Straight flush"
    };

    void assignNewDealer();

    virtual void shuffleCards();

    void deal() override;

    bool smallBlind(Gambler *gambler);

    bool bigBlind(Gambler *gambler);

    void check(Gambler *gambler);

    Gambler *nextGambler();

    bool everyoneMoved();

    void advancePhase();

    bool onePlayerLeft();

    std::vector<Gambler *> decideKickers(std::map<Gambler *, std::vector<Card *>> mapForKickers);

    std::vector<Gambler *>
    decideHighCardTie(std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands);

    std::vector<Gambler *>
    decideOnePairTie(std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands);

    std::vector<Gambler *>
    decideTwoPairTie(std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands);

    std::vector<Gambler *>
    decideThreeOfAKindTie(
            std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands);

    std::vector<Gambler *>
    decideStraightTie(std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands);

    std::vector<Gambler *>
    decideFlushTie(std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands);

    std::vector<Gambler *>
    decideFullHouseTie(std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands);

    std::vector<Gambler *>
    decideFourOfAKindTie(std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands);

    std::vector<Gambler *>
    decideStraightFlushTie(
            std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands);

protected:
    std::vector<Gambler *> chooseTheWinners() noexcept override;

public:
    explicit TexasHoldem(int minimumEntry, const std::string &name="");

    TexasHoldem(Gambler *gambler, int minimumEntry, const std::string &name="");

    TexasHoldem(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name="");

    void startGame() noexcept override;

    void advanceGame(int millisecondsPassed) override;

    bool addPlayer(Gambler *gambler) noexcept override;

    bool removePlayer(Gambler *gambler) noexcept override;

    static std::pair<TexasHoldemHand, Card *> calculateHand(std::vector<Card *> hand);

    std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>> recognizeHandValue(Gambler *gambler);

    bool call(Gambler *gambler);

    bool fold(Gambler *gambler);

    bool raise(Gambler *gambler, int amount);

    Gambler* getCurrentPlayer() const noexcept;

    std::vector<Card*> getCurrentDealtCards() const noexcept;

    std::map<Gambler*, bool> getNotFolded() const noexcept;

    TexasHoldemState getGameState() const noexcept;

    std::string getGameStateString() const noexcept;

    std::map<Gambler *, std::vector<Card *>> getGamblersCards() noexcept override;

    std::vector<Card*> getLastWinningHand() const noexcept;

    std::string getLastWinningHandString() const noexcept;

    int getCurrentHighest() const noexcept;

    Gambler* getCurrentDealer() const noexcept;

    bool unjammingPerformed(Gambler *player) noexcept override;

protected:
    void removeBankruptPlayers() noexcept override;
};


#endif //PROI_4_KASYNO_GRA_TEXASHOLDEM_H
