#pragma once
#pragma once
#include "Character.h"
#include <string>
#include <random>
#include <iostream>

class Monster : public Character
{
public:
	Monster(std::string name);
	void attack(Character* enemy) override ;
	void takeDamage(int amount) override;
	void death() override final;
	void printStatus() override final;

	virtual ~Monster() {} // 업캐스팅한 객체 소멸할때 필요

	// getter
	// 몬스터는 따로 인벤/돈 관리를 하지않고 단순하게 아이템/돈을 가지고 있고, 죽으면 드랍
	std::string getItems() const;
	int getMoney() const;

protected:
	std::string items;
	int money;
	std::string asciiArt;
};


// Monster를 상속받은 실제로 생성할 몬스터 클래스들 정의
//
// 첫번째 몬스터: 뚱냥이
class Chonkycat : public Monster
{
public:
	Chonkycat();
	~Chonkycat() {}
};

// 두번째 몬스터: 불독
class Bulldog : public Monster
{
public:
	Bulldog();
	~Bulldog() {}
};

// 세번째 몬스터: 고스트
class Ghost : public Monster
{
public:
	Ghost();
	~Ghost() {}
};

// 네번째 몬스터: 골렘
class Golem : public Monster
{
public:
	Golem();
	~Golem() {}
};

// 럭키 몬스터(랜덤 몬스터)
// HP, 공격력 등 스탯 랜덤(뚱냥이보다 약할수도 골렘보다 셀 수도 있음)
// 죽었을때 플레이어에게 주는 경험치, 돈도 랜덤
class LuckyMonster : public Monster
{
public:
	LuckyMonster();
	~LuckyMonster() {}
};