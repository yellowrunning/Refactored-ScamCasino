#pragma once
#include "GameData.h"
#include "Dice.h"
#include "CoinFlip.h"
#include "DiceBaccarat.h"
#include "Roulette.h"
#include "OddEven.h"

namespace Casino
{
	class CasinoSystem
	{
	public:

		CasinoSystem();
		void Run();

	private:
		
		GameData myGameData;
		char myPlayerName[15];

		Dice myLowStakesDice;
		Dice myHighStakesDice;

		DiceBaccarat myLowStakesDiceBaccarat;
		DiceBaccarat myHighStakesDiceBaccarat;

		OddEven myLowStakesOddEven;
		OddEven myHighStakesOddEven;

		CoinFlip myLowStakesCoinFlip;
		CoinFlip myHighStakesCoinFlip;

		Roulette myLowStakesRoulette;
		Roulette myHighStakesRoulette;
	};
}