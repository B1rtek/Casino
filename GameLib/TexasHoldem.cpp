#include "TexasHoldem.h"

#include <random>
#include <stdexcept>
#include <algorithm>

/**
 * Constructors based on the CardGame constructor, they force the minimumEntry value to be divisible by 1000 (blinds depend on it)
 */
TexasHoldem::TexasHoldem(int minimumEntry, const std::string &name) : CardGame(
        minimumEntry, CardGame::deck, name) {
    if (minimumEntry % 1000 != 0) {
        throw std::invalid_argument("minimumEntry must be divisible by 1000!");
    }
    this->maxPlayers = 10;
}

TexasHoldem::TexasHoldem(Gambler *gambler, int minimumEntry, const std::string &name) : CardGame(minimumEntry,
                                                                                                 CardGame::deck, name) {
    if (minimumEntry % 1000 != 0) {
        throw std::invalid_argument("minimumEntry must be divisible by 1000!");
    }
    this->maxPlayers = 10;
    if (gambler != nullptr) {
        gambler->joinGame(this);
    }
}

TexasHoldem::TexasHoldem(const std::vector<Gambler *> &gamblers, int minimumEntry, const std::string &name)
        : CardGame(minimumEntry, CardGame::deck, name) {
    if (minimumEntry % 1000 != 0) {
        throw std::invalid_argument("minimumEntry must be divisible by 1000!");
    }
    this->maxPlayers = 10;
    for (auto &gambler: gamblers) {
        if (gambler != nullptr) {
            gambler->joinGame(this);
        }
    }
}

/**
 * Recognizes the hand value for the gambler by selecting the most optimal hand
 * @param gambler gambler whose hand value will be calculated
 * @return maximum value calculated by calculateHand()
 */
std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>> TexasHoldem::recognizeHandValue(Gambler *gambler) {
    // initialize with the base set
    std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>> bestHand = {
            TexasHoldem::calculateHand(this->dealtCards), this->dealtCards};
    std::vector<Card *> tempCards;
    for (int i = 0; i < 5; i++) { // places one card at a time at every place and checks for patterns
        for (int j = 0; j < 2; j++) {
            tempCards = this->dealtCards;
            tempCards[i] = this->gamblersCards[gambler][j];
            std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>> tempHand = {
                    TexasHoldem::calculateHand(tempCards), tempCards};
            if (tempHand.first.first > bestHand.first.first ||
                (tempHand.first.first == bestHand.first.first && tempHand.first.second > bestHand.first.second)) {
                bestHand = tempHand;
            }
        }
    }
    for (int i = 0; i < 5; i++) { // places two cards at a time at every place and checks for patterns
        for (int j = 0; j < 5; j++) {
            if (i == j) continue;
            tempCards = this->dealtCards;
            tempCards[i] = this->gamblersCards[gambler][0];
            tempCards[j] = this->gamblersCards[gambler][1];
            std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>> tempHand = {
                    TexasHoldem::calculateHand(tempCards), tempCards};
            if (tempHand.first.first > bestHand.first.first ||
                (tempHand.first.first == bestHand.first.first && tempHand.first.second > bestHand.first.second)) {
                bestHand = tempHand;
            }
        }
    }
    return bestHand;
}

/**
 * Calculates value of the given 5 cards
 * @param hand hand to analyze
 * @return pair consisting of value type and highest card in the recognized hand to compare later
 */
std::pair<TexasHoldemHand, Card *> TexasHoldem::calculateHand(std::vector<Card *> hand) {
    // some data analysis
    int cardBuckets[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (auto &card: hand) {
        ++cardBuckets[card->getValue()];
    }
    CardColor firstColor = hand[0]->getColor();
    bool three = false, four = false, oneColor = std::all_of(++hand.begin(), hand.end(),
                                                             [&firstColor](Card *card) {
                                                                 return card->getColor() == firstColor;
                                                             });
    int pairsCount = 0, longestStreak = 0, currentStreak = 0;
    TexasHoldemHand bestHand = HIGH_CARD;
    Card *highCard = *max_element(hand.begin(), hand.end(), [](Card *a, Card *b) { return *a < *b; });
    for (int cardBucket: cardBuckets) {
        if (cardBucket == 1) {
            ++currentStreak;
            longestStreak = std::max(currentStreak, longestStreak);
        } else {
            currentStreak = 0;
            if (cardBucket == 2) ++pairsCount;
            if (cardBucket == 3) three = true;
            if (cardBucket == 4) four = true;
        }
        if (longestStreak == 5) {
            bestHand = STRAIGHT;
            break;
        }
    }
    // judging the hand according to the gathered data
    if (bestHand == STRAIGHT && oneColor) {
        return {STRAIGHT_FLUSH, highCard};
    } else if (four) {
        int i = 0;
        while (cardBuckets[hand[i]->getValue()] != 4) {
            ++i;
        }
        return {FOUR_OF_A_KIND, hand[i]};
    } else if (three && pairsCount == 1) {
        int i = 0;
        while (cardBuckets[hand[i]->getValue()] != 3) {
            ++i;
        }
        return {FULL_HOUSE, hand[i]};
    } else if (oneColor) {
        return {FLUSH, highCard};
    } else if (bestHand == STRAIGHT) {
        return {STRAIGHT, highCard};
    } else if (three) {
        int i = 0;
        while (cardBuckets[hand[i]->getValue()] != 3) {
            ++i;
        }
        return {THREE_OF_A_KIND, hand[i]};
    } else if (pairsCount == 2) {
        int i = 4;
        while (cardBuckets[hand[i]->getValue()] != 2) {
            --i;
        }
        return {TWO_PAIRS, hand[i]};
    } else if (pairsCount == 1) {
        int i = 0;
        while (cardBuckets[hand[i]->getValue()] != 2) {
            ++i;
        }
        return {ONE_PAIR, hand[i]};
    }
    return {HIGH_CARD, highCard};
}

/**
 * Decides the two pair hand ties by finding the kicker card
 * @param hands best hands of all gamblers
 * @return pointer to a gambler who had the best hand
 */
Gambler *
TexasHoldem::decideTwoPairTie(std::vector<std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands,
                              unsigned int maxHandIndex) {
    std::vector<unsigned> maxHands;
    for (unsigned i = 0; i < hands.size(); i++) {
        if (hands[i].first.first == TWO_PAIRS &&
            hands[i].first.second->getValue() == hands[maxHandIndex].first.second->getValue()) {
            maxHands.push_back(i);
        }
    }
    if (maxHands.size() == 1) {
        return this->gamblersPlaying[maxHandIndex];
    }
    // if this failed, compare values of the second pair
    // find values of the lower pair
    std::vector<CardValue> maxHandedLowerPairs;
    int pairBuckets[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    for (unsigned handIndexIndex = 0; handIndexIndex < maxHands.size(); handIndexIndex++) {
        std::vector<Card *> allHandCards = this->dealtCards;
        for (int i = 0; i < 2; i++)
            allHandCards.push_back(this->gamblersCards[this->gamblersPlaying[handIndexIndex]][i]);
        int cardBuckets[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (auto &card: allHandCards) {
            ++cardBuckets[card->getValue()];
        }
        // find lower pair
        int lowerPairIndex = 0;
        while (cardBuckets[lowerPairIndex] != 2) {
            ++lowerPairIndex;
        }
        ++pairBuckets[lowerPairIndex];

    }
    // if there's only one highest lower pair, we have a winner
    int highestLower = 13;
    while (pairBuckets[highestLower] == 0) {
        --highestLower;
    }
    if (pairBuckets[highestLower] == 1) { // we found them
        int winnerIndex = 0;
        while (maxHandedLowerPairs[winnerIndex] != highestLower) {
            ++winnerIndex;
        }
        return this->gamblersPlaying[maxHands[winnerIndex]];
    }
    // if this fails as well, find the high card
    std::vector<Card *> highCards;
    for (unsigned handIndexIndex = 0; handIndexIndex < maxHands.size(); handIndexIndex++) {
        std::vector<Card *> allHandCards = this->dealtCards;
        for (int i = 0; i < 2; i++)
            allHandCards.push_back(this->gamblersCards[this->gamblersPlaying[handIndexIndex]][i]);
        int cardBuckets[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (auto &card: allHandCards) {
            ++cardBuckets[card->getValue()];
        }
        std::sort(allHandCards.begin(), allHandCards.end());
        int highestIndex = 6;
        while (cardBuckets[allHandCards[highestIndex]->getValue()] == 2) {
            --highestIndex;
        }
        highCards.push_back(allHandCards[highestIndex]);
    }
    unsigned highestCardIndex = 0;
    for (unsigned i = 1; i < highCards.size(); i++) {
        if (*highCards[i] > *highCards[highestCardIndex]) {
            highestCardIndex = i;
        }
    }
    return this->gamblersPlaying[maxHands[highestCardIndex]];
}

/**
 * Decides the one pair hand ties by finding the kicker card
 * @param hands best hands of all gamblers
 * @return pointer to a gambler who had the best hand
 */
Gambler *
TexasHoldem::decideOnePairTie(std::vector<std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands,
                              unsigned int maxHandIndex) {
    std::vector<unsigned> maxHands;
    for (unsigned i = 0; i < hands.size(); i++) {
        if (hands[i].first.first == ONE_PAIR &&
            hands[i].first.second->getValue() == hands[maxHandIndex].first.second->getValue()) {
            maxHands.push_back(i);
        }
    }
    if (maxHands.size() == 1) {
        return this->gamblersPlaying[maxHandIndex];
    }
    // otherwise find highest cards that DON'T belong to the pair
    std::vector<Card *> highCards;
    for (unsigned handIndexIndex = 0; handIndexIndex < maxHands.size(); handIndexIndex++) {
        std::vector<Card *> allHandCards = this->dealtCards;
        for (int i = 0; i < 2; i++)
            allHandCards.push_back(this->gamblersCards[this->gamblersPlaying[handIndexIndex]][i]);
        int cardBuckets[14] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
        for (auto &card: allHandCards) {
            ++cardBuckets[card->getValue()];
        }
        std::sort(allHandCards.begin(), allHandCards.end());
        int highestIndex = 6;
        while (cardBuckets[allHandCards[highestIndex]->getValue()] == 2) {
            --highestIndex;
        }
        highCards.push_back(allHandCards[highestIndex]);
    }
    unsigned highestCardIndex = 0;
    for (unsigned i = 1; i < highCards.size(); i++) {
        if (*highCards[i] > *highCards[highestCardIndex]) {
            highestCardIndex = i;
        }
    }
    return this->gamblersPlaying[maxHands[highestCardIndex]];
}

/**
 * Chooses the winner by comparing hands
 * @return gambler who won
 */
Gambler *TexasHoldem::chooseTheWinner() noexcept {
    // check if all but one player gave up
    int stillInGame = 0;
    Gambler *potentialWinner = nullptr;
    for (auto gambler: this->notFolded) {
        if(gambler.second) {
            ++stillInGame;
            potentialWinner = gambler.first;
        }
    }
    if(stillInGame == 1) { // if there is only one person in game, they are the winner
        return potentialWinner;
    } // otherwise we check hands
    std::vector<std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands;
    for (auto &gambler: this->gamblersPlaying) {
        hands.push_back(this->recognizeHandValue(gambler));
    }
    unsigned maxHandIndex = 0;
    for (unsigned i = 1; i < this->gamblersPlaying.size(); i++) {
        if (hands[i].first.first > hands[maxHandIndex].first.first ||
            (hands[i].first.first == hands[maxHandIndex].first.first && hands[i].first.second > hands[maxHandIndex].first.second)) {
            maxHandIndex = i;
        }
    }
    if (hands[maxHandIndex].first.first == TWO_PAIRS) {
        return this->decideTwoPairTie(hands, maxHandIndex);
    } else if (hands[maxHandIndex].first.first == ONE_PAIR) {
        return this->decideOnePairTie(hands, maxHandIndex);
    }
    return this->gamblersPlaying[maxHandIndex];
}

void TexasHoldem::assignNewDealer() {
    if (unsigned(this->dealerIndex) >= this->gamblersPlaying.size()) { // players left
        this->dealerIndex = 0;
    } else if (this->dealer == this->gamblersPlaying[dealerIndex]) { // last dealer left
        ++this->dealerIndex;
    }
    this->dealer = this->gamblersPlaying[dealerIndex];
}

void TexasHoldem::shuffleCards() {
    std::shuffle(this->gameDeck.begin(), this->gameDeck.end(), std::mt19937(std::random_device()()));
}

void TexasHoldem::deal() {
    this->dealtCards.clear();
    int cardIndex = 0;
    while (cardIndex < 5) {
        this->dealtCards.push_back(this->gameDeck[cardIndex++]);
    }
    for (auto &gambler: this->gamblersPlaying) { // this loop will never fail because there can be only 10 players max
        this->gamblersCards[gambler].clear();
        for (int i = 0; i < 2; i++) this->gamblersCards[gambler].push_back(this->gameDeck[cardIndex++]);
    }
}

/**
 * Returns the next gambler to the left of the current one
 */
Gambler *TexasHoldem::nextGambler() {
    if (this->current == this->gamblersPlaying.back()) {
        this->currentPlayerIndex = 1;
        return this->gamblersPlaying.front();
    }
    return this->gamblersPlaying[this->currentPlayerIndex++];
}

/**
 * Advances the game
 * @param millisecondsPassed milliseconds passed since the start of the casino
 */
void TexasHoldem::advanceGame(int millisecondsPassed) {
    if (this->inProgress) {
        if (this->current->isBot()) this->current->makeAMove(millisecondsPassed);
        if (this->onePlayerLeft()) {
            this->state = SHOWDOWN;
        } else if (this->everyoneMoved()) {
            this->advancePhase();
        }
        if (this->state == SHOWDOWN) {
            this->inProgress = false;
            this->lastGameWinner = this->chooseTheWinner();
            this->payTheWinner(this->lastGameWinner);
            this->targetTime = millisecondsPassed + 30000;
        }
    } else {
        if (this->targetTime <= millisecondsPassed) {
            if (this->gamblersPlaying.size() >= 2) {
                this->startGame();
                // deal
                this->assignNewDealer();
                this->shuffleCards();
                this->deal();
                this->current = this->dealer;
                if (this->gamblersPlaying.size() != 2) {
                    this->currentPlayerIndex = 1;
                    this->current = this->nextGambler();
                }
                // no new target time is assigned, players can take their time to choose what they do
            } else { // game failed to start, waiting another 30 s
                this->targetTime = millisecondsPassed + 30000;
            }
        }
    }
}

/**
 * Bets the small blind
 * @param gambler gambler who's betting the small blind
 * @return true if it succeeded, false if it didn't (it always should)
 */
bool TexasHoldem::smallBlind(Gambler *gambler) {
    if (this->bet(gambler, this->minimumEntry / 1000)) {
        this->state = BIG_BLIND;
        this->currentHighest = std::max(this->currentHighest, this->currentBets[gambler]);
        return true;
    }
    return false;
}

/**
 * Bets the big blind
 * @param gambler gambler who's betting the big blind
 * @return true if it succeeded, false if it didn't (it always should)
 */
bool TexasHoldem::bigBlind(Gambler *gambler) {
    if (this->bet(gambler, this->minimumEntry / 500)) {
        this->state = PREFLOP;
        this->currentHighest = std::max(this->currentHighest, this->currentBets[gambler]);
        return true;
    }
    return false;
}

/**
 * Checks if all players have moved during this phase of the game
 */
bool TexasHoldem::everyoneMoved() {
    return std::all_of(this->movedDuringThisPhase.begin(), this->movedDuringThisPhase.end(),
                       [this](std::pair<Gambler *, bool> gamblerBoolPair) {
                           return gamblerBoolPair.second || !this->notFolded[gamblerBoolPair.first];
                       });
}

/**
 * Advances the game phase
 */
void TexasHoldem::advancePhase() {
    if (this->everyoneMoved()) {
        for (auto &gambler: this->gamblersPlaying) {
            this->movedDuringThisPhase[gambler] = false;
        }
        switch (this->state) {
            case PREFLOP: {
                this->state = FLOP;
            }
                break;
            case FLOP: {
                this->state = TURN;
            }
                break;
            case TURN: {
                this->state = RIVER;
            }
                break;
            case RIVER: {
                this->state = SHOWDOWN;
            }
                break;
            default:
                break;
        }
    }
}

/**
 * Checks if only one player has left
 */
bool TexasHoldem::onePlayerLeft() {
    bool oneLeft = false;
    for (auto &gamblerBoolPair: this->movedDuringThisPhase) {
        if (this->notFolded[gamblerBoolPair.first]) {
            if (oneLeft) return false;
            oneLeft = true;
        }
    }
    return true;
}


/**
 * Used to call, check and bet blinds
 * @param gambler gambler who is executing the call action
 * @return true if it succeeded, false if it didn't (it should always work)
 */
bool TexasHoldem::call(Gambler *gambler) {
    if (this->inProgress && this->current == gambler && this->notFolded[gambler]) {
        bool toReturn = true;
        switch (this->state) {
            case SMALL_BLIND: {
                toReturn = this->smallBlind(gambler);
            }
                break;
            case BIG_BLIND: {
                toReturn = this->bigBlind(gambler);
                this->movedDuringThisPhase[gambler] = true;
            }
                break;
            default: {
                if (this->currentHighest > this->currentBets[gambler] && this->inGameMoney[gambler] != 0) {
                    if (!this->bet(gambler, this->currentHighest - this->currentBets[gambler])) {
                        return false;
                    }
                } else {
                    this->check(gambler);
                }
                this->movedDuringThisPhase[gambler] = true;
            }
        }
        if (!toReturn) return false;
        this->current = this->nextGambler();
        return true;
    }
    return false;
}

/**
 * Called when call == check (will be used to call updates in the UI)
 * @param gambler gambler who's checking
 */
void TexasHoldem::check(Gambler *gambler) {}

/**
 * Folds player's card, effectively making them give up
 * @param gambler
 * @return
 */
bool TexasHoldem::fold(Gambler *gambler) {
    if (!this->notFolded[gambler]) return false;
    if (this->state < PREFLOP) return false; // you can't fold during blinds
    this->notFolded[gambler] = false;
    this->current = this->nextGambler();
    return true;
}

/**
 * Raises the highest bet, forcing other players to either call or fold
 * @param gambler
 * @param amount
 * @return
 */
bool TexasHoldem::raise(Gambler *gambler, int amount) {
    if (this->currentBets[gambler] + amount < this->currentHighest || !this->notFolded[gambler]) {
        return false;
    }
    if (this->state < PREFLOP) return false; // you can't raise during the blinds
    this->bet(gambler, amount);
    this->currentHighest = std::max(this->currentBets[gambler], this->currentHighest);
    this->current = this->nextGambler();
    for(auto &gamblerPlaying:this->gamblersPlaying) {
        this->movedDuringThisPhase[gamblerPlaying] = false;
    }
    this->movedDuringThisPhase[gambler] = true;
    return true;
}

/**
 * Overrides CardGame's removePlayer by removing gambler's entry from notFlopped map
 * @param gambler gambler added to the game
 * @return true if the addition was successful, false otherwise
 */
bool TexasHoldem::removePlayer(Gambler *gambler) noexcept {
    if (CardGame::removePlayer(gambler)) {
        this->notFolded.erase(this->notFolded.find(gambler));
        this->movedDuringThisPhase.erase(this->movedDuringThisPhase.find(gambler));
        return true;
    }
    return false;
}

Gambler *TexasHoldem::getCurrentPlayer() const noexcept {
    return this->current;
}

std::vector<Card *> TexasHoldem::getCurrentDealtCards() const noexcept {
    std::vector<Card *> currentCards = {CardGame::noneCard, CardGame::noneCard, CardGame::noneCard, CardGame::noneCard,
                                        CardGame::noneCard};
    if (this->state >= FLOP) {
        for (int i = 0; i < 3; i++) currentCards[i] = this->dealtCards[i];
    }
    if (this->state >= TURN) currentCards[3] = this->dealtCards[3];
    if (this->state >= RIVER) currentCards[4] = this->dealtCards[4];
    return currentCards;
}

std::map<Gambler *, std::vector<Card *>> TexasHoldem::getGamblersCards() noexcept {
    std::map<Gambler *, std::vector<Card *>> cards = CardGame::getGamblersCards();
    if(this->state < PREFLOP) {
        for(auto gambler:this->gamblersPlaying) {
            cards[gambler] = {CardGame::noneCard, CardGame::noneCard};
        }
        return cards;
    }
    return this->gamblersCards;
}

std::map<Gambler *, bool> TexasHoldem::getNotFolded() const noexcept {
    return this->notFolded;
}

bool TexasHoldem::addPlayer(Gambler *gambler) noexcept {
    if (this->gamblersPlaying.size() < this->maxPlayers && CardGame::addPlayer(gambler)) {
        this->notFolded[gambler] = true;
        this->movedDuringThisPhase[gambler] = false;
        return true;
    }
    return false;
}

TexasHoldemState TexasHoldem::getGameState() const noexcept {
    return this->state;
}