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

        bool playGame{ false };

        while (!playGame)
        {
            int input{};

            std::cout << "1. Instruktioner\n";
            std::cout << "2. Spela\n";
            std::cout << "3. L\x84mna bord\n\n";

            if (std::cin >> input && input >= 1 && input <= 3)
            {
                Choice choice = static_cast<Choice>(input);

                switch (choice)
                {
                case Choice::Instructions:
                    system("cls");

                    std::cout << "Spelet g\x86r ut p\x86 att du kommer sl\x86 tv\x86 stycken sexsiffringa t\x84rningar.\n";
                    std::cout << "Du ska gissa p\x86 ett tal mellan 2 till 12.\n";
                    std::cout << "Om din gissning \x84r lika med summan av de tv\x86 t\x84rningarna vinner du 2x av de satsade pengarna!\n";

                    functions::Enter();
                    system("cls");
                    break;

                case Choice::Play:
                    system("cls");
                    playGame = true;
                    break;

                case Choice::Leave:
                    return;
                }
            }
            else
            {
                std::cout << "Skriv bara 1 eller 2 eller 3.\n";
                functions::Enter();
                system("cls");
            }
        }

        functions::PlaceBet(data);
        const int bet = data.currentBet;

        int guess{};
        while (true)
        {
            std::cout << "\nGissa summan av tv\x86 t\x84rningar ("
                      << Values::globaldiceMinimumGuess << "-"
                      << Values::globaldiceMaximumGuess << "): ";

            if (std::cin >> guess && guess >= Values::globaldiceMinimumGuess && guess <= Values::globaldiceMaximumGuess)
            {
                break;
            }
            std::cout << "Skriv en summa mellan 2 och 12.\n";
            functions::Enter();
            system("cls");
        }

        const int numberA = functions::GetRndInt();
        const int numberB = functions::GetRndInt();
        const int sum = numberA + numberB;

        data.balance -= bet;
        int winnings = -bet;

        std::cout << "Du fick " << numberA << " och " << numberB
                  << " = " << sum << "\n\n";

        if (guess == sum)
        {
            winnings = bet;
            data.balance += bet * Values::globalnormalPayout;
            std::cout << "Du vann!\n";
        }
        else
        {
            std::cout << "Du f\x94rlorade.\n";
        }

        functions::AddStats(statistics, Game::Dice, bet, winnings);
        std::cout << "Kontobalans: " << data.balance << "kr\n";
        functions::CheckMoney(data);
        statistics::Show(statistics, data);
    }
}