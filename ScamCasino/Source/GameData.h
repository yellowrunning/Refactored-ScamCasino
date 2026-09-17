#pragma once
#include <array>

namespace Casino
{
    enum class Game
    {
        Dice = 1,
        OddEven = 2,
        DiceBaccarat = 3,
        CoinFlip = 4,
        Roulette = 5,
        Statistics = 6,
        Exit = 7
    };

    enum class CoinSide
    {
        Heads = 1,
        Tails = 2
    };

    enum class OddEvenChoice
    {
        Odd = 1,
        Even = 2
    };

    enum class BaccaratBet
    {
        Player = 1,
        Banker = 2,
        Tie = 3
    };

    enum class Choice
    {
        Instructions = 1,
        Play = 2,
        Leave = 3
    };

    struct GameData
    {
        int balance{};
        int currentBet{};
    };

    struct GameResult
    {
        Game game{ Game::Exit };
        int bet{};
        int winnings{};
        bool empty{ true };
    };

    struct StatisticsData
    {
        std::array<GameResult, 5> recentGames{};
        int diceProfit{};
        int oddEvenProfit{};
        int baccaratProfit{};
        int coinFlipProfit{};
        int rouletteProfit{};
    };
}
