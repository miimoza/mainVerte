#pragma once

#include "card.hh"
#include <iostream>
#include <memory>
#include <vector>

using cards_t = std::shared_ptr<std::vector<Card>>;

class Deck {
public:
  Deck();
  friend std::ostream &operator<<(std::ostream &os, const Deck &d);
  void brandNewDeck();
  void shakeDeck();
  Card pickToDeck();
  void addToDeck(Card c);
  std::vector<cards_t> getAllMoves();

private:
  cards_t cards;
};
