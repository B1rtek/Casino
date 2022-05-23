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
    return this->value == other.getValue();
}

std::ostream &operator<<(std::ostream &stream, Card card) {
    switch(card.value) {
        case NOVALUE: {
            stream << "[Hidden] ";
        }
        break;
        case JACK: {
            stream << "J ";
        }
        break;
        case QUEEN: {
            stream << "Q ";
        }
        break;
        case KING: {
            stream << "K ";
        }
        break;
        case ACE: {
            stream << "A ";
        }
        break;
        default: {
            stream << char(card.value+49) << ' ';
        }
    }
    switch (card.color) {
        case NOCOLOR: {
            stream << "[Hidden]";
        }
        break;
        case CLUBS: {
            stream << "Clubs";
        }
        break;
        case DIAMONDS: {
            stream << "Diamonds";
        }
        break;
        case SPADES: {
            stream << "Spades";
        }
        break;
        case HEARTS: {
            stream << "Hearts";
        }
        break;
    }
    return stream;
}
