#include "Dice.h"
#include "Functions.h"
#include "Values.h"
#include "Statistics.h"
#include <iostream>
#include "GameData.h"

namespace Casino
{
    Dice::Dice(int aMinBet, int aMaxBet)
        : myMinBet(aMinBet)
        , myMaxBet(aMaxBet)
        , myProfit(0)
    {

    }

    int Dice::GetProfit() const
    {
        return myProfit;
    }

    void Dice::Play(GameData& aData, const char* aPlayerName)
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
            std::cout << "V\x84lkommen till Dice " << aPlayerName << "!\n";
            std::cout << "Saldo: " << aData.balance << "kr\n\n";
            std::cout << "=== REGLER ===\n";
            std::cout << "Du ska gissa summan av tv\x86 t\x84rningar (2-12). Vinst ger 2x pengarna!\n";
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
                    std::cout << "=== REGLER ===\n";
                    std::cout << "Du ska gissa summan av tv\x86 t\x84rningar (2-12). Vinst ger 2x pengarna!\n";
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
                std::cout << "Skriv bara 1, 2 eller 3.\n";
                functions::Enter();
            }
        }

        functions::PlaceBet(aData, myMinBet, myMaxBet);
        const int bet = aData.currentBet;


        int guess = 0;
        while (true)
        {
            system("cls");
            std::cout << "\nGissa summan (2-12): ";
            if (std::cin >> guess && guess >= 2 && guess <= 12)
            {
                break;
            }
            std::cout << "Skriv ett nummer mellan 2 och 12.\n";
            functions::Enter();
        }

        const int numberA = functions::GetRndInt();
        const int numberB = functions::GetRndInt();
        const int sum = numberA + numberB;

        aData.balance -= bet;
        int winnings = -bet;

        std::cout << "Du fick " << numberA << " och " << numberB << " = " << sum << "\n";

        if (guess == sum)
        {
            winnings = bet;
            aData.balance += (bet * Values::globalNormalPayout);
            std::cout << "Bra gissat " << aPlayerName << ", du vann!\n";
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
