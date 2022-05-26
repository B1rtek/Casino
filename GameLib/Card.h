#ifndef PROI_4_KASYNO_GRA_CARD_H
#define PROI_4_KASYNO_GRA_CARD_H

#include <ostream>

enum CardColor {
    NOCOLOR,
    CLUBS,
    DIAMONDS,
    SPADES,
    HEARTS
};

enum CardValue {
    NOVALUE,
    N2,
    N3,
    N4,
    N5,
    N6,
    N7,
    N8,
    N9,
    N10,
    JACK,
    QUEEN,
    KING,
    ACE
};

/**
 * Card class, represents a playing card, used by all games inheriting from CardGame
 */
class Card {
    CardValue value;
    CardColor color;
public:
    Card() noexcept;

    Card(CardValue value, CardColor color) noexcept;

    CardValue getValue() const noexcept;

    CardColor getColor() const noexcept;

    bool operator>(const Card &other) const noexcept;

    bool operator<(const Card &other) const noexcept;

    bool operator==(const Card &other) const noexcept;

    friend std::ostream &operator<<(std::ostream &stream, Card card);

    static std::string toString(Card card) noexcept;
};


#endif //PROI_4_KASYNO_GRA_CARD_H
