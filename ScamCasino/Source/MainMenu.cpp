#include "MainMenu.h"
#include "GameData.h"
#include "Constants.h"
#include "Dice.h"
#include "OddEven.h"
#include "DiceBaccarat.h"
#include "CoinFlip.h"
#include "Statistics.h"
#include <iostream>

namespace casino::menu
{
    Game ChooseGame()
    {
        system("cls");
        int choice{};
        while (true)
        {
            std::cout << "\n===== Scamkasino =====\n";
            std::cout << "1. Dice\n";
            std::cout << "2. Udda/Ja\x84mnt\n";
            std::cout << "3. Dice Baccarat\n";
            std::cout << "4. Coinflip\n";
            std::cout << "5. Statistik\n";
            std::cout << "6. Avsluta\n> ";

            if (std::cin >> choice && choice >= 1 && choice <= 6)
            {
                return static_cast<Game>(choice);
            }

            std::cin.clear();
            std::cin.ignore(10000, '\n');
            std::cout << "V\x84lj ett nummer mellan 1 och 6.\n";
        }
    }

    void Run()
    {
        GameData data{};
        StatisticsData statistics{};
        data.balance = constants::startingMoney;

        bool running = true;

        while (running && data.balance > 0)
        {
            const Game game = ChooseGame();

            switch (game)
            {
            case Game::Dice:
                dice::Play(data, statistics);
                break;
            case Game::OddEven:
                oddEven::Play(data, statistics);
                break;
            case Game::DiceBaccarat:
                diceBaccarat::Play(data, statistics);
                break;
            case Game::CoinFlip:
                coinFlip::Play(data, statistics);
                break;
            case Game::Statistics:
                statistics::Show(statistics, data);
                break;
            case Game::Exit:
                running = false;
                break;
            }
        }

        std::cout << "\nSpelet st\x84ngs ner.\n";
        std::cout << "Kontobalans: " << data.balance << "kr\n";
    }
}
