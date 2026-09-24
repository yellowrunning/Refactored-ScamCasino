#pragma once
#include "GameData.h"

namespace Casino::functions
{
    int GetRndInt();
    void Enter();
    int PlaceBet(GameData& aData, int aMinBet, int aMaxBet);
}