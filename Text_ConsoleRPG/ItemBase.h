#pragma once
#include <string>	// std::string

enum class EItemType
{
	Equip,
	Consume,
	Ingredient
};

class ItemBase
{
public:
	ItemBase() {}

	ItemBase(EItemType type, std::string name, size_t maxCount, size_t sell, size_t buy)
		: itemType(type), itemName(name), maxStackCount(maxCount), sellCost(sell), buyCost(buy) {
	}

	// 아이템 타입
	EItemType itemType;

	// 아이템 이름
	std::string itemName;

	// 해당 아이템을 인벤토리 1칸에 저장할 수 있는 최대 개수
	size_t maxStackCount;

	// 상점에 아이템을 판매했을 때 얻는 금액
	size_t sellCost;

	// 상점에서 아이템을 구매했을 때 소비되는 금액
	size_t buyCost;

private:
	// dynamic_cast를 활용하기 위한 가상함수
	virtual void DynamicMethod();
};

