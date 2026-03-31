#pragma once
#include <string>	// std::string
#include <memory>	// std::shared_ptr

enum class EItemType
{
	Equip,
	Consume,
	Ingredient
};

// Forward Declaration
class Character;

// 패턴에 따라 필요한 함수를 정의한 인터페이스
// 캐릭터에게 아이템 효과를 적용할 수 있는 경우
class IApplicablePattern
{
public:
	// 캐릭터에게 효과를 적용
	virtual bool ApplyEffect(const std::shared_ptr<Character> character) = 0;
};
// 캐릭터로부터 아이템 효과를 제거할 수 있는 경우
class IReversiblePattern
{
public:
	// 캐릭터로부터 효과를 제거
	virtual bool RevertEffect(const std::shared_ptr<Character> character) = 0;
};

class ItemBase : public std::enable_shared_from_this<ItemBase>
{
public:
	ItemBase() {}

	ItemBase(EItemType type, std::string name, size_t maxCount, size_t sell, size_t buy)
		: itemType(type), itemName(name), maxStackCount(maxCount), sellCost(sell), buyCost(buy) {
	}
	virtual ~ItemBase() = default;

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

