

bool checkGreenHand(Deck hand)
{
    return getHandValue() <= 7;
}
bool checkCombo(Deck deck)
{
    return false;
}

void put(Deck deck)
{}
Card pickUnder(Deck combo)
{
    return combo.pickToDeck();
}
Card pickHeap(Deck heap)
{
    return heap.pickToDeck();
}; // NULL IF NO CARDS

std::vector<Deck> generateAllMoves(Deck hand);
