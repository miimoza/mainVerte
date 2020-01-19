#pragma once

#include <cstdlib>

#include "deck.hh"

class Game
{
public:
    Game();
    void dump();
    void runLoop();
    void gameTurn(int player);
    bool parse_and_apply(std::string command, int player);
    bool put(int player);
    bool pickUnder(size_t cemetery_index, int player);
    bool pickHeap(int player);
    bool fill_current_combo(std::string combo_indexes_str, int player);

private:
    Deck hand_p1;
    Deck hand_p2;
    Deck heap;

    Deck cemetery;
    Deck last_combo;
    Deck current_combo;
};
