#include "Character.h"
#include <iostream>

Character::Character(std::string name) 
{
	this->name = name;
}

void Character::attack(Enemy* enemy)
{
	std::cout <<"공격합니다!" << std::endl;
}
void Character::death()
{
	std::cout << "캐릭터가 사망했습니다." << std::endl;
}
void Character::printStatus()
{
	std::cout << "캐릭터 이름: " << name << std::endl;
	std::cout << "레벨: " << level << std::endl;
	std::cout << "최대 HP: " << maxHP << std::endl;
	std::cout << "현재 HP: " << currentHP << std::endl;
	std::cout << "공격력: " << ATK << std::endl;
	std::cout << "속도: " << speed << std::endl;
}

// getter 함수
std::string Character:: getName()
{
	return name;
}
int Character::getLevel()
{
	return level;
}
int Character::getMaxHP()
{
	return maxHP;
}
int Character::getCurrentHP()
{
	return currentHP;
}
int Character::getATK()
{
	return ATK;
}
int Character::getSpeed()
{
	return speed;
}
int Character::getExp()
{
	return exp;
}

// setter 함수

void Character::setMaxHP(int MaxHP)
{
	this->maxHP = MaxHP;
}
void Character::setCurrentHP(int currentHP)
{
	this->currentHP = currentHP;
}
void Character::setAttack(int ATK)
{
	this->ATK = ATK;
}
void Character::setExp(int Exp)
{
	this->exp = Exp;
}
void Character::setSpeed(int speed)
{
	this->speed = speed;
}
void Character::setLevel(int level)
{
	this->level = level;
}