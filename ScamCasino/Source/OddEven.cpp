#include "OddEven.h"
#include "Functions.h"
#include "Values.h"
#include "Statistics.h"
#include <iostream>

namespace Casino::oddEven
{
    void Play(GameData& data, StatisticsData& statistics)
    {
        functions::Money(statistics, Game::OddEven);

        if (functions::CheckTooMuch(statistics, Game::OddEven))
        {
            return;
        }

        functions::PlaceBet(data);
        const int bet = data.currentBet;

        int guess{};
        while (true)
        {
            std::cout << "Skriv Udda (1) eller J\x84mnt (2): ";

            if (std::cin >> guess && (guess == 1 || guess == 2))
            {
                break;
            }

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Skriv bara 1 eller 2.\n";
        }

        const OddEvenChoice choice = static_cast<OddEvenChoice>(guess);
        const int numberA = functions::GetRndInt();
        const int numberB = functions::GetRndInt();

        const bool bothOdd = numberA % 2 != 0 && numberB % 2 != 0;
        const bool bothEven = numberA % 2 == 0 && numberB % 2 == 0;
        const bool won = (choice == OddEvenChoice::Odd && bothOdd) ||
                         (choice == OddEvenChoice::Even && bothEven);

        data.balance -= bet;
        int winnings = -bet;

        std::cout << "Du fick " << numberA << " och " << numberB << ".\n";

        if (won)
        {
            winnings = bet;
            data.balance += bet * Values::normalPayout;
            std::cout << "du vann!\n";
        }
        else
        {
            std::cout << "du f\x94rlorade.\n";
        }

        functions::AddStats(statistics, Game::OddEven, bet, winnings);
        std::cout << "Kontobalans: " << data.balance << "kr\n";
        functions::CheckMoney(data);
        statistics::Show(statistics, data);
    }
}
