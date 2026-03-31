#include "Money.h"

Money::Money(size_t startMoney, size_t max)
	: maxMoney(max)
{
	currentMoney = (startMoney > maxMoney) ? maxMoney : startMoney;
}

bool Money::canAfford(size_t moneyAmount) const
{
	return currentMoney >= moneyAmount;
}

bool Money::spendMoney(size_t moneyAmount)
{
	if (!canAfford(moneyAmount))
		return false;

	currentMoney -= moneyAmount;
	return true;
}

bool Money::addMoney(size_t moneyAmount)
{
	currentMoney += moneyAmount;
	if (currentMoney > maxMoney)
	{
		currentMoney = maxMoney;
		return false;	// 돈 최대 소지량 초과
	}
	else
	{
		return true;	// 정상
	}
}

size_t Money::getCurrentMoney() const
{
	return currentMoney;
}

size_t Money::getMaxMoney() const
{
	return maxMoney;
}

void Money::increaseMaxMoney(size_t amount)
{
	maxMoney += amount;
}