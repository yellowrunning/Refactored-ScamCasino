#include "Dice.h"
#include "Functions.h"
#include "Constants.h"
#include "Statistics.h"
#include <iostream>

namespace casino::dice
{
    void Play(GameData& data, StatisticsData& statistics)
    {
        functions::Money(statistics, Game::Dice);

        if (functions::CheckTooMuch(statistics, Game::Dice))
        {
            return;
        }

        functions::PlaceBet(data);
        const int bet = data.currentBet;

        int guess{};
        while (true)
        {
            std::cout << "Gissa summan av tv\x86 t\x84rningar ("
                      << constants::diceMinimumGuess << "-"
                      << constants::diceMaximumGuess << "): ";

            if (std::cin >> guess &&
                guess >= constants::diceMinimumGuess &&
                guess <= constants::diceMaximumGuess)
            {
                break;
            }

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Skriv en summa mellan 2 och 12.\n";
        }

        const int numberA = functions::GetRndInt();
        const int numberB = functions::GetRndInt();
        const int sum = numberA + numberB;

        data.balance -= bet;
        int winnings = -bet;

        std::cout << "Du fick " << numberA << " och " << numberB
                  << " = " << sum << "\n";

        if (guess == sum)
        {
            winnings = bet;
            data.balance += bet * constants::normalPayout;
            std::cout << "du vann!\n";
        }
        else
        {
            std::cout << "du f\x94rlorade.\n";
        }

        functions::AddStats(statistics, Game::Dice, bet, winnings);
        std::cout << "Kontobalans: " << data.balance << "kr\n";
        functions::CheckMoney(data);
        statistics::Show(statistics, data);
    }
}
