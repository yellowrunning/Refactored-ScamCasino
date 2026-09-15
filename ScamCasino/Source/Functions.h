#pragma once
#include "GameData.h"

namespace casino::functions
{
    int GetRndInt();
    void Enter();
    int PlaceBet(GameData& data);

    void AddStats(StatisticsData& statistics, Game game, int bet, int winnings);
    int GetTableProfit(const StatisticsData& statistics, Game game);
    const char* TranslateGameId(Game game);

    void Money(StatisticsData& statistics, Game game);
    bool CheckTooMuch(const StatisticsData& statistics, Game game);
    void CheckMoney(const GameData& data);
}
