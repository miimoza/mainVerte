#pragma once

#include <string>

#include "deck.hh"

class AI
{
public:
    AI(Deck hand, Deck cemetery);
    std::string get_command();
    Deck get_best_combo();
    std::string get_combo_indexes();
    std::string get_pickway();

    void update_hand();

private:
    Deck hand;
    Deck cemetery;
    Deck combo;
};
