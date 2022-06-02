#include "TexasHoldem.h"

#include <random>
#include <stdexcept>
#include <algorithm>
#include <utility>

/**
 * Constructors based on the CardGame constructor, they force the minimumEntry value to be divisible by 1000 (blinds depend on it)
 */
TexasHoldem::TexasHoldem(int minimumEntry, const std::string &name) : CardGame(
        minimumEntry, CardGame::deck, name) {
    if (minimumEntry % 1000 != 0) {
        throw std::invalid_argument("minimumEntry must be divisible by 1000!");
    }
    this->maxPlayers = 10;
    this->gameType = TEXAS_HOLDEM;
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
    this->gameType = TEXAS_HOLDEM;
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
    this->gameType = TEXAS_HOLDEM;
}

/**
 * Recognizes the hand value for the gambler by selecting the most optimal hand
 * @param gambler gambler whose hand value will be calculated
 * @return maximum value calculated by calculateHand()
 */
std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>> TexasHoldem::recognizeHandValue(Gambler *gambler) {
    std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>> bestHand;
    if (this->state == FLOP) {
        std::vector<Card *> onlyPossibleHand = this->getCurrentDealtCards();
        onlyPossibleHand[3] = this->getGamblersCards()[gambler][0];
        onlyPossibleHand[3] = this->getGamblersCards()[gambler][1];
        bestHand = {TexasHoldem::calculateHand(onlyPossibleHand), onlyPossibleHand};
    } else if (this->state == TURN) {
        bestHand = {{HIGH_CARD, CardGame::noneCard},
                    {}};
        std::vector<Card *> cards = this->getGamblersCards()[gambler], tempCards;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 4; j++) {
                tempCards = this->getCurrentDealtCards();
                tempCards[4] = cards[i];
                tempCards[j] = cards[1 - i];
                std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>> tempHand = {
                        TexasHoldem::calculateHand(tempCards), tempCards};
                if (tempHand.first.first > bestHand.first.first ||
                    (tempHand.first.first == bestHand.first.first && *tempHand.first.second > *bestHand.first.second)) {
                    bestHand = tempHand;
                }
            }
        }
    } else if (this->state == RIVER || this->state == SHOWDOWN) {
        // initialize with the base set
        bestHand = {TexasHoldem::calculateHand(this->dealtCards), this->dealtCards};
        std::vector<Card *> tempCards;
        for (int i = 0; i < 5; i++) { // places one card at a time at every place and checks for patterns
            for (int j = 0; j < 2; j++) {
                tempCards = this->dealtCards;
                tempCards[i] = this->gamblersCards[gambler][j];
                std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>> tempHand = {
                        TexasHoldem::calculateHand(tempCards), tempCards};
                if (tempHand.first.first > bestHand.first.first ||
                    (tempHand.first.first == bestHand.first.first && *tempHand.first.second > *bestHand.first.second)) {
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
                    (tempHand.first.first == bestHand.first.first && *tempHand.first.second > *bestHand.first.second)) {
                    bestHand = tempHand;
                }
            }
        }
    } else {
        return {{HIGH_CARD, CardGame::noneCard},
                {}};
    }
    if (bestHand.first.first != FLUSH && bestHand.first.first != STRAIGHT_FLUSH && bestHand.first.first != HIGH_CARD) {
        bestHand.first.second = uncoloredDeck[bestHand.first.second->getValue()]; // in the checked hands the color of the highest card matters
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
        if (card->getValue() != NOVALUE) {
            ++cardBuckets[card->getValue()];
        }
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
 * Chooses winners by selecting hands (or their parts) with the highest kickers
 * @param mapForKickers map with all potential winners' kickers
 * @return vector with gamblers who won
 */
std::vector<Gambler *> TexasHoldem::decideKickers(std::map<Gambler *, std::vector<Card *>> mapForKickers) {
    // find highest kicker for each player
    std::map<Gambler *, Card *> highestKickers;
    for (auto &gamblerKickersPair: mapForKickers) {
        highestKickers[gamblerKickersPair.first] = *std::max_element(gamblerKickersPair.second.begin(),
                                                                     gamblerKickersPair.second.end(),
                                                                     [](Card *one, Card *two) { return *one < *two; });
    }
    // find the highest kicker overall
    Card *maxKicker = CardGame::noneCard;
    for (auto &gamblerKickerPair: highestKickers) {
        if (*gamblerKickerPair.second > *maxKicker) maxKicker = gamblerKickerPair.second;
    }
    // gamblers with that kicker win - kickers are only compared by value!!!
    std::vector<Gambler *> winners;
    for (auto &gamblerKickerPair: highestKickers) {
        if (gamblerKickerPair.second->getValue() == maxKicker->getValue()) winners.push_back(gamblerKickerPair.first);
    }
    return winners;
}


/**
 * Decides a tie between two or more tied high card hands
 * @param hands hands to decide a tie between
 * @return vector with all winners
 */
std::vector<Gambler *> TexasHoldem::decideHighCardTie(
        std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands) {
    std::map<Gambler *, std::vector<Card *>> mapForKickers;
    std::vector<Card *> temp;
    for (auto &gamblerCardsPair: hands) {
        temp = this->dealtCards;
        for (auto &card: this->gamblersCards[gamblerCardsPair.first]) {
            temp.push_back(card);
        }
        // remove the card that is responsible for the hand
        temp.erase(std::remove(temp.begin(), temp.end(), hands[gamblerCardsPair.first].first.second), temp.end());
        // add the rest to the map for kickers
        mapForKickers[gamblerCardsPair.first] = temp;
    }
    std::vector<Gambler *> winners = decideKickers(mapForKickers);
    this->lastWinningHand = hands[winners[0]].second;
    return winners;
}

/**
 * Decides a tie between two or more tied one pair hands
 * @param hands hands to decide a tie between
 * @return vector with all winners
 */
std::vector<Gambler *> TexasHoldem::decideOnePairTie(
        std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands) {
    std::map<Gambler *, std::vector<Card *>> mapForKickers;
    std::vector<Card *> temp;
    for (auto &gamblerCardsPair: hands) {
        temp = this->dealtCards;
        for (auto &card: this->gamblersCards[gamblerCardsPair.first]) {
            temp.push_back(card);
        }
        // remove the cards that are responsible for the hand
        temp.erase(std::remove_if(temp.begin(), temp.end(), [&gamblerCardsPair](Card *card) {
            return card->getValue() == gamblerCardsPair.second.first.second->getValue();
        }), temp.end());
        // add the rest to the map for kickers
        mapForKickers[gamblerCardsPair.first] = temp;
    }
    std::vector<Gambler *> winners = decideKickers(mapForKickers);
    this->lastWinningHand = hands[winners[0]].second;
    return winners;
}

/**
 * Decides a tie between two or more tied two pair hands
 * @param hands hands to decide a tie between
 * @return vector with all winners
 */
std::vector<Gambler *> TexasHoldem::decideTwoPairTie(
        std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands) {
    std::map<Gambler *, std::vector<Card *>> mapForSecondPair;
    std::vector<Card *> temp;
    for (auto &gamblerCardsPair: hands) {
        temp = this->dealtCards;
        for (auto &card: this->gamblersCards[gamblerCardsPair.first]) {
            temp.push_back(card);
        }
        // remove the cards that are responsible for the hand
        temp.erase(std::remove_if(temp.begin(), temp.end(), [&gamblerCardsPair](Card *card) {
            return card->getValue() == gamblerCardsPair.second.first.second->getValue();
        }), temp.end());
        // add the rest to the map for kickers
        mapForSecondPair[gamblerCardsPair.first] = temp;
    }
    // calculate second pairs and find the highest
    std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> calculatedHands, hands2;
    Card *highestHandValue = CardGame::noneCard;
    for (auto &gamblerCardsPair: mapForSecondPair) {
        calculatedHands[gamblerCardsPair.first] = {TexasHoldem::calculateHand(gamblerCardsPair.second),
                                                   gamblerCardsPair.second};
        if (*calculatedHands[gamblerCardsPair.first].first.second > *highestHandValue)
            highestHandValue = calculatedHands[gamblerCardsPair.first].first.second;
    }
    // check how many gamblers still have the same hand
    for (auto &gamblerCardsPair: calculatedHands) {
        if (*gamblerCardsPair.second.first.second == *highestHandValue) {
            hands2[gamblerCardsPair.first] = gamblerCardsPair.second;
        }
    }
    // if only one gambler has the highest second pair, they are the winner
    if (hands2.size() == 1) {
        Gambler *winner = hands2.begin()->first;
        this->lastWinningHand = hands[winner].second;
        return {winner};
    }
    // otherwise we'll search for a kicker
    mapForSecondPair.clear();
    for (auto &gamblerCardsPair: hands2) {
        temp = gamblerCardsPair.second.second;
        // remove the cards that are responsible for the hand
        temp.erase(std::remove_if(temp.begin(), temp.end(), [&gamblerCardsPair](Card *card) {
            return card->getValue() == gamblerCardsPair.second.first.second->getValue();
        }), temp.end());
        // add the rest to the map for kickers
        mapForSecondPair[gamblerCardsPair.first] = temp;
    }
    std::vector<Gambler *> winners = decideKickers(mapForSecondPair);
    this->lastWinningHand = hands[winners[0]].second;
    return winners;
}

/**
 * Decides a tie between two or more three of a kind hands
 * @param hands hands to decide a tie between
 * @return vector with all winners
 */
std::vector<Gambler *> TexasHoldem::decideThreeOfAKindTie(
        std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands) {
    // this case is basically the same as in the single pair tie and can be solved in the exact same way
    return this->decideOnePairTie(std::move(hands));
}

/**
 * Decides a tie between two or more straight hands
 * @param hands hands to decide a tie between
 * @return vector with all winners
 */
std::vector<Gambler *> TexasHoldem::decideStraightTie(
        std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands) {
    // nothing can be done as kickers don't play in straight hands
    std::vector<Gambler *> winners;
    Gambler *gamblerPlaying;
    for (auto &gamblerCardsPair: hands) {
        gamblerPlaying = gamblerCardsPair.first;
        winners.push_back(gamblerCardsPair.first);
    }
    this->lastWinningHand = hands[gamblerPlaying].second;
    return winners;
}

/**
 * Decides a tie between two or more flush hands
 * @param hands hands to decide a tie between
 * @return vector with all winners
 */
std::vector<Gambler *> TexasHoldem::decideFlushTie(
        std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands) {
    // same situation as in the straight case, all cards play so there are no kickers
    return this->decideStraightTie(std::move(hands));
}

/**
 * Decides a tie between two or more full house hands
 * @param hands hands to decide a tie between
 * @return vector with all winners
 */
std::vector<Gambler *> TexasHoldem::decideFullHouseTie(
        std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands) {
    // case similar to double pair, first we remove cards that create three of a kind
    std::map<Gambler *, std::vector<Card *>> mapForSecondPair;
    std::vector<Card *> temp;
    for (auto &gamblerCardsPair: hands) {
        temp = this->dealtCards;
        for (auto &card: this->gamblersCards[gamblerCardsPair.first]) {
            temp.push_back(card);
        }
        // remove the cards that are responsible for the hand
        temp.erase(std::remove_if(temp.begin(), temp.end(), [&gamblerCardsPair](Card *card) {
            return card->getValue() == gamblerCardsPair.second.first.second->getValue();
        }), temp.end());
        // because temp now has 4 cards, we'll add a noneCard at the end to make it 5
        temp.push_back(CardGame::noneCard);
        // and add the result to the map for kickers
        mapForSecondPair[gamblerCardsPair.first] = temp;
    }
    // calculate second pairs and find the highest
    std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> calculatedHands, hands2;
    Card *highestHandValue = CardGame::noneCard;
    for (auto &gamblerCardsPair: mapForSecondPair) {
        calculatedHands[gamblerCardsPair.first] = {TexasHoldem::calculateHand(gamblerCardsPair.second),
                                                   gamblerCardsPair.second};
        if (*calculatedHands[gamblerCardsPair.first].first.second > *highestHandValue)
            highestHandValue = calculatedHands[gamblerCardsPair.first].first.second;
    }
    // everyone with the highest hand is a winner because there are no kickers in full house
    std::vector<Gambler *> winners;
    for (auto &gamblerCardsPair: calculatedHands) {
        if (*gamblerCardsPair.second.first.second == *highestHandValue) {
            winners.push_back(gamblerCardsPair.first);
        }
    }
    this->lastWinningHand = hands[winners[0]].second;
    return winners;
}

/**
 * Decides a tie between two or more four of a kind hands
 * @param hands hands to decide a tie between
 * @return vector with all winners
 */
std::vector<Gambler *> TexasHoldem::decideFourOfAKindTie(
        std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands) {
    // procedure is the same as with three of a kind or a single pair
    return this->decideOnePairTie(std::move(hands));
}

/**
 * Decides a tie between two or more straight flush hands
 * @param hands hands to decide a tie between
 * @return vector with all winners
 */
std::vector<Gambler *> TexasHoldem::decideStraightFlushTie(
        std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands) {
    // same situation as in the straight and flush case, all cards play so there are no kickers
    return this->decideStraightTie(std::move(hands));
}

/**
 * Chooses the winners by comparing hands
 * @return gamblers who won
 */
std::vector<Gambler *> TexasHoldem::chooseTheWinners() noexcept {
    // check if all but one player gave up
    int stillInGame = 0;
    Gambler *potentialWinner = nullptr;
    for (auto gambler: this->notFolded) {
        if (gambler.second) {
            ++stillInGame;
            potentialWinner = gambler.first;
        }
    }
    if (stillInGame == 1) { // if there is only one person in game, they are the winner
        return {potentialWinner};
    } // otherwise we check hands
    std::map<Gambler *, std::pair<std::pair<TexasHoldemHand, Card *>, std::vector<Card *>>> hands, maxHands;
    for (auto &gambler: this->gamblersPlaying) {
        if (this->notFolded[gambler]) {
            hands[gambler] = this->recognizeHandValue(gambler);
        }
    }
    // find the highest one
    Gambler *gamblerWithMaxHand = hands.begin()->first;
    for (auto &gamblerHandPair: hands) {
        if (hands[gamblerHandPair.first].first.first > hands[gamblerWithMaxHand].first.first ||
            (hands[gamblerHandPair.first].first.first == hands[gamblerWithMaxHand].first.first &&
             *hands[gamblerHandPair.first].first.second > *hands[gamblerWithMaxHand].first.second)) {
            gamblerWithMaxHand = gamblerHandPair.first;
        }
    }
    // check if there is more than 1 gambler with a hand of the same strength
    for (auto &gamblerHandPair: hands) {
        if (hands[gamblerHandPair.first].first.first == hands[gamblerWithMaxHand].first.first &&
            *hands[gamblerHandPair.first].first.second == *hands[gamblerWithMaxHand].first.second) {
            maxHands[gamblerHandPair.first] = hands[gamblerHandPair.first];
        }
    }
    // and if there is more than one, we need to decide the tie
    if (maxHands.size() > 1) {
        switch (hands[gamblerWithMaxHand].first.first) {
            case HIGH_CARD: {
                return this->decideHighCardTie(maxHands);
            }
            case ONE_PAIR: {
                return this->decideOnePairTie(maxHands);
            }
            case TWO_PAIRS: {
                return this->decideTwoPairTie(maxHands);
            }
            case THREE_OF_A_KIND: {
                return this->decideThreeOfAKindTie(maxHands);
            }
            case STRAIGHT: {
                return this->decideStraightTie(maxHands);
            }
            case FLUSH: {
                return this->decideFlushTie(maxHands);
            }
            case FULL_HOUSE: {
                return this->decideFullHouseTie(maxHands);
            }
            case FOUR_OF_A_KIND: {
                return this->decideFourOfAKindTie(maxHands);
            }
            case STRAIGHT_FLUSH: {
                return this->decideStraightFlushTie(maxHands);
            }
        }
    } // otherwise the winner is clear
    this->lastWinningHand = hands[gamblerWithMaxHand].second;
    return {gamblerWithMaxHand};
}

void TexasHoldem::assignNewDealer() {
    if (unsigned(this->dealerIndex) >= this->gamblersPlaying.size()) { // players left
        this->dealerIndex = 0;
    } else if (this->dealer == this->gamblersPlaying[dealerIndex]) { // last dealer left
        ++this->dealerIndex;
    }
    if (unsigned(this->dealerIndex) >= this->gamblersPlaying.size()) { // can be out of range here
        this->dealerIndex = 0;
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
 * Returns the next playing gambler to the left of the current one
 */
Gambler *TexasHoldem::nextGambler() {
    Gambler *next = this->current;
    do {
        if (next == this->gamblersPlaying.back()) {
            this->currentPlayerIndex = 1;
            next = this->gamblersPlaying.front();
        } else {
            if (this->currentPlayerIndex >= this->gamblersPlaying.size()) this->currentPlayerIndex = 0;
            next = this->gamblersPlaying[this->currentPlayerIndex++];
        }
    } while (!this->notFolded[next]);
    return next;
}

void TexasHoldem::startGame() noexcept {
    Game::startGame();
    for (auto &gambler: this->gamblersPlaying) {
        this->notFolded[gambler] = true;
    }
    this->state = SMALL_BLIND;
    this->lastWinningHand.clear();
    this->currentHighest = 0;
}

/**
 * Advances the game
 * @param millisecondsPassed milliseconds passed since the start of the casino
 */
void TexasHoldem::advanceGame(int millisecondsPassed) {
    Game::advanceGame(millisecondsPassed);
    if (this->inProgress) {
        if (this->current->isBot()) this->current->makeAMove(millisecondsPassed);
        if (this->onePlayerLeft()) {
            this->state = SHOWDOWN;
        } else if (this->everyoneMoved()) {
            this->advancePhase();
        }
        if (this->state == SHOWDOWN) {
            this->inProgress = false;
            this->lastGameWinners = this->chooseTheWinners();
            this->payTheWinners(this->lastGameWinners);
            this->removeBankruptPlayers();
            this->targetTime = millisecondsPassed + 10000;
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
                this->currentPlayerIndex = 1;
                if (this->gamblersPlaying.size() != 2) {
                    this->currentPlayerIndex = this->dealerIndex + 1;
                    this->current = this->nextGambler();
                }
                // no new target time is assigned, players can take their time to choose what they do
            } else { // game failed to start, waiting another 10 s
                this->targetTime = millisecondsPassed + 10000;
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
                    int amount = this->currentHighest - this->currentBets[gambler];
                    amount = std::min(amount, this->inGameMoney[gambler]);
                    if (!this->bet(gambler, amount)) {
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
        this->lastMoveMillis = this->lastMillis;
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
    if (!this->notFolded[gambler] || this->state < PREFLOP || this->current != gambler)
        return false; // you can't fold during blinds
    this->notFolded[gambler] = false;
    this->current = this->nextGambler();
    this->lastMoveMillis = this->lastMillis;
    return true;
}

/**
 * Raises the highest bet, forcing other players to either call or fold
 * @param gambler
 * @param amount
 * @return
 */
bool TexasHoldem::raise(Gambler *gambler, int amount) {
    if (this->currentBets[gambler] + amount <= this->currentHighest || !this->notFolded[gambler] ||
        this->current != gambler) {
        return false;
    }
    if (this->state < PREFLOP) return false; // you can't raise during the blinds
    this->bet(gambler, amount);
    this->currentHighest = std::max(this->currentBets[gambler], this->currentHighest);
    this->current = this->nextGambler();
    for (auto &gamblerPlaying: this->gamblersPlaying) {
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
    if (this->state < PREFLOP) {
        for (auto gambler: this->gamblersPlaying) {
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
        this->gamblersCards[gambler].push_back(CardGame::noneCard);
        this->gamblersCards[gambler].push_back(CardGame::noneCard);
        return true;
    }
    return false;
}

TexasHoldemState TexasHoldem::getGameState() const noexcept {
    return this->state;
}

std::vector<Card *> TexasHoldem::getLastWinningHand() const noexcept {
    return this->lastWinningHand;
}

std::string TexasHoldem::getGameStateString() const noexcept {
    return this->texasHoldemStateStrings[this->state];
}

std::string TexasHoldem::getLastWinningHandString() const noexcept {
    if (this->lastWinningHand.size() == 5) {
        return this->texasHoldemHandStrings[TexasHoldem::calculateHand(this->lastWinningHand).first];
    }
    return "other players folding";
}

int TexasHoldem::getCurrentHighest() const noexcept {
    return this->currentHighest;
}

Gambler *TexasHoldem::getCurrentDealer() const noexcept {
    return this->dealer;
}

bool TexasHoldem::unjammingPerformed(Gambler *player) noexcept {
    if (this->current == player) return false;
    return Game::unjammingPerformed(player);
}

void TexasHoldem::removeBankruptPlayers() noexcept {
    for (auto &gambler: this->gamblersPlaying) {
        if (this->inGameMoney[gambler] < this->minimumEntry / 500) {
            gambler->leaveGame();
            gambler->spectate(this);
        }
    }
}
