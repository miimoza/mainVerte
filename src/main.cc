#include <clocale>
#include <iostream>

#include "card.hh"
#include "deck.hh"
#include "game.hh"

void simulation(size_t nb_game)
{
    int p1_success = 0, p2_success = 0, p1_blackball = 0, p2_blackball = 0,
        tied = 0;

    int p1_success_turn = 0, p2_success_turn = 0, p1_blackball_turn = 0,
        p2_blackball_turn = 0, tied_turn = 0;

    for (size_t i = 0; i < nb_game; i++)
    {
        Game game = Game();
        struct GameResult result = game.runLoop();
        switch (result.status)
        {
        case P1_SUCCESS:
            p1_success++;
            p1_success_turn += result.turn;
            break;
        case P2_SUCCESS:
            p2_success++;
            p2_success_turn += result.turn;
            break;
        case P1_BLACKBALL:
            p1_blackball++;
            p1_blackball_turn += result.turn;
            break;
        case P2_BLACKBALL:
            p2_blackball++;
            p2_blackball_turn += result.turn;
            break;
        case TIED:
            tied++;
            tied_turn += result.turn;
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

    std::cout << "=========== RESULT (games:" << nb_game << ")=======\n";
    std::cout << "p1_success:" << p1_success << "(" << p1_success_turn_average
              << ") | p1_blackball:" << p1_blackball << "("
              << p1_blackball_turn_average << ")\n";
    std::cout << "p2_success:" << p2_success << "(" << p2_success_turn_average
              << ") | p2_blackball:" << p2_blackball << "("
              << p2_blackball_turn_average << ")\n";
    std::cout << "tied:" << tied << "(" << tied_turn_average << ")\n";
}

int main()
{
    simulation(1000);
}
