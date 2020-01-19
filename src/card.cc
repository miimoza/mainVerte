#include "card.hh"

#include <iostream>

Card::Card(enum Color color, int value)
{
    this->color = color;
    this->value = value;
}

size_t Card::getValue()
{
    return value;
}

enum Color Card::getColor()
{
    return color;
}

int Card::getCardValue()
{
    switch (value)
    {
    case 0:
        return 1;
        break;
    case 1:
        return 2;
        break;
    case 2:
        return 3;
        break;
    case 3:
        return 4;
        break;
    case 4:
        return 5;
        break;
    case 5:
        return 6;
        break;
    case 6:
        return 7;
        break;
    case 7:
        return 8;
        break;
    case 8:
        return 9;
        break;
    case 9:
        return 10;
        break;
    case 10:
        if (color & (DIAMOND | HEART))
            return -1;
        return 11;
        break;
    case 11:
        return 11;
        break;
    case 12:
        return 11;
        break;
    }
    return value;
}

std::ostream& operator<<(std::ostream& os, const Card& c)
{
    switch (c.color)
    {
    case SPADE:
        os << "\033[30m";
        switch (c.value)
        {
        case 0:
            os << "🂡";
            break;
        case 1:
            os << "🂢";
            break;
        case 2:
            os << "🂣";
            break;
        case 3:
            os << "🂤";
            break;
        case 4:
            os << "🂥";
            break;
        case 5:
            os << "🂦";
            break;
        case 6:
            os << "🂧";
            break;
        case 7:
            os << "🂨";
            break;
        case 8:
            os << "🂩";
            break;
        case 9:
            os << "🂪";
            break;
        case 10:
            os << "🂫";
            break;
        case 11:
            os << "🂭";
            break;
        case 12:
            os << "🂮";
            break;
        }
        break;
    case DIAMOND:
        os << "\033[0;31m";

        switch (c.value)
        {
        case 0:
            os << "🃁";
            break;
        case 1:
            os << "🃂";
            break;
        case 2:
            os << "🃃";
            break;
        case 3:
            os << "🃄";
            break;
        case 4:
            os << "🃅";
            break;
        case 5:
            os << "🃆";
            break;
        case 6:
            os << "🃇";
            break;
        case 7:
            os << "🃈";
            break;
        case 8:
            os << "🃉";
            break;
        case 9:
            os << "🃊";
            break;
        case 10:
            os << "🃋";
            break;
        case 11:
            os << "🃍";
            break;
        case 12:
            os << "🃎";
            break;
        }
        break;
    case HEART:
        os << "\033[0;31m";
        switch (c.value)
        {
        case 0:
            os << "🂱";
            break;
        case 1:
            os << "🂲";
            break;
        case 2:
            os << "🂳";
            break;
        case 3:
            os << "🂴";
            break;
        case 4:
            os << "🂵";
            break;
        case 5:
            os << "🂶";
            break;
        case 6:
            os << "🂷";
            break;
        case 7:
            os << "🂸";
            break;
        case 8:
            os << "🂹";
            break;
        case 9:
            os << "🂺";
            break;
        case 10:
            os << "🂻";
            break;
        case 11:
            os << "🂽";
            break;
        case 12:
            os << "🂾";
            break;
        }
        break;
    case CLUB:
        os << "\033[30m";
        switch (c.value)
        {
        case 0:
            os << "🃑";
            break;
        case 1:
            os << "🃒";
            break;
        case 2:
            os << "🃓";
            break;
        case 3:
            os << "🃔";
            break;
        case 4:
            os << "🃕";
            break;
        case 5:
            os << "🃖";
            break;
        case 6:
            os << "🃗";
            break;
        case 7:
            os << "🃘";
            break;
        case 8:
            os << "🃙";
            break;
        case 9:
            os << "🃚";
            break;
        case 10:
            os << "🃛";
            break;
        case 11:
            os << "🃝";
            break;
        case 12:
            os << "🃞";
            break;
        }
        break;
    }

    os << "\033[1;37m";
    os << "\033[0m ";

    return os;
}
