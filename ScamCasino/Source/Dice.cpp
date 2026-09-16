#include "Dice.h"
#include "Functions.h"
#include "Values.h"
#include "Statistics.h"
#include <iostream>
#include "GameData.h"

namespace Casino::dice
{
    void Play(GameData& data, StatisticsData& statistics)
    {
        functions::Money(statistics, Game::Dice);

        if (functions::CheckTooMuch(statistics, Game::Dice))
        {
            return;
        }

   /*   int choice{};
        while (true)
        {
            std::cout << "1. Instruktioner\n";
            std::cout << "2. Spela\n";
            std::cout << "3. Lämna bord (inga pengar kommer tappas)";

            if (std::cin >> choice && (choice == 1 || choice == 2 || choice == 3 ))
            {
                break;
            }

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "Skriv bara 1 eller 2 eller 3.\n";
        }

        const Choice choice();
        {
            switch (choice)
            {
                case Choice::Yes:
                  system("cls");
                  std::cout << "Spelet g\x86r ut p\x86 att du kommer sl\x86 tv\x86 stycken sexsiffringa t\x84rningar,\ndu ska gissa p\x86 ett tal mellan 2 till 12.\n";
                  std::cout << "Om din gissning \x84r lika med summan av de tv\x86 t\x84rningarna vinner du 2x av de satsade pengarna!\n";
                  break;
                case Choice::No:
                  break;
                case Choice::Leave:
            }
        }
    */

        functions::PlaceBet(data);
        const int bet = data.currentBet;

        int guess{};
        while (true)
        {
            std::cout << "Gissa summan av tv\x86 t\x84rningar ("
                      << Values::diceMinimumGuess << "-"
                      << Values::diceMaximumGuess << "): ";

            if (std::cin >> guess && guess >= Values::diceMinimumGuess && guess <= Values::diceMaximumGuess)
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
            data.balance += bet * Values::normalPayout;
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
