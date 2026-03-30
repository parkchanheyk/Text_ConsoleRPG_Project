#include "Monster.h"

// Monster 몬스터 
Monster::Monster(std::string name) : Character(name)
{
	this->name = name;
}

void Monster::attack(std::shared_ptr<Character> enemy)
{
	std::cout << this->name << "이(가)" << enemy->getName() << "을(를) 공격했다!" << std::endl;
	this->takeDamage(enemy->getATK());
}

void Monster::takeDamage(int amount)
{
	this->setCurrentHP(this->getCurrentHP() - amount);
}

void Monster::death()
{
	std::cout << this->name << "이(가) 쓰러졌다!" << std::endl;
}

void Monster::printStatus()
{
	std::cout << "몬스터의 이름: " << name << std::endl;
	std::cout << "몬스터의 레벨: " << level << std::endl;
	std::cout << "몬스터의 최대 HP: " << maxHP << std::endl;
	std::cout << "몬스터의 현재 HP: " << currentHP << std::endl;
	std::cout << "몬스터의 공격력: " << ATK << std::endl;
	std::cout << "몬스터의 속도: " << speed << std::endl;
}

std::string Monster::getItems() const
{
	return this->items;
}

int Monster::getMoney() const
{

	return this->money;
}

// Monster를 상속받은 실제로 생성할 몬스터 클래스들 구현
// 멤버 변수들 값은 일단 임의로 설정한 상태
// Chonkycat 뚱냥이
Chonkycat::Chonkycat() : Monster("뚱냥이")
{
	this->maxHP = 100;
	this->currentHP = 100;
	this->ATK = 10;
	this->speed = 10;
	this->level = 1;
	this->exp = 10;
	this->items = "뚱냥이의 털뭉치";
	this->money = 100;
	this->asciiArt = R"(
      /\_/\
     ( o.o )
      > ^ <
     (  "  )
    )";
}



// Bulldog 불독
Bulldog::Bulldog() : Monster("불독")
{
	this->maxHP = 200;
	this->currentHP = 200;
	this->ATK = 20;
	this->speed = 15;
	this->level = 2;
	this->exp = 30;
	this->items = "불독의 턱살";
	this->money = 200;
	this->asciiArt = R"(
     / \---/ \
    (  O   O  )
     \   m   /  
     |       |
     |   _   |
     \__/ \__/
)";
}



// Ghost 고스트
Ghost::Ghost() : Monster("고스트")
{
	this->maxHP = 100;
	this->currentHP = 100;
	this->ATK = 50;
	this->speed = 50;
	this->level = 3;
	this->exp = 50;
	this->items = "고스트의 영혼";
	this->money = 500;
	this->asciiArt = R"(
          .--.
         (>  <)
         | ww |
         \    /
          `~~`
    )";
}



// Golem 골렘
Golem::Golem() : Monster("골렘")
{
	this->maxHP = 500;
	this->currentHP = 500;
	this->ATK = 100;
	this->speed = 1;
	this->level = 4;
	this->exp = 100;
	this->items = "골렘의 돌조각";
	this->money = 1000;
	this->asciiArt = R"(
     [|||||||]
    [|[ o o ]|]
    [|   ^   |]
     [||___||]
      /|   |\
    )";
}



// LuckyMonster 럭키 몬스터
LuckyMonster::LuckyMonster() : Monster("???")
{
	// 난수 생성
	std::random_device rd;
	std::mt19937 generate(rd());


	this->maxHP = std::uniform_int_distribution<int>(50, 500)(generate);
	this->currentHP = this->maxHP;
	this->ATK = std::uniform_int_distribution<int>(5, 100)(generate);
	this->speed = std::uniform_int_distribution<int>(1, 100)(generate);
	this->level = std::uniform_int_distribution<int>(1, 4)(generate);
	this->exp = std::uniform_int_distribution<int>(1, 200)(generate);
	this->items = "행운의 증표";
	this->money = std::uniform_int_distribution<int>(1, 5000)(generate);
	this->asciiArt = R"(
      .-------.
     /   $   /|
    .-------. |
    |  _ _  | /
    '-------'
)";
}