#include "card.hh"

#include <iostream>

Card::Card(enum Color color, int value)
{
    this->color = color;
    this->value = value;
}

int Card::getValue()
{
    return value;
}

enum Color Card::getColor()
{
    return color;
}

std::ostream& operator<<(std::ostream& os, const Card& c)
{
    os << c.value;

    switch (c.color)
    {
    case SPADE:
        os << "S";
        break;
    case DIAMOND:
        os << "D";
        break;
    case HEART:
        os << "H";
        break;
    case CLUB:
        os << "C";
        break;
    }

    os << " ";

    return os;
}
