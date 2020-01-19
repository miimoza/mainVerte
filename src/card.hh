#pragma once

#include <cstddef>
#include <iostream>

enum Color
{
    SPADE = 1,
    DIAMOND = 2,
    HEART = 4,
    CLUB = 8
};

class Card
{
public:
    Card(enum Color color, int value);
    friend std::ostream& operator<<(std::ostream& os, const Card& c);

    size_t getValue();
    enum Color getColor();

    int getCardValue();

    bool operator<(const Card& other) const
    {
        return value < other.value;
    }

private:
    enum Color color;
    size_t value;
};
