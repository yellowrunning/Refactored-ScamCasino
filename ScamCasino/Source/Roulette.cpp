#include "Roulette.h"
#include "Functions.h"
#include "Values.h"
#include <iostream>
#include <random>
#include <array>

namespace Casino
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

    Roulette::Roulette(int aMinBet, int aMaxBet)
        : myMinBet(aMinBet)
        , myMaxBet(aMaxBet)
        , myProfit(0)
    {

    }

    int Roulette::GetProfit() const
    {
        return myProfit;
    }

    void Roulette::Play(GameData& aData, const char* aPlayerName)
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
            std::cout << "V\x84lkommen till Roulette, " << aPlayerName << "!";
            std::cout << "\nSaldo: " << aData.balance << "kr\n\n";
            std::cout << "=== REGLER ===\n";
            std::cout << "Detta \x84r det du kan satsa p\x86:\n";
            std::cout << "1. Straight (Gissa exakt nummer 0-36) Utbetalning: 36x\n";
            std::cout << "2. Red/Black (Red eller Black) Utbetalning: 2x\n";
            std::cout << "3. Odd/Even (Udda eller J\x84mnt) Utbetalning: 2x\n";
            std::cout << "4. Column Bet (Kolumn 1, 2 eller 3) Utbetalning: 3x\n";
            std::cout << "Om kulan landar p\x86 0 vinner du bara om du satsade p\x86 0!\n";

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
            std::cout << "3. L\x84mna bord\n\n> ";

            if (std::cin >> input && input >= 1 && input <= 3)
            {
                Choice choice = static_cast<Choice>(input);

                switch (choice)
                {
                case Choice::Instructions:
                {
                    system("cls");
                    std::cout << "===== Roulette =====\n";
                    std::cout << "Detta \x84r det du kan satsa p\x86:\n";
                    std::cout << "1. Straight (Gissa exakt nummer 0-36) Utbetalning: 36x\n";
                    std::cout << "2. Red/Black (Red eller Black) Utbetalning: 2x\n";
                    std::cout << "3. Odd/Even (Udda eller J\x84mnt) Utbetalning: 2x\n";
                    std::cout << "4. Column Bet (Kolumn 1, 2 eller 3) Utbetalning: 3x\n";
                    std::cout << "Om kulan landar p\x86 0 vinner du bara om du satsade p\x86 0!\n";
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

        int betChoice = 0;
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
        int guess = 0;

        switch (type)
        {
        case BetType::Straight:
        {
            while (true)
            {
                system("cls");
                std::cout << "V\x84lj ett nummer att satsa p\x86 (0-36):\n> ";
                if (std::cin >> guess && guess >= 0 && guess <= 36) break;
                std::cout << "Ogiltigt nummer! M\x86ste vara mellan 0 och 36.\n";
                functions::Enter();
            }
            break;
        }
        case BetType::RedBlack:
        {
            while (true)
            {
                system("cls");
                std::cout << "V\x84lj f\x84rg:\n1. Red\n2. Black\n> ";
                if (std::cin >> guess && (guess == 1 || guess == 2)) break;
                std::cout << "Skriv bara 1 eller 2.\n";
                functions::Enter();
            }
            break;
        }
        case BetType::OddEven:
        {
            while (true)
            {
                system("cls");
                std::cout << "V\x84lj:\n1. Udda\n2. J\x84mnt\n> ";
                if (std::cin >> guess && (guess == 1 || guess == 2)) break;
                std::cout << "Skriv bara 1 eller 2.\n";
                functions::Enter();
            }
            break;
        }
        case BetType::Column:
        {
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
        }

        std::random_device seed;
        std::mt19937 rndEngine(seed());
        std::uniform_int_distribution<int> rouletteWheel(0, 36);
        const int winningNumber = rouletteWheel(rndEngine);

        aData.balance -= bet;
        int winnings = -bet;
        bool won = false;

        switch (type)
        {
        case BetType::Straight:
        {
            if (guess == winningNumber)
            {
                won = true;
                winnings = bet * 35;
                aData.balance += (bet * 36);
            }
            break;
        }
        case BetType::RedBlack:
        {
            if (winningNumber != 0)
            {
                bool winningIsRed = Red(winningNumber);
                if ((guess == 1 && winningIsRed) || (guess == 2 && !winningIsRed))
                {
                    won = true;
                    winnings = bet;
                    aData.balance += (bet * Values::globalNormalPayout);
                }
            }
            break;
        }
        case BetType::OddEven:
        {
            if (winningNumber != 0)
            {
                bool winningIsOdd = (winningNumber % 2 != 0);
                if ((guess == 1 && winningIsOdd) || (guess == 2 && !winningIsOdd))
                {
                    won = true;
                    winnings = bet;
                    aData.balance += (bet * Values::globalNormalPayout);
                }
            }
            break;
        }
        case BetType::Column:
        {
            if (winningNumber != 0)
            {
                if (guess == GetColumn(winningNumber))
                {
                    won = true;
                    winnings = bet * 2;
                    aData.balance += (bet * 3);
                }
            }
            break;
        }
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