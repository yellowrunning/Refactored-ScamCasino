#pragma once
#include "GameData.h"

namespace Casino
{
    enum class BetType
    {
        Straight = 1,
        RedBlack = 2,
        OddEven = 3,
        Column = 4
    };
}

namespace Casino::roulette
{
    void Play(GameData& data, StatisticsData& statistics);
}