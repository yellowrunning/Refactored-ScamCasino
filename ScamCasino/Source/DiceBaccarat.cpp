#include "DiceBaccarat.h"
#include "Functions.h"
#include "Constants.h"
#include "Statistics.h"
#include <iostream>

namespace casino::diceBaccarat
{
    void Play(GameData& data, StatisticsData& statistics)
    {
        functions::Money(statistics, Game::DiceBaccarat);

        if (functions::CheckTooMuch(statistics, Game::DiceBaccarat))
        {
            return;
        }

        functions::PlaceBet(data);
        const int bet = data.currentBet;

        int guess{};
        while (true)
        {
            std::cout << "1. Player (2x)\n";
            std::cout << "2. Banken (2x)\n";
            std::cout << "3. Lika (10x)\n> ";

            if (std::cin >> guess && guess >= 1 && guess <= 3)
            {
                break;
            }

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Du kan bara gissa p\x86 1, 2 eller 3.\n";
        }

        const BaccaratBet choice = static_cast<BaccaratBet>(guess);

        const int playerA = functions::GetRndInt();
        const int playerB = functions::GetRndInt();
        const int bankerA = functions::GetRndInt();
        const int bankerB = functions::GetRndInt();

        const int playerTotal = playerA + playerB;
        const int bankerTotal = bankerA + bankerB;

        BaccaratBet winner = BaccaratBet::Tie;

        if (playerTotal > bankerTotal)
        {
            winner = BaccaratBet::Player;
        }
        else if (bankerTotal > playerTotal)
        {
            winner = BaccaratBet::Banker;
        }

        data.balance -= bet;
        int winnings = -bet;

        std::cout << "Player fick " << playerA << " + " << playerB
                  << " = " << playerTotal << "\n";
        std::cout << "Banken fick " << bankerA << " + " << bankerB
                  << " = " << bankerTotal << "\n";

        if (choice == winner)
        {
            if (winner == BaccaratBet::Tie)
            {
                winnings = bet * (constants::baccaratTiePayout - 1);
                data.balance += bet * constants::baccaratTiePayout;
            }
            else
            {
                winnings = bet;
                data.balance += bet * constants::normalPayout;
            }

            std::cout << "du vann!\n";
        }
        else
        {
            std::cout << "du f\x94rlorade.\n";
        }

        functions::AddStats(statistics, Game::DiceBaccarat, bet, winnings);
        std::cout << "Kontobalans: " << data.balance << "kr\n";
        functions::CheckMoney(data);
        statistics::Show(statistics, data);
    }
}
