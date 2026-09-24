#pragma once
#include "GameData.h"
#include "Dice.h"
#include "CoinFlip.h"
#include "DiceBaccarat.h"
#include "OddEven.h"
#include "Roulette.h"

namespace Casino::statistics
{
    void Show
    (
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
    );
}
