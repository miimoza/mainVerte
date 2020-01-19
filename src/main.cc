#include <clocale>
#include <iostream>

#include "card.hh"
#include "deck.hh"
#include "game.hh"

int main()
{
    Game game = Game();
    game.runLoop();
}
