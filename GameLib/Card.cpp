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
