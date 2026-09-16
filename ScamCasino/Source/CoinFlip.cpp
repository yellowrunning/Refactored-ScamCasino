#include "CoinFlip.h"
#include "Functions.h"
#include "Values.h"
#include "Statistics.h"
#include <iostream>
#include <random>

namespace Casino::coinFlip
{
    void Play(GameData& data, StatisticsData& statistics)
    {
        functions::Money(statistics, Game::CoinFlip);

        if (functions::CheckTooMuch(statistics, Game::CoinFlip))
        {
            return;
        }

        functions::PlaceBet(data);
        const int bet = data.currentBet;

        int guess{};
        while (true)
        {
            std::cout << "1. Krona\n";
            std::cout << "2. Klave\n> ";

            if (std::cin >> guess && guess >= Values::coinMinimum && guess <= Values::coinMaximum)
            {
                break;
            }

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "V\x84lj bara 1 eller 2.\n";
        }

        const CoinSide choice = static_cast<CoinSide>(guess);

        std::random_device seed;
        std::mt19937 rndEngine(seed());
        std::uniform_int_distribution<int> rndCoin(Values::coinMinimum, Values::coinMaximum);
        const CoinSide result = static_cast<CoinSide>(rndCoin(rndEngine));

        data.balance -= bet;
        int winnings = -bet;

        if (result == CoinSide::Heads)
        {
            std::cout << "Myntet blev Krona!\n";
        }
        else
        {
            std::cout << "Myntet blev Klave!\n";
        }

        if (choice == result)
        {
            winnings = bet;
            data.balance += bet * Values::normalPayout;
            std::cout << "du vann!\n";
        }
        else
        {
            std::cout << "du f\x94rlorade.\n";
        }

        functions::AddStats(statistics, Game::CoinFlip, bet, winnings);
        std::cout << "Kontobalans: " << data.balance << "kr\n";
        functions::CheckMoney(data);
        statistics::Show(statistics, data);
    }
}
