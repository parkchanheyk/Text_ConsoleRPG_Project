#pragma once
#include <string>
class Enemy; // Enemy 클래스에 대한 전방 선언

class Character
{
public:
	Character(std::string name);

	virtual void attack(Enemy* enemy) = 0;
	virtual void death();
	virtual void printStatus();

	// getter 함수
	std::string getName();
	int getLevel();
	int getMaxHP();
	int getCurrentHP();
	int getATK();
	int getSpeed();

	int getExp();

	// setter 함수

	void setMaxHP(int MaxHP);
	void setCurrentHP(int currentHP);
	void setAttack(int ATK);
	void setExp(int Exp);
	void setSpeed(int speed);

	void setLevel(int level);

protected:

	std::string name; 
	int maxHP; 
	int currentHP; 
	int level;
	int ATK; 
	int exp; 
	int speed;
};

