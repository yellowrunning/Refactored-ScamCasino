#include "CoinFlip.h"
#include "Functions.h"
#include "Values.h"
#include "Statistics.h"
#include <iostream>
#include <random>

namespace Casino::coinFlip
{
    void Play(GameData& data, StatisticsData& statistics)
    {
        functions::Money(statistics, Game::CoinFlip);

        if (functions::CheckTooMuch(statistics, Game::CoinFlip))
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

                    std::cout << "Du kommer flippa ett mynt.\n";
                    std::cout << "Myntet kan landa p\x86 krona eller klave.\n";
                    std::cout << "R\x84tt gissning ger 2x utbetalning!\n";

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
            std::cout << "\n1. Krona\n";
            std::cout << "2. Klave\n> ";

            if (std::cin >> guess && guess >= Values::coinMinimum && guess <= Values::coinMaximum)
            {
                break;
            }
            std::cout << "V\x84lj bara 1 eller 2.\n";
            functions::Enter();
            system("cls");
        }

        const CoinSide choice = static_cast<CoinSide>(guess);

        std::random_device seed;
        std::mt19937 rndEngine(seed());
        std::uniform_int_distribution<int> rndCoin(Values::coinMinimum, Values::coinMaximum);
        const CoinSide result = static_cast<CoinSide>(rndCoin(rndEngine));

        data.balance -= bet;
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
            data.balance += bet * Values::normalPayout;
            std::cout << "Du vann!\n";
        }
        else
        {
            std::cout << "Du f\x94rlorade.\n";
        }

        functions::AddStats(statistics, Game::CoinFlip, bet, winnings);
        std::cout << "Kontobalans: " << data.balance << "kr\n";
        functions::CheckMoney(data);
        statistics::Show(statistics, data);
    }
}
