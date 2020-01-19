#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "card.hh"

using cards_t = std::shared_ptr<std::vector<Card>>;

class Deck
{
public:
    Deck();
    friend std::ostream& operator<<(std::ostream& os, const Deck& d);
    void brandNew();
    void shuffle();
    Card pick(int index = 0);
    void add(Card c);
    void addDeck(Deck deck);
    size_t getSize();
    int getValue();
    void clear();

private:
    cards_t cards;
};
