#pragma once
#include <string>

#include "Character.h"
#include "Player.h"

//전방선언 필요?

class BossMonster :public Character
{
public:
	BossMonster();
	// 소멸자 해야하나?
	
	void attack(Character* enemy) override;

	void takeDamage(int amount) override;

	void printStatus() override;
	
	void death() override;

	void attackPattern4(Player* player);

	void attackPattern4CheckAnswer(Player* player);

	int determinePhase(int currentHP);

	// getters
	int getCorrectAnswer();
	int getPhase();
	bool getIsInvincible();

	// setters

private:
	bool isInvincible = false;
	int phase = 1;
	int correctAnswer = 0;
};