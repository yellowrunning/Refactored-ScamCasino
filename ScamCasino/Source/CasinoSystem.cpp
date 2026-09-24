#include "GameData.h"
#include "Values.h"
#include "Dice.h"
#include "OddEven.h"
#include "DiceBaccarat.h"
#include "CoinFlip.h"
#include "Roulette.h"
#include "Statistics.h"
#include <iostream>
#include "Functions.h"
#include "CasinoSystem.h"

namespace Casino
{
	CasinoSystem::CasinoSystem()
		: myGameData { Values::globalStartingMoney, 0 }
		, myLowStakesDice(1, 150)
		, myHighStakesDice(151, 500)
		, myLowStakesDiceBaccarat(1, 150)
		, myHighStakesDiceBaccarat(151, 500)
		, myLowStakesOddEven(1, 150)
		, myHighStakesOddEven(151, 500)
		, myLowStakesCoinFlip(1, 150)
		, myHighStakesCoinFlip(151, 500)
		, myLowStakesRoulette(1, 150)
		, myHighStakesRoulette(151, 500)
	{

		myPlayerName[0] = '\0';
	}

	void CasinoSystem::Run()
	{
		bool validName = false;
		while (!validName)
		{
			std::cout << "V\x84lkommen till ScamCasino!\n";
			std::cout << "Ange ditt namn (2-14 bokst\x86ver):\n> ";

			std::cin.get(myPlayerName, 15);

			if (std::cin.fail())
			{
				std::cin.clear();
			}

			while (std::cin.get() != '\n')
			{
				continue;
			}

			int length = 0;
			while (myPlayerName[length] != '\0')
			{
				length++;
			}

			if (length < 2 || length > 16)
			{
				system("cls");
				std::cout << "Namnet m\x86ste vara mellan 2 och 14 tecken.\n\n";
				continue;
			}

			bool lettersOnly = true;
			for (int i = 0; i < length; ++i)
			{
				char c = myPlayerName[i];

				bool letters = (c >= 'A' && c <= 'Z' || c >= 'a' && c <= 'z');

				if (!letters)
				{
					lettersOnly = false;
					break;
				}
			}
			if (!lettersOnly)
			{
				system("cls");
				std::cout << "Namnet f\x86r bara inneh\x86lla bokst\x86ver.\n\n";
				continue;
			}
			validName = true;
		}
        system("cls");
        std::cout << "V\x84lkommen in, " << myPlayerName << "!\n";
        functions::Enter();

        bool isRunning = true;
        while (isRunning)
        {
            system("cls");
            std::cout << "===== SCAMCASINO LOBBY =====\n";
            std::cout << "Spelare: " << myPlayerName << " | Saldo: " << myGameData.balance << "kr\n\n";
            std::cout << "1. Dice (Low Stakes)\n";
            std::cout << "2. Dice (High Stakes)\n";
            std::cout << "3. Dice Baccarat (Low Stakes)\n";
            std::cout << "4. Dice Baccarat (High Stakes)\n";
            std::cout << "5. Udda/J\x84mnt (Low Stakes)\n";
            std::cout << "6. Udda/J\x84mnt (High Stakes)\n";
            std::cout << "7. Coinflip (Low Stakes)\n";
            std::cout << "8. Coinflip (High Stakes)\n";
            std::cout << "9. Roulette (Low Stakes)\n";
            std::cout << "10. Roulette (High Stakes)\n";
            std::cout << "11. Statistik\n";
            std::cout << "12. Avsluta spelet\n\n> ";

            int selection = 0;
            if (std::cin >> selection)
            {
                switch (selection)
                {
                case 1:
                {
                    myLowStakesDice.Play(myGameData, myPlayerName);
                    break;
                }
                case 2:
                {
                    myHighStakesDice.Play(myGameData, myPlayerName);
                    break;
                }
                case 3:
                {
                    myLowStakesDiceBaccarat.Play(myGameData, myPlayerName);
                    break;
                }
                case 4:
                {
                    myHighStakesDiceBaccarat.Play(myGameData, myPlayerName);
                    break;
                }
                case 5:
                {
                    myLowStakesOddEven.Play(myGameData, myPlayerName);
                    break;
                }
                case 6:
                {
                    myHighStakesOddEven.Play(myGameData, myPlayerName);
                    break;
                }
                case 7:
                {
                    myLowStakesCoinFlip.Play(myGameData, myPlayerName);
                    break;
                }
                case 8:
                {
                    myHighStakesCoinFlip.Play(myGameData, myPlayerName);
                    break;
                }
                case 9:
                {
                    myLowStakesRoulette.Play(myGameData, myPlayerName);
                    break;
                }
                case 10:
                {
                    myHighStakesRoulette.Play(myGameData, myPlayerName);
                    break;
                }
                case 11:
                {
                    statistics::Show
                    (
                        myGameData, myPlayerName,
                        myLowStakesDice, myHighStakesDice,
                        myLowStakesCoinFlip, myHighStakesCoinFlip,
                        myLowStakesDiceBaccarat, myHighStakesDiceBaccarat,
                        myLowStakesOddEven, myHighStakesOddEven,
                        myLowStakesRoulette, myHighStakesRoulette
                    );
                    break;
                }
                case 12:
                {
                    isRunning = false;
                    break;
                }
                default:
                {
                    std::cout << "Felaktigt val\n";
                    functions::Enter();
                    break;
                }
                }
            }
            else
            {
                std::cout << "Skriv bara siffror!\n";
                functions::Enter();
            }

            if (myGameData.balance <= 0)
            {
                system("cls");
                std::cout << "Du har inga pengar kvar, " << myPlayerName << "GTFO\n";
                functions::Enter();
                isRunning = false;
            }
        }
    }
}
