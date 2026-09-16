#include "Statistics.h"
#include "Functions.h"
#include <iostream>

namespace Casino::statistics
{
    void Show(const StatisticsData& statistics, const GameData& data)
    {
        std::cout << "\n===== Statistik =====\n";

        for (int i = 0; i < 5; ++i)
        {
            const GameResult& result = statistics.recentGames[i];

            if (result.empty)
            {
                std::cout << i + 1 << ". [Inget spel]\n";
            }
            else
            {
                std::cout << i + 1 << ". "
                          << functions::TranslateGameId(result.game)
                          << " | Satsning: " << result.bet
                          << "kr | Vinst/f\x94rlust: " << result.winnings
                          << "kr\n";
            }
        }

        std::cout << "\nPengar vid varje bord:\n";
        std::cout << "Dice: " << statistics.diceProfit << "kr\n";
        std::cout << "Udda/Ja\x84mnt: " << statistics.oddEvenProfit << "kr\n";
        std::cout << "Dice Baccarat: " << statistics.baccaratProfit << "kr\n";
        std::cout << "Coinflip: " << statistics.coinFlipProfit << "kr\n";
        std::cout << "\nKontobalans: " << data.balance << "kr\n";

        functions::Enter();
    }
}
