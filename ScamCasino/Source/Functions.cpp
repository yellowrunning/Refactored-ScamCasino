#include "Functions.h"
#include "Values.h"
#include <iostream>
#include <random>

namespace Casino::functions
{
    int GetRndInt()
    {
        std::random_device seed;
        std::mt19937 rndEngine(seed());
        std::uniform_int_distribution<int> rndDist(1, Values::diceSides);
        return rndDist(rndEngine);
    }

    void Enter()
    {
        std::cout << "\ntryck p\x86 enter f\x94r att forts\x84tta\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }

    int PlaceBet(GameData& data)
    {
        while (true)
        {
            system("cls");

            std::cout << "Satsa pengar:\n";
            std::cout << "Kontobalans: " << data.balance << "kr\n> ";

            if (std::cin >> data.currentBet &&
                data.currentBet >= Values::minimumBet &&
                data.currentBet <= data.balance)
            {
                return data.currentBet;
            }

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Skriv en giltig summa.\n";
        }
    }

    int GetTableProfit(const StatisticsData& statistics, Game game)
    {
        switch (game)
        {
        case Game::Dice:
            return statistics.diceProfit;
        case Game::OddEven:
            return statistics.oddEvenProfit;
        case Game::DiceBaccarat:
            return statistics.baccaratProfit;
        case Game::CoinFlip:
            return statistics.coinFlipProfit;
        case Game::Roulette:
            return statistics.rouletteProfit;
        default:
            return 0;
        }
    }

    void AddStats(StatisticsData& statistics, Game game, int bet, int winnings)
    {
        for (int i = Values::maxRecentGames - 1; i > 0; --i)
        {
            statistics.recentGames[i] = statistics.recentGames[i - 1];
        }

        statistics.recentGames[0] = { game, bet, winnings, false };

        switch (game)
        {
        case Game::Dice:
            statistics.diceProfit += winnings;
            break;
        case Game::OddEven:
            statistics.oddEvenProfit += winnings;
            break;
        case Game::DiceBaccarat:
            statistics.baccaratProfit += winnings;
            break;
        case Game::CoinFlip:
            statistics.coinFlipProfit += winnings;
        case Game::Roulette:
            statistics.rouletteProfit += winnings;
            break;
        default:
            break;
        }
    }

    const char* TranslateGameId(Game game)
    {
        switch (game)
        {
        case Game::Dice:
            return "Dice";
        case Game::OddEven:
            return "Udda/J\x84mnt";
        case Game::DiceBaccarat:
            return "Dice Baccarat";
        case Game::CoinFlip:
            return "Coinflip";
        case Game::Roulette:
            return "Roulette";
        default:
            return "Tomt";
        }
    }

    void Money(StatisticsData& statistics, Game game)
    {
        const int money = GetTableProfit(statistics, game);

        if (money > Values::moneyMessageLimit)
        {
            std::cout << "Du har tj\x84rnat " << money << "kr vid "
                      << TranslateGameId(game) << "-bordet!\n";
        }
        else if (money < Values::moneyMessageLimit)
        {
            std::cout << "Du har tappat " << -money << "kr vid "
                      << TranslateGameId(game) << "-bordet.\n";
        }
        else
        {
            std::cout << "Du har inte tappat eller tj\x84rnat n\x86got vid "
                      << TranslateGameId(game) << "-bordet.\n";
        }
    }

    bool CheckTooMuch(const StatisticsData& statistics, Game game)
    {
        if (GetTableProfit(statistics, game) > Values::securityLimit)
        {
            std::cout << "Du har vunnit f\x94r mycket vid det h\x84r bordet!\n";
            std::cout << "GTFO\n";
            std::cout << "Du f\x86r fortfarande spela p\x86 andra bord.\n";
            Enter();
            return true;
        }

        return false;
    }

    void CheckMoney(const GameData& data)
    {
        if (data.balance <= 0)
        {
            std::cout << "Kontobalansen \x84r 0kr. GTFO\n";
        }
    }
}
