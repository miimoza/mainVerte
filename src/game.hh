#pragma once

#include <cstdlib>

#include "deck.hh"

class Game
{
public:
    Game();
    void dump();
    int runLoop();
    int parse_and_apply(std::string command, int player);
    int put(Deck combo);
    int pickUnder(size_t cemetery_index, int player);
    int pickHeap(int player);
    void gameTurn(int player);

private:
    Deck hand_p1;
    Deck hand_p2;
    Deck heap;
    Deck cemetery;
    Deck last_combo;
};
