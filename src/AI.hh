#pragma once

#include <string>

#include "deck.hh"

class AI
{
public:
    AI(Deck hand, Deck cemetery);
    std::string getCommand();
    Deck getBestCombo(Deck hand);
    std::string getComboIndexes();
    float getCardCapacity(Card card);
    std::string getPickway();

    void updateHand();

private:
    Deck hand;
    Deck cemetery;
    Deck combo;
};
