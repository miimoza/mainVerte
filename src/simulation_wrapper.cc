#include "simulation_wrapper.hh"

#include <clocale>
#include <iostream>

#include "card.hh"
#include "deck.hh"
#include "game.hh"
#include "game_result.hh"

void launchSimulation(size_t nb_game)
{
    int p1_success = 0, p2_success = 0, p1_blackball = 0, p2_blackball = 0,
        tied = 0;

    int p1_success_turn = 0, p2_success_turn = 0, p1_blackball_turn = 0,
        p2_blackball_turn = 0, tied_turn = 0;

    int p1_success_value = 0, p2_success_value = 0, p1_blackball_value = 0,
        p2_blackball_value = 0, tied_value = 0;

    for (size_t i = 0; i < nb_game; i++)
    {
        Game game = Game();
        GameResult result = game.runLoop();
        // result.dump();
        switch (result.status)
        {
        case P1_SUCCESS:
            p1_success++;
            p1_success_turn += result.turn;
            p1_success_value += result.greenhand_value;
            break;
        case P2_SUCCESS:
            p2_success++;
            p2_success_turn += result.turn;
            p2_success_value += result.greenhand_value;
            break;
        case P1_BLACKBALL:
            p1_blackball++;
            p1_blackball_turn += result.turn;
            p1_blackball_value += result.greenhand_value;
            break;
        case P2_BLACKBALL:
            p2_blackball++;
            p2_blackball_turn += result.turn;
            p2_blackball_value += result.greenhand_value;
            break;
        case TIED:
            tied++;
            tied_turn += result.turn;
            tied_value += result.greenhand_value;
            break;
        }
    }

    float p1_success_turn_average = (float)p1_success_turn / (float)p1_success;
    float p2_success_turn_average = (float)p2_success_turn / (float)p2_success;
    float p1_blackball_turn_average =
        (float)p1_blackball_turn / (float)p1_blackball;
    float p2_blackball_turn_average =
        (float)p2_blackball_turn / (float)p2_blackball;
    float tied_turn_average = (float)tied_turn / (float)tied;

    float p1_success_value_average =
        (float)p1_success_value / (float)p1_success;
    float p2_success_value_average =
        (float)p2_success_value / (float)p2_success;
    float p1_blackball_value_average =
        (float)p1_blackball_value / (float)p1_blackball;
    float p2_blackball_value_average =
        (float)p2_blackball_value / (float)p2_blackball;
    float tied_value_average = (float)tied_value / (float)tied;

    std::cout << "RESULTS: (games:" << nb_game << ")\n";
    std::cout << "p1_success:" << p1_success << "(t:" << p1_success_turn_average
              << ", v:" << p1_success_value_average
              << ") | p1_blackball:" << p1_blackball
              << "(t:" << p1_blackball_turn_average
              << ", v:" << p1_blackball_value_average << ")\n";
    std::cout << "p2_success:" << p2_success << "(t:" << p2_success_turn_average
              << ", v:" << p2_success_value_average
              << ") | p2_blackball:" << p2_blackball
              << "(t:" << p2_blackball_turn_average
              << ", v:" << p2_blackball_value_average << ")\n";
    std::cout << "tied:" << tied << "(t:" << tied_turn_average
              << ", v:" << tied_value_average << ")\n";
}
