#include "deck.hh"

int getHandValue(Deck hand);

bool checkGreenHand(Deck hand);
bool checkCombo(Deck deck);

void put(Deck deck);
Card pickUnder(Deck heap);
Card pickHeap(Deck heap); // NULL IF NO CARDS

std::vector<Deck> generateAllMoves(Deck hand);
