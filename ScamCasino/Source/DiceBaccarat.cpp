#include "DiceBaccarat.h"
#include "Functions.h"
#include "Values.h"
#include <iostream>

namespace Casino
{
    DiceBaccarat::DiceBaccarat(int aMinBet, int aMaxBet)
        : myMinBet(aMinBet)
        , myMaxBet(aMaxBet)
        , myProfit(0)
    {

    }

    int DiceBaccarat::GetProfit() const
    {
        return myProfit;
    }

    void DiceBaccarat::Play(GameData& aData, const char* aPlayerName)
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
            std::cout << "V\x84lkommen till DiceBaccarat, " << aPlayerName << "!";
            std::cout << "\nSaldo: " << aData.balance << "kr\n\n";
            std::cout << "=== REGLER ===\n";
            std::cout << "Det kommer att finnas tv\x86 spelare: Player // Banken.";
            std::cout << "\nDu kan satsa p\x86 Player // Banken // Lika.";
            std::cout << "\nDen som f\x86r h\x94gst sammanlagda nummer vinner!\nOm det blir lika vinner du bara om du satsade p\x86 lika.";
            std::cout << "\n\nUtbetalning: 2x p\x86 en spelare // 10x p\x86 lika!!!\n";

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

                    std::cout << "Det kommer att finnas tv\x86 spelare: Player // Banken.";
                    std::cout << "\nDu kan satsa p\x86 Player // Banken // Lika.";
                    std::cout << "\nDen som f\x86r h\x94gst sammanlagda nummer vinner!\nOm det blir lika vinner du bara om du satsade p\x86 lika.";
                    std::cout << "\n\nUtbetalning: 2x p\x86 en spelare // 10x p\x86 lika!!!\n";

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
            std::cout << "\nSatsning:\n\n";
            std::cout << "1. Player (2x)\n";
            std::cout << "2. Banken (2x)\n";
            std::cout << "3. Lika (10x)\n> ";

            if (std::cin >> guess && guess >= 1 && guess <= 3)
            {
                break;
            }
            std::cout << "Du kan bara gissa p\x86 1, 2 eller 3.\n";
            functions::Enter();
        }

        const BaccaratBet choice = static_cast<BaccaratBet>(guess);

        const int playerA = functions::GetRndInt();
        const int playerB = functions::GetRndInt();
        const int bankerA = functions::GetRndInt();
        const int bankerB = functions::GetRndInt();

        const int playerTotal = playerA + playerB;
        const int bankerTotal = bankerA + bankerB;

        BaccaratBet winner = BaccaratBet::Tie;

        if (playerTotal > bankerTotal)
        {
            winner = BaccaratBet::Player;
        }
        else if (bankerTotal > playerTotal)
        {
            winner = BaccaratBet::Banker;
        }

        system("cls");
        aData.balance -= bet;
        int winnings = -bet;

        std::cout << "Player fick " << playerA << " + " << playerB
            << " = " << playerTotal << "\n";
        std::cout << "Banken fick " << bankerA << " + " << bankerB
            << " = " << bankerTotal << "\n\n";

        if (choice == winner)
        {
            if (winner == BaccaratBet::Tie)
            {
                winnings = bet * (Values::globalBaccaratTiePayout - 1);
                aData.balance += bet * Values::globalBaccaratTiePayout;
            }
            else
            {
                winnings = bet;
                aData.balance += bet * Values::globalNormalPayout;
            }

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