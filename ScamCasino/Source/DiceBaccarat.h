#pragma once
#include "GameData.h"

namespace Casino
{
	class DiceBaccarat
	{
	public:
		DiceBaccarat(int aMinBet, int aMaxBet);

		void Play(GameData& aData, const char* aPlayerName);

		int GetProfit() const;

	private:
		int myMinBet;
		int myMaxBet;
		int myProfit;
	};
}