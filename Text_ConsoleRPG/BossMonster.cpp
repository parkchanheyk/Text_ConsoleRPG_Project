#include <iostream>
#include <string>
#include <conio.h>

#include "BossMonster.h"
#include "Player.h"
#include "windows.h"

BossMonster::BossMonster() :Character("[초대형 울트라 찍찍 들쥐]")
{
	// 모든 수치는 공유 후 조율할 예정
	maxHP = 999;
	currentHP = maxHP;
	level = 17;
	ATK = 26;
	exp = 1000;
	speed = 60;
}

int BossMonster::determinePhase(int currentHP)
{
	if (currentHP > (maxHP * 2 / 3))
	{
		phase = 1;
	}
	else if (currentHP > (maxHP / 3))
	{
		phase = 2;
	}
	else
	{
		phase = 3;
	}

	return phase;
}

void BossMonster::attack(std::shared_ptr<Character> enemy)
{
	srand(time(NULL)); // 랜덤 시드 생성

	int pattern = 0;
	bool cheatMode = false;

	isInvincible = false;

	switch (determinePhase(currentHP))
	{
	case 1:
		pattern = rand() % 4 + 1; // 1~4 랜덤
		break;
	case 2:
		pattern = rand() % 4 + 3; // 3~6 랜덤
		break;
	case 3:
		pattern = rand() % 4 + 4; // 4~7 랜덤
		break;
	}

	std::cout << '\n';
	Sleep(500);

	switch (pattern)
	{
	case 1:
		std::cout << name << "가 [꼬리 휘두르기]를 시전했습니다!\n\n";
		enemy->takeDamage(ATK);
		break;
	case 2:
		std::cout << name << "가 [산성 침 뱉기]를 시전했습니다!\n\n";
		enemy->takeDamage(ATK * 0.7);
		break;
	case 3:
		std::cout << name << "가 [고양이 잡는 쥐]를 시전했습니다!\n";
		std::cout << "손톱이 날아옵니다!\n\n";
		enemy->takeDamage(ATK * 1.7);
		break;
	case 4:
	{   
		attackPattern4(enemy);
		break;
	}
	case 5:
		std::cout << name << "가 [썩은 치즈]를 먹었습니다!\n";
		if (cheatMode = false)
		{
			currentHP += 250;
			if (currentHP > maxHP)
			{
				currentHP = maxHP;
			}
			std::cout << name << "의 체력이 250 회복되었습니다.\n\n";
		}
		else
		{
			currentHP += 2;
			if (currentHP > maxHP)
			{
				currentHP = maxHP;
			}
			std::cout << name << "의 체력이 2 회복되었습니다.\n\n";
		}
		
		break;
	case 6:
		isInvincible = true;
		std::cout << name << "가 [시궁창의 축복]을 사용했습니다!\n";
		std::cout << name << "를 향한 다음 공격이 1회 무효화됩니다.\n\n";
		// Player쪽에서 만약 isInvincible = true;면 대미지 0을 넣는 거로
		break;
	case 7:
		std::cout << name << "가 [들쥐의 분노]를 시전했습니다!\n";
		ATK += 9; // 수치 추후 조율
		std::cout << name << "의 공격력이 추가로 9 올랐습니다!\n\n";
		break;
	default:
		std::cout << "공격 패턴 출력 과정에서 오류 발생\n";
		break;
	}

	std::cout << "\n[enter 키를 눌러 계속하기]";

	char c = _getch();
	if (c == 'c')
	{
		cheatMode = true;
		std::cout << "\n치트 모드가 활성화됩니다...";
		Sleep(2000);
		maxHP = 100;
		currentHP = 100;
		ATK = 8;
		enemy->setCurrentHP(enemy->getMaxHP());
	}
	system("cls");
}

void BossMonster::attackPattern4(std::shared_ptr<Character> enemy)
{
	int a = rand() % 15 + 1;
	int b = rand() % 15 + 1;

	int random = rand() % 4 + 1;

	std::cout << name << "가 [깜짝 퀴즈 공격]을 시전합니다!\n";
	std::cout << "과연 내가 내는 퀴즈를 맞출 수 있을까 찍찍~?\n";
	std::cout << "다음 퀴즈의 정답은 뭘까?\n\n";

	switch (random)
	{
	case 1:
		// quiz #1
		std::cout << "int a는 " << a << "이고, int b는 " << b << "이다.\n";
		std::cout << "a % b의 값은 ?\n\n";
		correctAnswer = a % b;
		break;
	case 2:
		// quiz #2
		std::cout << "int a는 " << a << "이고, int b는 " << b << ",\n";
		std::cout << "int answer = (a < b) ? a : b일 때\n";
		std::cout << "answer의 값은?\n\n";
		correctAnswer = (a < b) ? a : b;
		break;
	case 3:
		// quiz #3
		correctAnswer = (a < 7 && b > 7);
		std::cout << "int a는 " << a << "이고, int b는 " << b << ",\n";
		std::cout << "int answer = (a < 7 && b > 7)일 때\n";
		std::cout << "answer의 값은?\n\n";
		break;
	case 4:
		// quiz #4
		std::cout << "int a는 " << a << "이고, int b는 " << b << ",\n";
		std::cout << "answer = (a & b)의 값은?\n";
		std::cout << "answer의 값은?\n\n";
		correctAnswer = (a & b);
		break;
	}

	std::cin >> playerAnswer;

	if (playerAnswer != correctAnswer)
	{
		std::cout << name << ": 푸하하 틀렸지롱~\n";
		std::cout << name << "가 공부하지 않은 님을 응징하고 체력을 80 회복합니다!\n";
		enemy->takeDamage(ATK);
		currentHP += 80;
		if (currentHP > maxHP)
		{
			currentHP = maxHP;
		}
	}
	else
	{
		std::cout << name << ": 정답을 맞추다니...!! 이거 실화냐 찍찍~~??\n\n";
		std::cout << enemy->getName() << "은 혼란을 틈타 " << name << "를 공격했습니다.\n";
		takeDamage(enemy->getATK());
		std::cout << '\n' << enemy->getName() << "은 자신감을 얻어 체력을 [22] 회복했습니다.\n";
		enemy->setCurrentHP(enemy->getCurrentHP() + 22);
		if (enemy->getCurrentHP() > enemy-> getMaxHP())
		{
			enemy->setCurrentHP(enemy->getMaxHP());
		}
	}
}

void BossMonster::takeDamage(int amount)
{
	//speed의 절반이 회피 확률, 최댓값은 30
	int dodgeChance = (speed > 60) ? 30 : speed / 2;

	if (isInvincible == true)
	{
		std::cout << name << "는 [시궁창의 축복] 효과로 인해 피해를 입지 않았습니다!\n";
		std::cout << "우하하, 이 정도 공격은 통하지 않는다 찍찍~!\n\n";
		isInvincible = false;
	}
	else if ((rand() % 100 < dodgeChance))
	{
		std::cout << "\n 휘릭! " << name << "가 공격을 가볍게 피했습니다!" << std::endl;
		Sleep(500);
		return;
	}
	else
	{
		currentHP -= amount;
		std::cout << name << "에게 " << amount << "의 피해를 입혔습니다!\n";
	}
	

	if (currentHP <= 0) {
		currentHP = 0;
		death();
	}
}

void BossMonster::printStatus()
{
	std::cout << "현재 " << name << "의 상태입니다\n\n";
	std::cout << "체력: " << getCurrentHP() << "/" << getMaxHP() << "\n";
	std::cout << "민첩성: " << getSpeed() << "\n";
}

void BossMonster::death()
{
	std::cout << name << "크윽... 내가 지다니...!! 찍...\n";
	std::cout << name << "를 쓰러뜨렸습니다~!!\n\n";
}

// getters
bool BossMonster::getIsInvincible()
{
	return isInvincible;
}

// setters