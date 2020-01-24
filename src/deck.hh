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
    void dumpBack();
    void brandNew();
    void shuffle();
    void sort();
    void clear();

    Card getCard(size_t index);
    Card pick(size_t index = 0);
    void popBack();
    void copyDeck(Deck deck);
    void add(Card c);
    void addDeck(Deck deck);

    enum Color getColorAt(size_t i);
    size_t getValueAt(size_t i);
    size_t getSize();
    int getValue();
    int find(Card c);

    bool checkGreenHand();
    bool checkCombo();
    bool checkSameColor();
    bool checkSameValue();
    bool checkSequence();

    void __generateCombination(std::shared_ptr<std::vector<Deck>> combos,
                               Deck combination, size_t offset, size_t k);
    std::shared_ptr<std::vector<Deck>> generateCombos();

private:
    cards_t cards;
};
