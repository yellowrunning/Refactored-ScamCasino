#pragma once
#include "GameData.h"

namespace Casino
{
	class OddEven
	{
	public:
		OddEven(int aMinBet, int aMaxBet);

		void Play(GameData& aData, const char* aPlayerName);

		int GetProfit() const;

	private:
		int myMinBet;
		int myMaxBet;
		int myProfit;
	};
}