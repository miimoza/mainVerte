#include "game_result.hh"

#include <iostream>

GameResult::GameResult(enum Status status, size_t turn, int greenhand_value)
    : status(status)
    , turn(turn)
    , greenhand_value(greenhand_value)
{
    std::cout << "*******************\n";
    std::cout << "*** GREEN HAND ! **\n";
    std::cout << "*******************\n";

    switch (status)
    {
    case P1_SUCCESS:
        std::cout << "*******************\n";
        std::cout << "**** P1 SUCCESS ***\n";
        break;
    case P2_SUCCESS:
        std::cout << "**** P2 SUCCESS ***\n";
        break;
    case P1_BLACKBALL:
        std::cout << "*** P1 BLACKBALL **\n";
        break;
    case P2_BLACKBALL:
        std::cout << "*** P2 BLACKBALL **\n";
        break;
    case TIED:
        std::cout << "******* TIED ******\n";
        break;
    }

    std::cout << "- GREENHAND VALUE: " << greenhand_value << "\n";
    std::cout << "- TURN NUMBER:" << turn << "\n";
}
