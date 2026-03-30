#pragma once
#include <memory>	// std::shared_ptr
#include <map>		// std::map
#include "ItemBase.h"

// map에서 사용하기 위한 std::shared_ptr<ItemBase>의 comparer
struct ItemBasePointerComparer
{
	bool operator()(const std::shared_ptr<ItemBase>& lhs, const std::shared_ptr<ItemBase>& rhs) const
	{
		if (lhs == nullptr || rhs == nullptr)
		{
			return lhs < rhs;
		}

		// 1차 : itemType 오름차순 정렬
		if (lhs->itemType != rhs->itemType)
		{
			return lhs->itemType < rhs->itemType;
		}

		// 2차 : itemName 오름차순 정렬
		if (lhs->itemName != rhs->itemName)
		{
			return lhs->itemName < rhs->itemName;
		}

		// 3차 : 서로의 typeid(동적 클래스 타입)가 동일한지 확인
		return typeid(lhs.get()) != typeid(rhs.get());
	}
};

class Inventory
{
public:
	// 생성자 (인벤토리 사이즈 제한 설정)
	Inventory(size_t inventoryCapacity = 10);

	/// <summary>
	/// 인벤토리에 아이템을 임의 개수만큼 추가 시도
	/// </summary>
	/// <param name="item">아이템</param>
	/// <param name="amount">개수</param>
	/// <returns>True : 아이템 추가 완료</returns>
	bool AddItem(std::shared_ptr<ItemBase> item, size_t amount = 1);// end function

	/// <summary>
	/// 인벤토리에 아이템을 임의 개수만큼 제거 시도
	/// </summary>
	/// <param name="item">아이템</param>
	/// <param name="amount">개수</param>
	/// <returns>True : 아이템 제거 성공</returns>
	bool RemoveItem(std::shared_ptr<ItemBase> item, size_t amount = 1);

	/// <summary>
	/// 임의 아이템을 인벤토리에 추가하려는 경우 가능한 최대 수량을 계산
	/// </summary>
	/// <param name="item">아이템</param>
	/// <returns>0 : 아이템이 추가될 수 없음</returns>
	size_t GetAcceptableAmount(std::shared_ptr<ItemBase> item) const;

	// 현재 인벤토리의 몇칸이 사용중인지 반환
	size_t GetSize() const;

	// 인벤토리 크기
	const size_t capacity;

	// (아이템, 개수)로 이루어진 인벤토리 관리 컨테이너
	std::map<std::shared_ptr<ItemBase>, size_t, ItemBasePointerComparer> container;
};

