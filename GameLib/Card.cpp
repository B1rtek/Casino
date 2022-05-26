#include "Card.h"

/**
 * Creates a default card, Ace of Clubs
 */
Card::Card() noexcept {
    this->color = CardColor::NOCOLOR;
    this->value = CardValue::NOVALUE;
}

/**
 * Creates the specified card (from the french 52-card deck)
 * @param value value of the card
 * @param color color of the card
 */
Card::Card(CardValue value, CardColor color) noexcept: color(color), value(value) {}

CardValue Card::getValue() const noexcept {
    return this->value;
}

CardColor Card::getColor() const noexcept {
    return this->color;
}

/**
 * Compares cards using the poker scoring criteria
 */
bool Card::operator>(const Card &other) const noexcept {
    if (this->value > other.getValue()) {
        return true;
    } else if (this->value < other.getValue()) {
        return false;
    } else {
        return this->color > other.getColor();
    }
}

/**
 * Compares cards using the poker scoring criteria
 */
bool Card::operator<(const Card &other) const noexcept {
    if (this->value < other.getValue()) {
        return true;
    } else if (this->value > other.getValue()) {
        return false;
    } else {
        return this->color < other.getColor();
    }
}

/**
 * Cards are equal only if both their value and color is the same - colors have values as well
 */
bool Card::operator==(const Card &other) const noexcept {
    return this->value == other.getValue() && this->color == other.getColor();
}

std::ostream &operator<<(std::ostream &stream, Card card) {
    stream << Card::toString(card);
    return stream;
}

std::string Card::toString(Card card) noexcept {
    std::string representation;
    switch(card.value) {
        case NOVALUE: {
            representation += "[Hidden] ";
        }
            break;
        case JACK: {
            representation += "J ";
        }
            break;
        case QUEEN: {
            representation += "Q ";
        }
            break;
        case KING: {
            representation += "K ";
        }
            break;
        case ACE: {
            representation += "A ";
        }
            break;
        case N10: {
            representation += "10 ";
        }
            break;
        default: {
            representation += char(card.value+49);
            representation += ' ';
        }
    }
    switch (card.color) {
        case NOCOLOR: {
            representation += "[Hidden]";
        }
            break;
        case CLUBS: {
            representation += "Clubs";
        }
            break;
        case DIAMONDS: {
            representation += "Diamonds";
        }
            break;
        case SPADES: {
            representation += "Spades";
        }
            break;
        case HEARTS: {
            representation += "Hearts";
        }
            break;
    }
    return representation;
}