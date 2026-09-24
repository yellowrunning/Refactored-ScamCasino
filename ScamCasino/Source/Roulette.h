#pragma once
#include "GameData.h"

namespace Casino
{
    enum class BetType
    {
        Straight = 1,
        RedBlack = 2,
        OddEven = 3,
        Column = 4
    };
}

namespace Casino
{
	class Roulette
	{
	public:
		Roulette(int aMinBet, int aMaxBet);

		void Play(GameData& aData, const char* aPlayerName);

		int GetProfit() const;

	private:
		int myMinBet;
		int myMaxBet;
		int myProfit;
	};
}