#pragma once

#include <cstddef>

enum Status
{
    P1_SUCCESS = 1,
    P2_SUCCESS = 2,
    P1_BLACKBALL = 4,
    P2_BLACKBALL = 8,
    TIED = 16
};

class GameResult
{
public:
    GameResult(enum Status status, size_t turn, int greenhand_value);

    enum Status status;
    size_t turn;
    int greenhand_value;
};
