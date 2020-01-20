#pragma once

#include <cstdlib>

#include "deck.hh"

class Game
{
public:
    Game();
    void dump();
    int declare_green_hand(int player);
    int runLoop();
    bool userTurn(int player);
    bool AITurn(int player);
    int parse_and_apply(std::string command, int player);
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
