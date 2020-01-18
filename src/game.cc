#include "game.hh"

#include <iostream>

void Game::dump()
{
    std::cout << "===================== GAME STATUS ======================\n";
    std::cout << "P1{" << hand_p1 << "} | P2{" << hand_p2 << "}\n";
    std::cout << "C{" << cemetery << "} | H{" << heap << "}\n";
    std::cout << "HSize: " << heap.getSize() << "\n";
    std::cout << "========================================================\n";
}

Game::Game()
{
    std::cout << "Init the game...\n";

    heap = Deck();
    hand_p1 = Deck();
    hand_p2 = Deck();
    cemetery = Deck();

    heap.brandNew();
    heap.shake();

    for (int i = 0; i < 6; i++)
    {
        hand_p1.add(heap.pick());
        hand_p2.add(heap.pick());
    }

    cemetery.add(heap.pick());
}

int Game::runLoop()
{
    std::cout << "Let's go !\n";

    std::cout << "P1 VALUE: " << hand_p1.getValue() << "\n";

    return 0;
}
