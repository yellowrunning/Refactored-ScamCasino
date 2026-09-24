#include "OddEven.h"
#include "Functions.h"
#include "Values.h"
#include <iostream>

namespace Casino
{
    OddEven::OddEven(int aMinBet, int aMaxBet)
        : myMinBet(aMinBet)
        , myMaxBet(aMaxBet)
        , myProfit(0)
    {

    }

    int OddEven::GetProfit() const
    {
        return myProfit;
    }

    void OddEven::Play(GameData& aData, const char* aPlayerName)
    {
        if (aData.balance < myMinBet)
        {
            system("cls");
            std::cout << "Tyv\x84rr " << aPlayerName << ", du f\x86r inte spela h\x84.\n";
            std::cout << "Detta bord kr\x84ver minst " << myMinBet << "kr p\x86 kontot.\n";
            functions::Enter();
            return;
        }

        static bool firstTime = true;
        if (firstTime)
        {
            system("cls");
            std::cout << "V\x84lkommen till Udda/J\x84mnt, " << aPlayerName << "!";
            std::cout << "\nSaldo: " << aData.balance << "kr\n\n";
            std::cout << "=== REGLER ===\n";
            std::cout << "Det kommer att finnas tv\x86 spelare: Player // Banken.";
            std::cout << "Spelet g\x86r ut p\x86 att du kommer sl\x86 tv\x86 stycken sexsiffringa t\x84rningar\n";
            std::cout << "Du ska gissa p\x86 udda eller j\x84mnt.";
            std::cout << "\nOm de tv\x86 t\x84rningarna sl\x86r det du gissade p\x86 vinner du 2x de pengarna du satsade!\n";
            std::cout << "Om t\x84rningarna sl\x86r udda och j\x84mnt f\x94rlorar du alltid.\n";

            functions::Enter();
            firstTime = false;
        }

        bool playGame = false;
        while (!playGame)
        {
            system("cls");
            int input = 0;

            std::cout << "1. Instruktioner\n";
            std::cout << "2. Spela\n";
            std::cout << "3. L\x84mna bord\n\n";

            if (std::cin >> input && input >= 1 && input <= 3)
            {
                Choice choice = static_cast<Choice>(input);

                switch (choice)
                {
                case Choice::Instructions:
                {
                    system("cls");

                    std::cout << "Spelet g\x86r ut p\x86 att du kommer sl\x86 tv\x86 stycken sexsiffringa t\x84rningar\n";
                    std::cout << "Du ska gissa p\x86 udda eller j\x84mnt.";
                    std::cout << "\nOm de tv\x86 t\x84rningarna sl\x86r det du gissade p\x86 vinner du 2x de pengarna du satsade!\n";
                    std::cout << "Om t\x84rningarna sl\x86r udda och j\x84mnt f\x94rlorar du alltid.\n";

                    functions::Enter();
                    break;
                }
                case Choice::Play:
                {
                    playGame = true;
                    break;
                }
                case Choice::Leave:
                {
                    return;
                }
                }
            }
            else
            {
                std::cout << "Skriv bara 1 eller 2 eller 3.\n";
                functions::Enter();
            }
        }

        functions::PlaceBet(aData, myMinBet, myMaxBet);
        const int bet = aData.currentBet;

        int guess = 0;
        while (true)
        {
            system("cls");
            std::cout << "\nGissa Udda (1) eller J\x84mnt (2)\n>";

            if (std::cin >> guess && (guess == 1 || guess == 2))
            {
                break;
            }
            std::cout << "Skriv bara 1 eller 2.\n";
            functions::Enter();
        }

        const OddEvenChoice choice = static_cast<OddEvenChoice>(guess);
        const int numberA = functions::GetRndInt();
        const int numberB = functions::GetRndInt();

        const bool bothOdd = numberA % 2 != 0 && numberB % 2 != 0;
        const bool bothEven = numberA % 2 == 0 && numberB % 2 == 0;
        const bool won = (choice == OddEvenChoice::Odd && bothOdd) ||
            (choice == OddEvenChoice::Even && bothEven);

        aData.balance -= bet;
        int winnings = -bet;

        std::cout << "\nDu fick " << numberA << " och " << numberB << ".\n\n";

        if (won)
        {
            winnings = bet;
            aData.balance += bet * Values::globalNormalPayout;
            std::cout << "Du vann, " << aPlayerName << "!\n";
        }
        else
        {
            std::cout << "Du f\x94rlorade.\n";
        }

        myProfit += winnings;
        std::cout << "Kontobalans: " << aData.balance << "kr\n";
        functions::Enter();
    }
}