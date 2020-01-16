#include <iostream>

#include "deck.hh"

Deck::Deck() {
  cards = std::make_shared<std::vector<Card>>();
  brandNewDeck();
}

std::ostream &operator<<(std::ostream &os, const Deck &d) {
  os << "[";
  for (Card c : *d.cards)
    os << c;
  os << "]\n";

  return os;
}

void Deck::brandNewDeck() {
  // RESET VECTOR MEMORY
  std::vector<Card>().swap(*cards);

  // GENERATE THE BRAND NEW DECK
  for (size_t value = 0; value < 13; value++) {
    (*cards).push_back(Card(SPADE, value));
    (*cards).push_back(Card(DIAMOND, value));
    (*cards).push_back(Card(HEART, value));
    (*cards).push_back(Card(CLUB, value));
  }
}

void Deck::shakeDeck() {
  if ((*cards).size() > 0) {
    for (int i = 0; i < 10000; i++) {
      size_t rnd_1 = rand() % (*cards).size();
      size_t rnd_2 = rand() % (*cards).size();

      Card tmp_card = (*cards).at(rnd_1);

      (*cards).at(rnd_1) = (*cards).at(rnd_2);
      (*cards).at(rnd_2) = tmp_card;
    }
  }
}

Card Deck::pickToDeck() {
  if ((*cards).size() > 0) {
    Card c = (*cards).back();
    (*cards).pop_back();
    return c;
  }
  return Card(SPADE, 66);
}

void Deck::addToDeck(Card c) { (*cards).push_back(c); }

std::vector<cards_t> Deck::getAllMoves() {
  std::vector<cards_t> moves;
  moves.push_back(cards);
  return moves;
}
