#include "ConsumeItem.h"
#include <iostream>
#include "Character.h"

bool HPPotionItem::ApplyEffect(const std::shared_ptr<Character> character)
{
	// 포인터(매개변수) nullptr 값 방어 코드
	if (character != nullptr)
	{
		// 캐릭터 레벨이 사용 조건을 만족하는지 확인
		if (character->getLevel() >= minLevel)
		{
			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : Success to Apply Item(" << itemName << ") to " << character->getName() << std::endl;

			// 회복 후 체력 계산
			size_t newHP = character->getCurrentHP() + healHP;

			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : Heal " << character->getName() << "'s HP to " << newHP << std::endl;

			// 회복된 체력 적용
			character->setCurrentHP(newHP);

			return true;
		}
	}

	// 로그 출력
	std::cout << "#LogTemp - ConsumeItem : Failed to Apply Item(" << itemName << ")" << std::endl;
	return false;
}

bool ExpScroll::ApplyEffect(const std::shared_ptr<Character> character)
{
	// 포인터(매개변수) nullptr 값 방어 코드
	if (character != nullptr)
	{
		// 캐릭터 레벨이 사용 조건을 만족하는지 확인
		if (character->getLevel() >= minLevel)
		{
			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : Success to Apply Item(" << itemName << ") to " << character->getName() << std::endl;

			size_t newExp = character->getExp() + exp;

			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : " << character->getName() << " Get Exp as " << exp << std::endl;

			// 증가된 경험치 적용
			character->setExp(newExp);

			return true;
		}
	}

	std::cout << "#LogTemp - ConsumeItem : Failed to Apply Item(" << itemName << ")" << std::endl;
	return false;
}

bool AtkBuffItem::ApplyEffect(const std::shared_ptr<Character> character)
{
	// 포인터(매개변수) nullptr 값 방어 코드
	if (character != nullptr)
	{
		// 캐릭터 레벨이 사용 조건을 만족하는지 확인
		if (character->getLevel() >= minLevel)
		{
			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : Success to Apply Item(" << itemName << ") to " << character->getName() << std::endl;

			// 증가된 공격력 계산
			size_t newAtk = character->getATK() + buffAtk;

			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : Increase Atk of " << character->getName() << " as " << buffAtk << std::endl;

			// 증가된 공격력 적용
			character->setAttack(newAtk);

			return true;
		}
	}

	std::cout << "#LogTemp - ConsumeItem : Failed to Apply Item(" << itemName << ")" << std::endl;
	return false;
}

bool AtkBuffItem::RevertEffect(const std::shared_ptr<Character> character)
{
	// 포인터(매개변수) nullptr 값 방어 코드
	if (character != nullptr)
	{
		// 캐릭터 레벨이 사용 조건을 만족하는지 확인
		if (character->getLevel() >= minLevel)
		{
			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : Success to Revert Item(" << itemName << ") from " << character->getName() << std::endl;

			// 감소된 공격력 계산
			size_t newAtk = character->getATK() - buffAtk;

			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : Decrease Atk of " << character->getName() << " as " << buffAtk << std::endl;

			// 감소된 공격력 적용
			character->setAttack(newAtk);

			return true;
		}
	}

	std::cout << "#LogTemp - ConsumeItem : Failed to Revert Item(" << itemName << ")" << std::endl;
	return false;
}

bool HPBuffItem::ApplyEffect(const std::shared_ptr<Character> character)
{
	// 포인터(매개변수) nullptr 값 방어 코드
	if (character != nullptr)
	{
		// 캐릭터 레벨이 사용 조건을 만족하는지 확인
		if (character->getLevel() >= minLevel)
		{
			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : Success to Apply Item(" << itemName << ") to " << character->getName() << std::endl;

			// 증가된 최대 HP 계산
			size_t newMaxHP = character->getMaxHP() + buffHP;

			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : Increase MaxHP of " << character->getName() << " as " << buffHP << std::endl;

			// 증가된 최대 HP 적용
			character->setMaxHP(newMaxHP);

			return true;
		}
	}

	std::cout << "#LogTemp - ConsumeItem : Failed to Apply Item(" << itemName << ")" << std::endl;
	return false;
}

bool HPBuffItem::RevertEffect(const std::shared_ptr<Character> character)
{
	// 포인터(매개변수) nullptr 값 방어 코드
	if (character != nullptr)
	{
		// 캐릭터 레벨이 사용 조건을 만족하는지 확인
		if (character->getLevel() >= minLevel)
		{
			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : Success to Revert Item(" << itemName << ") from " << character->getName() << std::endl;

			// 감소된 최대 HP 계산
			size_t newMaxHP = character->getMaxHP() - buffHP;

			// 로그 출력
			std::cout << "#LogTemp - ConsumeItem : Decrease MaxHP of " << character->getName() << " as " << buffHP << std::endl;

			// 감소된 최대 HP 적용
			character->setMaxHP(newMaxHP);

			return true;
		}
	}

	std::cout << "#LogTemp - ConsumeItem : Failed to Revert Item(" << itemName << ")" << std::endl;
	return false;
}
