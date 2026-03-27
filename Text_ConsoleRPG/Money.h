#pragma once

class Money
{
protected:
	size_t currentMoney;
	size_t maxMoney;

public:
	Money(size_t startMoney = 0, size_t maxM = 9999);

	bool canAfford(size_t moneyAmount) const;

	bool spendMoney(size_t moneyAmount);

	bool getMoney(size_t moneyAmount);

	size_t getCurrentMoney() const;

	size_t getMaxMoney() const;

	void increaseMaxMoney(size_t amount);
};