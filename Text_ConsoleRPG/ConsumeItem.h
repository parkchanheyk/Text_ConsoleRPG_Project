#pragma once
#include "ItemBase.h"
#include <memory>	// std::shared_ptr

// Forward Declaration
class Character;

// 패턴에 따라 필요한 함수를 정의한 인터페이스
// 캐릭터에게 아이템 효과를 적용할 수 있는 경우
class IApplicablePattern
{
	// 캐릭터에게 효과를 적용
	virtual bool ApplyEffect(const std::shared_ptr<Character> character) = 0;
};
// 캐릭터로부터 아이템 효과를 제거할 수 있는 경우
class IReversiblePattern
{
	// 캐릭터로부터 효과를 제거
	virtual bool RevertEffect(const std::shared_ptr<Character> character) = 0;
};

// 소비 아이템의 기본이 되는 추상 클래스
class ConsumeItem : public ItemBase, public IApplicablePattern
{
public:
	ConsumeItem()
	{
		itemName = "소비 아이템";
		maxStackCount = 100;
		sellCost = 10;
		buyCost = 100;
	}
};

// HP 포션을 정의한 클래스
class HPPotionItem : public ConsumeItem
{
public:
	HPPotionItem(std::string itemName, size_t healHP, size_t minLevel, size_t buyCost) : ConsumeItem()
	{
		this->itemName = itemName;
		this->healHP = healHP;
		this->minLevel = minLevel;
		this->buyCost = buyCost;
		this->sellCost = buyCost / 10;
	}

	// HP 회복량
	size_t healHP;
	
	// 최소 요구 레벨
	size_t minLevel;

	// 캐릭터의 HP 회복
	virtual bool ApplyEffect(const std::shared_ptr<Character> character) override;
};

// 경험치 스크롤을 정의한 클래스
class ExpScroll : public ConsumeItem
{
public:
	ExpScroll(std::string itemName, size_t exp, size_t minLevel) :ConsumeItem()
	{
		this->itemName = itemName;
		this->exp = exp;
		this->minLevel = minLevel;
	}

	// 획득 exp
	size_t exp;
	
	// 최소 요구 레벨
	size_t minLevel;

	virtual bool ApplyEffect(const std::shared_ptr<Character> character) override;
};

// 공격력 버프 아이템을 정의한 클래스
class AtkBuffItem : public ConsumeItem, public IReversiblePattern
{
public:
	AtkBuffItem(std::string itemName, size_t buffAtk, size_t minLevel) : ConsumeItem()
	{
		this->itemName = itemName;
		this->buffAtk = buffAtk;
		this->minLevel = minLevel;
	}

	// 공격력 증가량
	size_t buffAtk;

	// 최소 요구 레벨
	size_t minLevel;

	// 캐릭터의 공격력 증가
	virtual bool ApplyEffect(const std::shared_ptr<Character> character) override;
	// 캐릭터의 공격력 감소
	virtual bool RevertEffect(const std::shared_ptr<Character> character) override;
};

class HPBuffItem : public ConsumeItem, public IReversiblePattern
{
	HPBuffItem(std::string itemName, size_t buffHP, size_t minLevel) : ConsumeItem()
	{
		this->itemName = itemName;
		this->buffHP = buffHP;
		this->minLevel = minLevel;
	}

	// 공격력 증가량
	size_t buffHP;

	// 최소 요구 레벨
	size_t minLevel;

	// 캐릭터의 최대 HP 증가
	virtual bool ApplyEffect(const std::shared_ptr<Character> character) override;
	// 캐릭터의 최대 HP 감소
	virtual bool RevertEffect(const std::shared_ptr<Character> character) override;
};