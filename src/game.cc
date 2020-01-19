#define PLAYER_ONE 1
#define PLAYER_TWO 2

#include "game.hh"

#include <iostream>
#include <sstream>
#include <string>

#include "moves.hh"

void Game::dump()
{
    std::cout << "===================== GAME STATUS ======================\n";
    std::cout << "P1" << hand_p1 << "(" << hand_p1.getValue() << ") | P2"
              << hand_p2 << "(" << hand_p2.getValue() << ")\n";
    std::cout << "C" << cemetery << " | L" << last_combo << "\n";
    std::cout << "H" << heap << "\n";
    std::cout << "========================================================\n";
}

Game::Game()
{
    std::cout << "Init the game...\n";

    heap = Deck();
    hand_p1 = Deck();
    hand_p2 = Deck();
    cemetery = Deck();
    last_combo = Deck();

    heap.brandNew();
    heap.shuffle();

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

    while (true)
    {
        gameTurn(PLAYER_ONE);
        gameTurn(PLAYER_TWO);
    }

    return 0;
}

void Game::gameTurn(int player)
{
    bool valid_entry = false;

    while (!valid_entry)
    {
        dump();
        std::string command_p1;
        std::cout
            << "\033[0;31m[P" << player
            << "]\033[1;37m(<$card1_index,[...]>;<'h':heap,'c':cemetery>)$ ";
        std::cin >> command_p1;
        if (parse_and_apply(command_p1, player))
            valid_entry = true;
    }
}

int Game::parse_and_apply(std::string command, int player)
{
    std::cout << "RES:" << command << "\n";

    int semicolon_pos = command.find(";");
    std::string combo_indexes = command.substr(0, semicolon_pos);
    std::string picking_way = command.substr(semicolon_pos + 1);

    std::cout << "Combo:" << combo_indexes << "\n";
    std::cout << "Pick:" << picking_way << "\n";

    Deck combo = Deck();
    std::stringstream ss(combo_indexes);

    for (int i; ss >> i;)
    {
        std::cout << "c:" << i << "\n";

        if (player == PLAYER_ONE)
            combo.add(hand_p1.pick(i));
        else
            combo.add(hand_p2.pick(i));

        if (ss.peek() == ',')
            ss.ignore();
    }

    dump();

    if (!put(combo))
        return 0;

    dump();

    if (picking_way.compare("h") == 0)
    {
        if (!pickHeap(player))
            return 0;
    } else
    {
        if (!pickUnder(picking_way.at(1), player))
            return 0;
    }

    return 1;
}

int Game::put(Deck combo)
{
    if (!checkCombo(combo))
    {
        std::cout << "[error] invalid combo\n";
        return 0;
    }

    std::cout << "[PUT] " << combo << "\n";

    last_combo.addDeck(combo);

    return 1;
}

int Game::pickUnder(size_t cemetery_index, int player)
{
    if (cemetery_index >= cemetery.getSize())
    {
        std::cout << "[error] invalid cemetery index\n";
        return 0;
    }

    std::cout << "[PICK_UNDER] " << cemetery_index << "\n";
    if (player == PLAYER_ONE)
        hand_p1.add(cemetery.pick(cemetery_index));
    else
        hand_p2.add(cemetery.pick(cemetery_index));

    cemetery.clear();
    cemetery.addDeck(last_combo);

    return 1;
}

int Game::pickHeap(int player)
{
    // RETURN 0 IF NO CARDS
    if (heap.getSize() == 0)
    {
        std::cout << "[error] no more cards in the heap\n";
        return 0;
    }

    std::cout << "[PICK_HEAP]\n";
    if (player == PLAYER_ONE)
        hand_p1.add(heap.pick());
    else
        hand_p2.add(heap.pick());

    heap.addDeck(cemetery);
    cemetery.addDeck(last_combo);

    return 1;
}
