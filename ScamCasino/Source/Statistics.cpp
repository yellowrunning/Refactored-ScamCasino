#include "Statistics.h"
#include "Functions.h"
#include "GameData.h"    
#include "Dice.h"       
#include "CoinFlip.h"   
#include "DiceBaccarat.h"  
#include "OddEven.h"      
#include "Roulette.h"     
#include <iostream>


namespace Casino::statistics
{
    void Show(
        const GameData& aData,
        const char* aPlayerName,
        const Dice& aLowDice,
        const Dice& aHighDice,
        const CoinFlip& aLowCoin,
        const CoinFlip& aHighCoin,
        const DiceBaccarat& aLowBaccarat,
        const DiceBaccarat& aHighBaccarat,
        const OddEven& aLowOddEven,
        const OddEven& aHighOddEven,
        const Roulette& aLowRoulette,
        const Roulette& aHighRoulette
    )
    {
        (void)aPlayerName;

        std::cout << "\n===== Statistik " << aPlayerName << " =====\n";

        const int totalDiceProfit = aLowDice.GetProfit() + aHighDice.GetProfit();
        const int totalBaccaratProfit = aLowBaccarat.GetProfit() + aHighBaccarat.GetProfit();
        const int totalOddEvenProfit = aLowOddEven.GetProfit() + aHighOddEven.GetProfit();
        const int totalCoinProfit = aLowCoin.GetProfit() + aHighCoin.GetProfit();
        const int totalRouletteProfit = aLowRoulette.GetProfit() + aHighRoulette.GetProfit();

        std::cout << "\nPengar vid varje bord:\n";
        std::cout << "Dice: " << totalDiceProfit << "kr\n";
        std::cout << "Udda/Ja\x84mnt: " << totalOddEvenProfit << "kr\n";
        std::cout << "Dice Baccarat: " << totalBaccaratProfit << "kr\n";
        std::cout << "Coinflip: " << totalCoinProfit << "kr\n";
        std::cout << "Roulette: " << totalRouletteProfit << "kr\n";
        std::cout << "\nKontobalans: " << aData.balance << "kr\n";

        functions::Enter();
    }
}
