#include "moves.hh"

bool checkGreenHand(Deck hand)
{
    return hand.getValue() <= 7;
}
bool checkCombo(Deck combo)
{
    return true;
}

std::vector<Deck> generateAllMoves(Deck hand);
