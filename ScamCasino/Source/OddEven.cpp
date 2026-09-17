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

                    std::cout << "Spelet g\x86r ut p\x86 att du kommer sl\x86 tv\x86 stycken sexsiffringa t\x84rningar\n";
                    std::cout << "Du ska gissa p\x86 udda eller j\x84mnt.";
                    std::cout << "\nOm de tv\x86 t\x84rningarna sl\x86r det du gissade p\x86 vinner du 2x de pengarna du satsade!\n";
                    std::cout << "Om t\x84rningarna sl\x86r udda och j\x84mnt f\x94rlorar du alltid.\n";

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
            std::cout << "\nGissa Udda (1) eller J\x84mnt (2)\n>";

            if (std::cin >> guess && (guess == 1 || guess == 2))
            {
                break;
            }
            std::cout << "Skriv bara 1 eller 2.\n";
            functions::Enter();
            system("cls");
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

        std::cout << "\nDu fick " << numberA << " och " << numberB << ".\n\n";

        if (won)
        {
            winnings = bet;
            data.balance += bet * Values::normalPayout;
            std::cout << "Du vann!\n";
        }
        else
        {
            std::cout << "Du f\x94rlorade.\n";
        }

        functions::AddStats(statistics, Game::OddEven, bet, winnings);
        std::cout << "Kontobalans: " << data.balance << "kr\n";
        functions::CheckMoney(data);
        statistics::Show(statistics, data);
    }
}
