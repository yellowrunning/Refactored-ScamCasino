#include "Roulette.h"
#include "Functions.h"
#include "Values.h"
#include "Statistics.h"
#include <iostream>
#include <random>
#include <array>


namespace Casino::roulette
{
    namespace
    {
        bool Red(int number)
        {
            if (number == 0) return false;

            constexpr std::array<int, 18> redNumbers = {
                1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36
            };

            for (int red : redNumbers)
            {
                if (number == red) return true;
            }
            return false;
        }

        int GetColumn(int number)
        {
            if (number == 0) return 0;
            return ((number - 1) % 3) + 1;
        }
    }

    void Play(GameData& data, StatisticsData& statistics)
    {
        functions::Money(statistics, Game::Roulette);

        if (functions::CheckTooMuch(statistics, Game::Roulette))
        {
            return;
        }

        bool playGame{ false };

        while (!playGame)
        {
            int input{};
            std::cout << "1. Instruktioner\n";
            std::cout << "2. Spela\n";
            std::cout << "3. L\x84mna bord\n\n> ";

            if (std::cin >> input && input >= 1 && input <= 3)
            {
                Choice choice = static_cast<Choice>(input);

                switch (choice)
                {
                case Choice::Instructions:
                    system("cls");
                    std::cout << "===== Roulette =====\n";
                    std::cout << "Detta \x84r det du kan satsa p\x86:\n";
                    std::cout << "1. Straight (Gissa exakt nummer 0-36) Utbetalning: 36x\n";
                    std::cout << "2. Red/Black (Red eller Black) Utbetalning: 2x\n";
                    std::cout << "3. Odd/Even (Udda eller J\x84mnt) Utbetalning: 2x\n";
                    std::cout << "4. Column Bet (Kolumn 1, 2 eller 3) Utbetalning: 3x\n";
                    std::cout << "Om kulan landar p\x86 0 vinner du bara om du satsade p\x86 0!\n";
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
                std::cout << "Skriv bara 1, 2 eller 3.\n";
                functions::Enter();
                system("cls");
            }
        }

        functions::PlaceBet(data);
        const int bet = data.currentBet;

        int betChoice{};
        while (true)
        {
            system("cls");
            std::cout << "V\x84lj vad du vill satsa p\x86:\n\n";
            std::cout << "1. Straight (Ett specifikt nummer)\n";
            std::cout << "2. RedBlack\n";
            std::cout << "3. Udda / J\x84mnt\n";
            std::cout << "4. Kolumn\n> ";

            if (std::cin >> betChoice && betChoice >= 1 && betChoice <= 4)
            {
                break;
            }
            std::cout << "\nV\x84lj ett nummer mellan 1 och 4.\n";
            functions::Enter();
        }

        const BetType type = static_cast<BetType>(betChoice);
        int guess{};

        switch (type)
        {
        case BetType::Straight:
            while (true)
            {
                system("cls");
                std::cout << "V\x84lj ett nummer att satsa p\x86 (0-36):\n> ";
                if (std::cin >> guess && guess >= 0 && guess <= 36) break;
                std::cout << "Ogiltigt nummer! M\x86ste vara mellan 0 och 36.\n";
                functions::Enter();
            }
            break;

        case BetType::RedBlack:
            while (true)
            {
                system("cls");
                std::cout << "V\x84lj f\x84rg:\n1. Red\n2. Black\n> ";
                if (std::cin >> guess && (guess == 1 || guess == 2)) break;
                std::cout << "Skriv bara 1 eller 2.\n";
                functions::Enter();
            }
            break;

        case BetType::OddEven:
            while (true)
            {
                system("cls");
                std::cout << "V\x84lj:\n1. Udda\n2. J\x84mnt\n> ";
                if (std::cin >> guess && (guess == 1 || guess == 2)) break;
                std::cout << "Skriv bara 1 eller 2.\n";
                functions::Enter();
            }
            break;

        case BetType::Column:
            while (true)
            {
                system("cls");
                std::cout << "V\x84lj kolumn (1, 2 eller 3):\n> ";
                if (std::cin >> guess && guess >= 1 && guess <= 3) break;
                std::cout << "Skriv bara 1, 2 eller 3.\n";
                functions::Enter();
            }
            break;
        }

        std::random_device seed;
        std::mt19937 rndEngine(seed());
        std::uniform_int_distribution<int> rouletteWheel(0, 36);
        const int winningNumber = rouletteWheel(rndEngine);

        data.balance -= bet;
        int winnings = -bet;
        bool won{ false };

        switch (type)
        {
        case BetType::Straight:
            if (guess == winningNumber)
            {
                won = true;
                winnings = bet * 35;
                data.balance += (bet * 36);
            }
            break;

        case BetType::RedBlack:
            if (winningNumber != 0)
            {
                bool winningIsRed = Red(winningNumber);
                if ((guess == 1 && winningIsRed) || (guess == 2 && !winningIsRed))
                {
                    won = true;
                    winnings = bet;
                    data.balance += (bet * Values::globalnormalPayout);
                }
            }
            break;

        case BetType::OddEven:
            if (winningNumber != 0)
            {
                bool winningIsOdd = (winningNumber % 2 != 0);
                if ((guess == 1 && winningIsOdd) || (guess == 2 && !winningIsOdd))
                {
                    won = true;
                    winnings = bet;
                    data.balance += (bet * Values::globalnormalPayout);
                }
            }
            break;

        case BetType::Column:
            if (winningNumber != 0)
            {
                if (guess == GetColumn(winningNumber))
                {
                    won = true;
                    winnings = bet * 2;
                    data.balance += (bet * 3);
                }
            }
            break;
        }

        system("cls");
        std::cout << "Kulan stannade p\x86: " << winningNumber;
        if (winningNumber == 0)
        {
            std::cout << " (Green)\n\n";
        }
        else if (Red(winningNumber))
        {
            std::cout << " (Red)\n\n";
        }
        else
        {
            std::cout << " (Svart)\n\n";
        }

        if (won)
        {
            std::cout << "Du vann!\n";
        }
        else
        {
            std::cout << "Du f\x94rlorade.\n";
        }

        functions::AddStats(statistics, Game::Roulette, bet, winnings);
        std::cout << "Kontobalans: " << data.balance << "kr\n";
        functions::CheckMoney(data);
        statistics::Show(statistics, data);
    }
}
