#define PLAYER_ONE 1
#define PLAYER_TWO 2

#include "game.hh"

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "AI.hh"

Game::Game()
{
    heap = Deck();
    hand_p1 = Deck();
    hand_p2 = Deck();
    cemetery = Deck();
    last_combo = Deck();
    current_combo = Deck();

    heap.brandNew();
    heap.shuffle();

    for (int i = 0; i < 6; i++)
    {
        hand_p1.add(heap.pick());
        hand_p2.add(heap.pick());
    }

    cemetery.add(heap.pick());

    hand_p1.sort();
    hand_p2.sort();

    turn_nb = 0;
}

void Game::dump(int player)
{
    std::cout << "========(" << turn_nb << ")========\n";

    if (player == PLAYER_ONE)
    {
        hand_p2.dumpBack();
        std::cout << "\n";
        std::cout << "             " << cemetery << "🂠\n";
        std::cout << hand_p1 << "\n";
        std::cout << "0 1 2 3 4 5\n";
    } else if (player == PLAYER_TWO)
    {
        hand_p1.dumpBack();
        std::cout << "\n";
        std::cout << "             " << cemetery << "🂠\n";
        std::cout << hand_p2 << "\n";
        std::cout << "0 1 2 3 4 5\n";
    } else
    {
        std::cout << hand_p2 << "\n";
        std::cout << "             " << cemetery << "🂠\n";
        std::cout << hand_p1 << "\n";
    }

    std::cout << "===================\n";
}

GameResult Game::runLoop()
{
    while (true)
    {
        turn_nb++;
        if (AITurn(PLAYER_ONE))
            return declare_green_hand(PLAYER_ONE);

        if (AITurn(PLAYER_TWO))
            return declare_green_hand(PLAYER_TWO);
    }

    return GameResult(TIED, 0, 0);
}

bool Game::AITurn(int player)
{
    int res;

    if (player == PLAYER_ONE)
    {
        AI ai_p1 = AI(hand_p1, cemetery, hand_p2.getSize());
        res = parse_and_apply(ai_p1.getCommand(), player);
    } else
    {
        AI ai_p2 = AI(hand_p2, cemetery, hand_p1.getSize());
        res = parse_and_apply(ai_p2.getCommand(), player);
    }

    if (res == 2)
        return true;

    if (!res)
        throw "\033[0;41m[ENTRY NON VALID PLEASE FIX YOUR AI]\033[0m\n";

    return false;
}

bool Game::userTurn(int player)
{
    dump(player);
    bool valid_entry = false;
    int res;
    while (!valid_entry)
    {
        std::string command;
        std::cout << "\033[0;92m[P" << player << "]\033[1;37m$ ";
        std::cin >> command;
        res = parse_and_apply(command, player);
        if (res == 2)
            return true;
        else if (res == 1)
            valid_entry = true;
        else
            std::cout << "\033[0;41m[ENTRY NON VALID PLEASE TRY "
                         "AGAIN]\033[0m\n\033[0;41musage: "
                         "<$card1_index,[...]>;<'h':heap,'c$index':"
                         "cemetery>\033[0m\n";
    }

    return false;
}

int Game::parse_and_apply(std::string command, int player)
{
    if (!command.compare("greenhand"))
    {
        if ((player == PLAYER_ONE && !hand_p1.checkGreenHand())
            || (player == PLAYER_TWO && !hand_p2.checkGreenHand()))
        {
            std::cout << "[error] greenhand not valid\n";
            return 0;
        }
        return 2;
    }

    int semicolon_pos = command.find(";");
    std::string combo_indexes_str = command.substr(0, semicolon_pos);
    std::string picking_way = command.substr(semicolon_pos + 1);

    if (semicolon_pos == -1 || !combo_indexes_str.size() || !picking_way.size())
    {
        std::cout << "[error] please respect usage "
                     "(<$card1_index,[...]>;<'h':heap,'c$index':"
                     "cemetery>)\n";
        return 0;
    }

    if (!fill_current_combo(combo_indexes_str, player))
        return 0;

    if (!put(player))
        return 0;

    if (picking_way.compare("h") == 0)
    {
        if (!pickHeap(player))
            return 0;
    } else if (picking_way.at(0) == 'c')
    {
        std::string str;
        if (picking_way.size() < 2)
            str = std::string(1, '0');
        else
            str = std::string(1, picking_way.at(1));

        std::stringstream sstream(str);
        size_t cemetery_index;

        sstream >> cemetery_index;
        if (!pickUnder(cemetery_index, player))
            return 0;
    } else
    {
        return 0;
    }

    if (player == PLAYER_ONE)
        hand_p1.sort();
    else
        hand_p2.sort();

    return 1;
}

bool Game::fill_current_combo(std::string combo_indexes_str, int player)
{
    if (combo_indexes_str.find_first_not_of("0123456789,") != std::string::npos)
    {
        std::cout << "[error] combo index must be a digit\n";
        return false;
    }

    std::stringstream ss(combo_indexes_str);
    std::vector<size_t> combo_indexes = std::vector<size_t>();

    for (size_t index; ss >> index;)
    {
        if ((player == PLAYER_ONE && index >= hand_p1.getSize())
            || (player == PLAYER_TWO && index >= hand_p2.getSize()))
        {
            std::cout << "[error] invalid combo indexes\n";
            return false;
        }
        combo_indexes.push_back(index);

        if (ss.peek() == ',')
            ss.ignore();
    }

    std::sort(combo_indexes.begin(), combo_indexes.end());

    auto it = std::unique(combo_indexes.begin(), combo_indexes.end());
    bool containDuplicate = (it == combo_indexes.end());
    if (!containDuplicate)
    {
        std::cout << "[error] combo index must not contain duplicate\n";
        return false;
    }

    for (int i = combo_indexes.size() - 1; i >= 0; i--)
    {
        if (player == PLAYER_ONE)
            current_combo.add(hand_p1.pick(combo_indexes[i]));
        else
            current_combo.add(hand_p2.pick(combo_indexes[i]));

        if (ss.peek() == ',')
            ss.ignore();
    }

    return true;
}

GameResult Game::declare_green_hand(int player)
{
    // dump();

    int score_p1 = hand_p1.getValue();
    int score_p2 = hand_p2.getValue();

    if (player == PLAYER_ONE)
    {
        if (score_p1 > score_p2)
            return GameResult(P1_BLACKBALL, turn_nb, score_p1);
        if (score_p1 < score_p2)
            return GameResult(P1_SUCCESS, turn_nb, score_p1);
    } else
    {
        if (score_p2 > score_p1)
            return GameResult(P2_BLACKBALL, turn_nb, score_p2);

        if (score_p2 < score_p1)
            return GameResult(P2_SUCCESS, turn_nb, score_p2);
    }

    return GameResult(TIED, turn_nb, score_p1);
}

bool Game::put(int player)
{
    if (!current_combo.checkCombo())
    {
        std::cout << "[error] invalid combo (" << current_combo << ")\n";

        if (player == PLAYER_ONE)
            hand_p1.addDeck(current_combo);
        else
            hand_p2.addDeck(current_combo);

        return false;
    }

    // std::cout << "[PUT] " << current_combo << "\n";

    last_combo.addDeck(current_combo);

    return true;
}

bool Game::pickUnder(size_t cemetery_index, int player)
{
    if (cemetery_index >= cemetery.getSize())
    {
        std::cout << "[error] invalid cemetery index (" << cemetery_index << ">"
                  << cemetery.getSize() - 1 << ")\n";
        return false;
    }

    // std::cout << "[PICK_UNDER] cemetery_index:" << cemetery_index << "\n";
    if (player == PLAYER_ONE)
        hand_p1.add(cemetery.pick(cemetery_index));
    else
        hand_p2.add(cemetery.pick(cemetery_index));

    cemetery.clear();
    cemetery.addDeck(last_combo);

    return true;
}

bool Game::pickHeap(int player)
{
    // RETURN 0 IF NO CARDS
    if (heap.getSize() == 0)
    {
        std::cout << "[error] no more cards in the heap\n";
        return false;
    }

    // std::cout << "[PICK_HEAP]\n";
    if (player == PLAYER_ONE)
        hand_p1.add(heap.pick());
    else
        hand_p2.add(heap.pick());

    cemetery.clear();
    cemetery.addDeck(last_combo);

    return true;
}
