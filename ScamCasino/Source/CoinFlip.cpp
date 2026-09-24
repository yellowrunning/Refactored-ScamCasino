#include "CoinFlip.h"
#include "Functions.h"
#include "Values.h"
#include <iostream>
#include <random>

namespace Casino
{
    CoinFlip::CoinFlip(int aMinBet, int aMaxBet)
        : myMinBet(aMinBet)
        , myMaxBet(aMaxBet)
        , myProfit(0)
    {

    }

    int CoinFlip::GetProfit() const
    {
        return myProfit;
    }

    void CoinFlip::Play(GameData& aData, const char* aPlayerName)
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
            std::cout << "V\x84lkommen till Coinflip, " << aPlayerName << "!";
            std::cout << "\nSaldo: " << aData.balance << "kr\n\n";
            std::cout << "=== REGLER ===\n";
            std::cout << "Du kommer flippa ett mynt.\n";
            std::cout << "Myntet kan landa p\x86 krona eller klave.\n";
            std::cout << "R\x84tt gissning ger 2x utbetalning!\n";

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

                    std::cout << "Du kommer flippa ett mynt.\n";
                    std::cout << "Myntet kan landa p\x86 krona eller klave.\n";
                    std::cout << "R\x84tt gissning ger 2x utbetalning!\n";

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
            std::cout << "\n1. Krona\n";
            std::cout << "2. Klave\n> ";

            if (std::cin >> guess && guess >= 1 && guess <= 2)
            {
                break;
            }
            std::cout << "V\x84lj bara 1 eller 2.\n";
            functions::Enter();
        }

        const CoinSide choice = static_cast<CoinSide>(guess);

        std::random_device seed;
        std::mt19937 rndEngine(seed());
        std::uniform_int_distribution<int> rndCoin(1, 2);
        const CoinSide result = static_cast<CoinSide>(rndCoin(rndEngine));

        aData.balance -= bet;
        int winnings = -bet;

        if (result == CoinSide::Heads)
        {
            std::cout << "\nMyntet blev Krona!\n";
        }
        else
        {
            std::cout << "\nMyntet blev Klave!\n";
        }

        if (choice == result)
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