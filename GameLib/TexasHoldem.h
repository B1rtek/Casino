#ifndef PROI_4_KASYNO_GRA_TEXASHOLDEM_H
#define PROI_4_KASYNO_GRA_TEXASHOLDEM_H

#include "CardGame.h"

enum TexasHoldemState {
    SMALL_BLIND,
    BIG_BLIND,
    PREFLOP,
    FLOP,
    TURN,
    RIVER,
    SHOWDOWN
};

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

class TexasHoldem : public CardGame {
    std::vector<Card *> dealtCards;
    Gambler *current = nullptr, *dealer = nullptr;
    int dealerIndex = 0, currentPlayerIndex = 0, currentHighest = 0;
    TexasHoldemState state = SMALL_BLIND;
    std::map<Gambler *, bool> notFolded, movedDuringThisPhase;

    std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>> recognizeHandValue(Gambler *gambler);

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

    Gambler*decideHighCardTie(std::vector<std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands,
                              unsigned int maxHandIndex);

    Gambler *decideTwoPairTie(std::vector<std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands,
                              unsigned int maxHandIndex);

    Gambler *decideOnePairTie(std::vector<std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands,
                              unsigned int maxHandIndex);

protected:
    std::vector<Gambler *> chooseTheWinners() noexcept override;

public:
    explicit TexasHoldem(int minimumEntry, const std::string &name="");

    TexasHoldem(Gambler *gambler, int minimumEntry, const std::string &name="");

    TexasHoldem(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name="");

    void advanceGame(int millisecondsPassed) override;

    bool addPlayer(Gambler *gambler) noexcept override;

    bool removePlayer(Gambler *gambler) noexcept override;

    static std::pair<TexasHoldemHand, Card *> calculateHand(std::vector<Card *> hand);

    bool call(Gambler *gambler);

    bool fold(Gambler *gambler);

    bool raise(Gambler *gambler, int amount);

    Gambler* getCurrentPlayer() const noexcept;

    std::vector<Card*> getCurrentDealtCards() const noexcept;

    std::map<Gambler*, bool> getNotFolded() const noexcept;

    TexasHoldemState getGameState() const noexcept;

    std::map<Gambler *, std::vector<Card *>> getGamblersCards() noexcept override;
};


#endif //PROI_4_KASYNO_GRA_TEXASHOLDEM_H
