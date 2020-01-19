#include <vector>

#include "deck.hh"

int getHandValue(Deck hand);

bool checkGreenHand(Deck hand);
bool checkCombo(Deck deck);

std::vector<Deck> generateAllMoves(Deck hand);
