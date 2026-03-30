#include <iostream>
#include <string>

#include "BossMonster.h"

BossMonster::BossMonster() :Character("[초대형 울트라 찍찍 들쥐]")
{
	// 모든 수치는 공유 후 조율할 예정
	maxHP = 10000;
	currentHP = 10000;
	level = 100;
	ATK = 100;
	exp = 100;
	speed = 100;
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

void BossMonster::attack(Character* enemy)
{	
	int pattern = 0;

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

	switch (pattern)
	{
	case 1:
		std::cout << name << "가 [꼬리 휘두르기]를 시전했습니다!\n\n";
		enemy->setCurrentHP(enemy->getCurrentHP() - (ATK));
		enemy->takeDamage(ATK);
		break;
	case 2:
		std::cout << name << "가 [산성 침 뱉기]를 시전했습니다!\n\n";
		enemy->setCurrentHP(enemy->getCurrentHP() - (ATK * 0.7));
		enemy->takeDamage(ATK * 0.7);
		break;
	case 3:
		std::cout << name << "가 [고양이 잡는 쥐]를 시전했습니다.\n";
		std::cout << "손톱이 날아옵니다!\n\n";
		enemy->setCurrentHP(enemy->getCurrentHP() - (ATK * 1.7));
		enemy->takeDamage(ATK * 1.7);
		break;
	case 5:
		std::cout << name << "가 메가 [썩은 치즈]를 먹었습니다!\n";
		setCurrentHP(getCurrentHP() + 100);
		std::cout << name << "의 체력이 100 회복되었습니다.\n\n";
		break;
	case 6:
		isInvincible = true;
		std::cout << name << "가 ??????다!\n";
		std::cout << name << "를 향한 다음 공격이 1회 무효화됩니다.\n\n";
		// Player쪽에서 만약 isInvincible = true;면 대미지 0을 넣는 거로
		break;
	case 7:
		std::cout << name << "가 ~~~~를 시전했습니다!";
		ATK += 50; // 수치 추후 조율
		std::cout << name << "의 공격력이 추가로 50 올랐습니다!\n\n";
		break;
	default:
		std::cout << "공격 패턴 출력 과정에서 오류 발생\n";
		break;
	case 4: //얘를 맨 밑에 두지 않으면 빌드 실패함..
		// static cast인지 dynamic cast인지, 그리고 아래 체크 필요한지 확인
		Player * player = dynamic_cast<Player*>(enemy);
		if (player != nullptr)
		{
			attackPattern4(player);
		}
		else
		{
			std::cout << "오류: enemy가 Player 타입이 아닙니다.\n";
		}
		attackPattern4(player);
		break;
	}
}

void BossMonster::attackPattern4(Player* player)
{
	std::cout << name << "가 퀴즈 공격을 시전합니다!\n\n";
	std::cout << name << ": 너처럼 나쁜 아이는 벌을 받아야 한다 찍찍...\n";
	std::cout << name << ": 하지만 그 전에 너를 평가하겠다 찍찍!\n";
	std::cout << name << ": 과연 내가 내는 퀴즈를 맞출 수 있을까 찍찍~?!?!?!\n\n";

	int a = rand() % 15 + 1;
	int b = rand() % 15 + 1;

	int random = rand() % 4 + 1;

	std::cout << "다음 퀴즈의 정답은 뭘까?";

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
		std::cout << "answer = (a & b)의 값은?\n"; // 이거 배웠나?
		std::cout << "answer의 값은?\n\n";
		correctAnswer = (a & b);
		break;
	}
}

void BossMonster::takeDamage(int amount)
{
	currentHP -= amount;

	std::cout << name << "에게 " << amount << "의 피해를 입혔습니다!\n";

	if (currentHP <= 0) {
		currentHP = 0;
		death();
	}
}

void BossMonster::attackPattern4CheckAnswer(Player* player)
{
	if (true/*true 지우고 이거 player->getPlayerAnswer() != correctAnswer*/)
	{
		std::cout << name << ": 푸하하 틀렸지롱~\n";
		std::cout << name << "가 공부하지 않은 님을 응징하고 체력을 회복합니다!\n";
		player->setCurrentHP(player->getCurrentHP() - (ATK));
		currentHP += ATK;
	}
	else
	{
		std::cout << name << ": 정답을 맞추다니...!! 이거 실화냐 찍찍~~??\n";
		std::cout << player->getName() << "은 혼란을 틈타 " << name << "를 공격했습니다.\n\n";
		takeDamage(player->getATK());
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
	
	// 전투하면서 올랐던 공격력 수치 초기화.
	// 만약 보스 죽이고 게임이 아예 끝난다면 이거 필요 없음.
	ATK = 100;
}

// getters
bool BossMonster::getIsInvincible()
{
	return isInvincible;
}
int BossMonster::getPhase()
{
	return phase;
}
int BossMonster::getCorrectAnswer()
{
	return correctAnswer;
}

// setters