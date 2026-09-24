#include "Functions.h"
#include "Values.h"
#include <iostream>
#include <random>

namespace Casino::functions
{
    int GetRndInt()
    {
        std::random_device seed;
        std::mt19937 rndEngine(seed());
        std::uniform_int_distribution<int> rndDist(1, Values::globalDiceSides);
        return rndDist(rndEngine);
    }

    void Enter()
    {
        std::cout << "\ntryck p\x86 enter f\x94r att forts\x84tta\n";
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cin.get();
    }

    int PlaceBet(GameData& aData, int aMinBet, int aMaxBet)
    {
        while (true)
        {
            system("cls");

            std::cout << "Satsa pengar (Gr\x84ns: " << aMinBet << "-" << aMaxBet << "kr):\n";
            std::cout << "Kontobalans: " << aData.balance << "kr\n> ";

            if (std::cin >> aData.currentBet &&
                aData.currentBet >= aMinBet &&
                aData.currentBet <= aMaxBet &&
                aData.currentBet <= aData.balance)
            {
                if (aData.currentBet == aData.balance)
                {
                    std::cout << "\nAll IN!!!\n";
                    functions::Enter();
                    system("cls");
                }
                return aData.currentBet;
            }
            std::cout << "\nSkriv en giltig summa.\n";
            Enter();
        }
    }
}