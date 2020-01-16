#include <iostream>

#include "card.hh"

Card::Card(enum Color color, int value) {
  this->color = color;
  this->value = value;
}

std::ostream &operator<<(std::ostream &os, const Card &c) {
  os << c.value;

  switch (c.color) {
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
