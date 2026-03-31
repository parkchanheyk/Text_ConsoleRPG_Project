#include "Inventory.h"
#include <Windows.h>	// COORD, SetConsoleCursorPosition
#include <iostream>	// std::cout, std::endl
#include <conio.h>
#include "LogMacros.h"

// 생성자 (인벤토리 사이즈 제한 설정)
Inventory::Inventory(size_t inventoryCapacity) : capacity(inventoryCapacity)
{
	LOG_INFO(std::to_string(inventoryCapacity) + "칸 짜리 인벤토리 생성됨");
}

/// <summary>
/// 인벤토리에 아이템을 임의 개수만큼 추가 시도
/// </summary>
/// <param name="item">아이템</param>
/// <param name="amount">개수</param>
/// <returns>True : 아이템 추가 완료</returns>
bool Inventory::AddItem(std::shared_ptr<ItemBase> item, size_t amount)
{
	// 추가할 아이템이 존재하지 않거나 개수가 0이면 false 반환
	if (item == nullptr || amount == 0)
	{
		return false;
	}

	// 현재 해당 아이템을 추가로 수용할 수 있는 최대 개수 계산
	size_t acceptableAmount = GetAcceptableAmount(item);

	// 수용 가능한 최대 개수와 추가하려는 개수 비교
	if (amount <= acceptableAmount)
	{
		// 인벤토리 내용 수정
		container[item] += amount;

		// 로그 출력
		std::string logMsg = "#Inventory : Success to Add Item(";
		logMsg.append(item->itemName);
		logMsg.append(") x ");
		logMsg.append(std::to_string(amount));
		LOG_INFO(logMsg);

		return true;
	}

	// 인벤토리 수정 없이 함수 종료
	
	// 로그 출력
	std::string logMsg = "#Inventory : Failed to Add Item(";
	logMsg.append(item->itemName);
	logMsg.append(") x ");
	logMsg.append(std::to_string(amount));
	LOG_INFO(logMsg);

	return false;
}

/// <summary>
/// 인벤토리에 아이템을 임의 개수만큼 제거 시도
/// </summary>
/// <param name="item">아이템</param>
/// <param name="amount">개수</param>
/// <returns>True : 아이템 제거 성공</returns>
bool Inventory::RemoveItem(std::shared_ptr<ItemBase> item, size_t amount)
{
	// 제거할 아이템이 존재하지 않거나 개수가 0이면 false 반환
	if (item == nullptr || amount == 0)
	{
		return false;
	}

	// 현재 보유하고 있는 해당 아이템 개수 확인
	if (amount > container[item])
	{
		// 인벤토리 수정 없이 false 반환
		
		// 로그 출력
		std::string logMsg = "#Inventory : Failed to Remove Item(";
		logMsg.append(item->itemName);
		logMsg.append(") x ");
		logMsg.append(std::to_string(amount));
		LOG_INFO(logMsg);

		return false;
	}

	// 보유 아이템 개수 감소 처리
	container[item] -= amount;

	// 감소 후 아이템 0개 보유 시 목록에서 해당 아이템 삭제
	if (container[item] == 0)
	{
		container.erase(item);
	}

	// 로그 출력
	std::string logMsg = "#Inventory : Success to Remove Item(";
	logMsg.append(item->itemName);
	logMsg.append(") x ");
	logMsg.append(std::to_string(amount));
	LOG_INFO(logMsg);

	return true;
}

/// <summary>
/// 임의 아이템을 인벤토리에 추가하려는 경우 가능한 최대 수량을 계산
/// </summary>
/// <param name="item">아이템</param>
/// <returns>0 : 아이템이 추가될 수 없음</returns>
size_t Inventory::GetAcceptableAmount(std::shared_ptr<ItemBase> item) const
{
	// 확인하려는 아이템이 nullptr인 경우 0 반환
	if (item == nullptr)
	{
		return 0;
	}

	// 인벤토리의 남은 용량에 대한 여유 수량 계산
	size_t acceptableAmount = (capacity - GetSize()) * item->maxStackCount;

	// 동일한 아이템을 보유한 경우, 보유 개수에 따른 여유 수량 계산
	if (container.find(item) != container.end())
	{
		// 현재 보유중인 수량 확인
		size_t currentAmount = container.at(item);

		// 현재 보유중인 수량을 바탕을 슬롯에 대입했을 경우의 여유 수량 계산
		if ((currentAmount % item->maxStackCount) != 0)
		{
			acceptableAmount += item->maxStackCount - (currentAmount % item->maxStackCount);
		}
	}
	return acceptableAmount;
}

// 현재 인벤토리의 몇칸이 사용중인지 반환
size_t Inventory::GetSize() const
{
	size_t size = 0;
	for (const auto& pair : container)
	{
		if (pair.second > 0)
		{
			size += (pair.second / pair.first->maxStackCount);
			size += (pair.second % pair.first->maxStackCount) == 0 ? 0 : 1;
		}
	}
	return size;
}
