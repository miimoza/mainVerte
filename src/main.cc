#include <iostream>

#include "card.hh"
#include "deck.hh"
#include "game.hh"

int main() {
  Game game(4);
  Deck d = Deck();
  std::cout << d;
  std::cout << "============ SHAKE DECK ==========\n";
  d.shakeDeck();
  std::cout << d;

  std::cout << "========== PICK LAST CARD =======\n";
  std::cout << "Last Card Popped: " << d.pickToDeck() << "\n";
  std::cout << d;
  std::cout << "========== ADD ONE CARD =========\n";
  d.addToDeck(Card(SPADE, 5));
  std::cout << d;

  std::vector<cards_t> m = d.getAllMoves();
  std::cout << m[0];
}
