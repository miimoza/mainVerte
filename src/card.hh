#pragma once

#include <cstddef>
#include <iostream>

enum Color { SPADE, DIAMOND, HEART, CLUB };

class Card {
public:
  Card(enum Color color, int value);
  friend std::ostream &operator<<(std::ostream &os, const Card &c);

private:
  enum Color color;
  size_t value;
};
