#pragma once

#include <cstdlib>

#include "deck.hh"

class Game
{
public:
    Game();
    void dump();
    int runLoop();

private:
    Deck hand_p1;
    Deck hand_p2;
    Deck heap;
    Deck cemetery;
};
