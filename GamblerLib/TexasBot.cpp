#include "TexasBot.h"

TexasBot::TexasBot(const std::string &name) : GamblerBot(name) {
    this->gamblerType = TEXAS_BOT;
}

TexasBot::TexasBot(int balance, const std::string &name) : GamblerBot(balance, name) {
    this->gamblerType = TEXAS_BOT;
}

TexasBot::TexasBot(int balance, Game *game, const std::string &name) : GamblerBot(balance, game, name) {
    this->gamblerType = TEXAS_BOT;
}

void TexasBot::makeAMove(int millisecondsPassed) noexcept {
    if (this->gamePlayed != nullptr) {
        if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentPlayer() != this) return;
        if (!this->moveScheduled) {
            this->targetTime = millisecondsPassed + 300;
            this->moveScheduled = true;
        } else if (this->targetTime <= millisecondsPassed) {
            if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getGameState() < PREFLOP) {
                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
            } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getGameState() == PREFLOP) {
                std::vector<Card *> bot_cards = dynamic_cast<TexasHoldem *>(this->gamePlayed)->getGamblersCards()[this];
                if (bot_cards[0] == bot_cards[1]) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // raise between 15% to 25% of balance if pair in hand
                        int amount = int(
                                ((double(rand() % 11) + 15.0) / 100.0) * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                        if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else {
                        if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() * 2 <=
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) {
                            if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                                double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.15) {
                                // 50% chance of reraising to 20% of balance if bet is below 10% of balance if pair in hand
                                if (rand() % 10 <= 4) {
                                    int amount = int(double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.2);
                                    if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                    }
                                } else {
                                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                }
                            } else {
                                // calls any bet between 10% and 50% of balance if pair in hand
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else if (bot_cards[0]->getValue() >= N10) {
                            // if pair is above 9, 10% chance of calling any bet above 50% balance
                            if (rand() % 10 == 0) dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            else dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        } else {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this); // if pair below 10, fold when bet above 50% balance
                        }
                    }
                } else if (bot_cards[0]->getValue() >= N10 || bot_cards[1]->getValue() >= N10) {
                    if (abs(bot_cards[0]->getValue() - bot_cards[1]->getValue()) == 1) {
                        if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                            // raise between 5% to 10% of balance if straight high cards
                            int amount = int(
                                    (double(rand() % 6) + 5.0) / 100.0 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                            if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                                   double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.3) {
                            // calls any bet below 30% of balance if straight high cards
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else {
                            // folds if bet above 30%
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        }
                    } else {
                        if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                            // just check if simple high card
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                                   double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.2) {
                            // calls any bet below 20% of balance if simple high card
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else {
                            // folds if bet above 20%
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        }
                    }
                } else {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // just check if any random cards below 10's
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                    } else {
                        if (abs(bot_cards[0]->getValue() - bot_cards[1]->getValue()) == 1) {
                            if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                                double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.25) {
                                // calls any bet below 25% of balance if straight cards below 10's
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            } else {
                                // folds if bet is above 25% of balance if straight cards below 10's
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                            }
                        } else {
                            if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                                double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.1) {
                                // calls any bet below 10% of balance if random cards below 10's
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            } else {
                                // folds if bet is above 10% of balance if random cards below 10's
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                            }
                        }
                    }
                }
            } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getGameState() == FLOP) {
                if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first >= STRAIGHT) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // raise from 20% to 30% of balance if hand better equal straight
                        int amount = int((double(rand() % 11) + 20.0) / 100.0 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                        if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else {
                        if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                            double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.15) {
                            // 50% chance of reraising to 30% of balance if bet is below 15% of balance if hand better equal straight
                            if (rand() % 10 <= 4) {
                                int amount = int(0.3 * double(this->gamePlayed->getInGameMoney()[this]));
                                if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                }
                            } else {
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else {
                            // calls any bet above 15% of balance if hand better equal straight
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           THREE_OF_A_KIND) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // raise from 30% to 40% of balance if hand is three of a kind
                        int amount = int((double(rand() % 11) + 30.0) / 100.0 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                        if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.6) {
                        if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                            double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.15) {
                            // 50% chance of reraising to 30% of balance if bet is below 15% of balance if hand is three of a kind
                            if (rand() % 10 <= 4) {
                                int amount = int(0.3 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                                if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                }
                            } else {
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else {
                            // calls any bet between 15% and 60% of balance if hand is three of a kind
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else {
                        // 40% of chance of calling any bet above 60% of balance if hand is three of a kind
                        if (rand() % 10 <= 3) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        }
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           TWO_PAIRS) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // raise from 20% to 30% of balance if hand is two pairs
                        int amount = int((double(rand() % 11) + 20.0) / 100.0 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                        if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.4) {
                        if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                            double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.1) {
                            // 50% chance of reraising to 20% of balance if bet is below 10% of balance if hand is two pairs
                            if (rand() % 10 <= 4) {
                                int amount = int(0.2 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                                if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                }
                            } else {
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else {
                            // calls any bet between 10% and 40% of balance if hand is two pairs
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else {
                        // 20% of chance of calling any bet above 40% of balance if hand is two pairs
                        if (rand() % 10 <= 1) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        }
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           ONE_PAIR) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // raise from 10% to 15% of balance if hand is one pair
                        int amount = int((double(rand() % 6) + 10.0) / 100.0 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                        if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.15) {
                        if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                            double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.05) {
                            // 50% chance of reraising to 10% of balance if bet is below 5% of balance if hand is one pair
                            if (rand() % 10 <= 4) {
                                int amount = int(0.1 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                                if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                }
                            } else {
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else {
                            // calls any bet between 5% and 15% of balance if hand is one pair
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else {
                        // 10% of chance of calling any bet above 15% of balance if hand is one pair
                        if (rand() % 10 == 0) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        }
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           HIGH_CARD) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // just checks if high card
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.05) {
                        // calls any bet below 5% of balance
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                    } else {
                        // fold if bet is above 5% of balance
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                    }
                }
            } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getGameState() == TURN) {
                if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first >= STRAIGHT) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // raise from 15% to 20% of balance if hand better equal straight
                        int amount = int((double(rand() % 6) + 15.0) / 100.0 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                        if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else {
                        if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                            double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.1) {
                            // 50% chance of reraising to 20% of balance if bet is below 10% of balance if hand better equal straight
                            if (rand() % 10 <= 4) {
                                int amount = int(0.2 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                                if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                }
                            } else {
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else {
                            // calls any bet above 15% of balance if hand better equal straight
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           THREE_OF_A_KIND) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // raise from 30% to 40% of balance if hand is three of a kind
                        int amount = int((double(rand() % 11) + 30.0) / 100.0 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                        if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.6) {
                        if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                            double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.15) {
                            // 50% chance of reraising to 30% of balance if bet is below 15% of balance if hand is three of a kind
                            if (rand() % 10 <= 4) {
                                int amount = int(0.3 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                                if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                }
                            } else {
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else {
                            // calls any bet between 15% and 60% of balance if hand is three of a kind
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else {
                        // 40% of chance of calling any bet above 60% of balance if hand is three of a kind
                        if (rand() % 10 <= 3) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        }
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           TWO_PAIRS) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // raise from 20% to 30% of balance if hand is two pairs
                        int amount = int((double(rand() % 11) + 20.0) / 100.0 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                        if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.4) {
                        if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                            double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.1) {
                            // 50% chance of reraising to 20% of balance if bet is below 10% of balance if hand is two pairs
                            if (rand() % 10 <= 4) {
                                int amount = int(0.2 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                                if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                }
                            } else {
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else {
                            // calls any bet between 10% and 40% of balance if hand is two pairs
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else {
                        // 20% of chance of calling any bet above 40% of balance if hand is two pairs
                        if (rand() % 10 <= 1) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        }
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           ONE_PAIR) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // raise from 10% to 15% of balance if hand is one pair
                        int amount = int((double(rand() % 6) + 10.0) / 100.0 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                        if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.15) {
                        if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                            double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.05) {
                            // 50% chance of reraising to 10% of balance if bet is below 5% of balance if hand is one pair
                            if (rand() % 10 <= 4) {
                                int amount = int(0.1 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                                if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                }
                            } else {
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else {
                            // calls any bet between 5% and 15% of balance if hand is one pair
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else {
                        // 10% of chance of calling any bet above 15% of balance if hand is one pair
                        if (rand() % 10 == 0) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        }
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           HIGH_CARD) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // just checks if high card
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.05) {
                        // calls any bet below 5% of balance
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                    } else {
                        // fold if bet is above 5% of balance
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                    }
                }
            } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getGameState() == RIVER) {
                if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first >= STRAIGHT) {
                    // call all in if hand is better equal straight
                    int amount = dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this];
                    if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           THREE_OF_A_KIND) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // raise from 30% to 40% of balance if hand is three of a kind]
                        int amount = int((double(rand() % 11) + 30.0) / 100.0 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                        if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.6) {
                        if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                            double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.15) {
                            // 50% chance of reraising to 30% of balance if bet is below 15% of balance if hand is three of a kind
                            if (rand() % 10 <= 4) {
                                int amount = int(0.3 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                                if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                }
                            } else {
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else {
                            // calls any bet between 15% and 60% of balance if hand is three of a kind
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else {
                        // 70% of chance of calling any bet above 60% of balance if hand is three of a kind
                        if (rand() % 10 <= 6) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        }
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           TWO_PAIRS) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // raise from 20% to 25% of balance if hand is two pairs
                        int amount = int((double(rand() % 6) + 20.0) / 100.0 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                        if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.3) {
                        if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                            double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.1) {
                            // 50% chance of reraising to 20% of balance if bet is below 10% of balance if hand is two pairs
                            if (rand() % 10 <= 4) {
                                int amount = int(0.2 * double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]));
                                if (!dynamic_cast<TexasHoldem *>(this->gamePlayed)->raise(this, amount)) {
                                    dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                                }
                            } else {
                                dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                            }
                        } else {
                            // calls any bet between 10% and 30% of balance if hand is two pairs
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        }
                    } else {
                        // 20% of chance of calling any bet above 30% of balance if hand is two pairs
                        if (rand() % 10 <= 1) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        }
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           ONE_PAIR) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // just checks if hand is one pair
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.1) {
                        // calls any bet below 10% of balance if hand is one pair
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                    } else {
                        // 5% of chance of calling any bet above 10% of balance if hand is one pair
                        if (rand() % 20 == 0) {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                        } else {
                            dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                        }
                    }
                } else if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->recognizeHandValue(this).first.first ==
                           HIGH_CARD) {
                    if (dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest() ==
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentBets()[this]) {
                        // just checks if high card
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                    } else if (double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getCurrentHighest()) <=
                               double(dynamic_cast<TexasHoldem *>(this->gamePlayed)->getInGameMoney()[this]) * 0.05) {
                        // calls any bet below 5% of balance
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->call(this);
                    } else {
                        // fold if bet is above 5% of balance
                        dynamic_cast<TexasHoldem *>(this->gamePlayed)->fold(this);
                    }
                }
            }
            this->moveScheduled = false;
        }
    }
}
