#include "DiceBaccarat.h"
#include "Functions.h"
#include "Values.h"
#include "Statistics.h"
#include <iostream>

namespace Casino::diceBaccarat
{
    void Play(GameData& data, StatisticsData& statistics)
    {
        functions::Money(statistics, Game::DiceBaccarat);

        if (functions::CheckTooMuch(statistics, Game::DiceBaccarat))
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

                    std::cout << "Det kommer att finnas tv\x86 spelare: Player // Banken.";
                    std::cout << "\nDu kan satsa p\x86 Player // Banken // Lika.";
                    std::cout << "\nDen som f\x86r h\x94gst sammanlagda nummer vinner!\nOm det blir lika vinner du bara om du satsade p\x86 lika.";
                    std::cout << "\n\nUtbetalning: 2x p\x86 en spelare // 10x p\x86 lika!!!\n";

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
            system("cls");
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
        data.balance -= bet;
        int winnings = -bet;

        std::cout << "Player fick " << playerA << " + " << playerB
                  << " = " << playerTotal << "\n";
        std::cout << "Banken fick " << bankerA << " + " << bankerB
                  << " = " << bankerTotal << "\n\n";

        if (choice == winner)
        {
            if (winner == BaccaratBet::Tie)
            {
                winnings = bet * (Values::globalbaccaratTiePayout - 1);
                data.balance += bet * Values::globalbaccaratTiePayout;
            }
            else
            {
                winnings = bet;
                data.balance += bet * Values::globalnormalPayout;
            }

            std::cout << "Du vann!\n";
        }
        else
        {
            std::cout << "Du f\x94rlorade.\n";
        }

        functions::AddStats(statistics, Game::DiceBaccarat, bet, winnings);
        std::cout << "Kontobalans: " << data.balance << "kr\n";
        functions::CheckMoney(data);
        statistics::Show(statistics, data);
    }
}
