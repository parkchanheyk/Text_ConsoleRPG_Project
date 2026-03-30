#include "Inventory.h"
#include <Windows.h>	// COORD, SetConsoleCursorPosition
#include <iostream>	// std::cout, std::endl
#include <conio.h>

// 생성자 (인벤토리 사이즈 제한 설정)
Inventory::Inventory(size_t inventoryCapacity) : capacity(inventoryCapacity)
{
	std::cout << inventoryCapacity << "칸 짜리 인벤토리 생성됨" << std::endl;
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

		std::cout << "#LogTemp - Inventory : Success to Add Item(" << item->itemName << ") x " << amount << std::endl;
		return true;
	}

	// 인벤토리 수정 없이 함수 종료
	std::cout << "#LogTemp - Inventory : Failed to Add Item(" << item->itemName << ") x " << amount << std::endl;
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
		std::cout << "#LogTemp - Inventory : Failed to Remove Item(" << item->itemName << ") x " << amount << std::endl;
		return false;
	}

	// 보유 아이템 개수 감소 처리
	container[item] -= amount;

	// 감소 후 아이템 0개 보유 시 목록에서 해당 아이템 삭제
	if (container[item] == 0)
	{
		container.erase(item);
	}

	std::cout << "#LogTemp - Inventory : Success to Remove Item(" << item->itemName << ") x " << amount << std::endl;
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

// 인벤토리에 보유중인 아이템 목록 출력
void Inventory::PrintInventory() const
{
//	// 선택된 아이템이 인벤토리의 몇번째 줄에 위치한지를 저장하는 변수
//	static size_t selectedIndex = 0;
//
//	// UI 좌우 크기 조절을 위한 최대 길이 저장 변수
//	size_t maxLength = 12;	// 메뉴 이름의 길이를 최소값으로 설정
//
//	// 아이템 목록 출력
//	size_t index = 2;
//	for (const auto& pair : container)
//	{
//		// 커서 위치 이동 (앞쪽 공백 6칸 고정)
//		SetTextCursorLocation(6, index++);
//
//		// 출력할 문자열 설정
//		std::string line;
//		line.append(pair.first->itemName);	// 아이템 이름
//		line.append(" x ");		// 개수 표시를 위한 인디케이터
//		line.append(std::to_string(pair.second));	// 보유 개수
//
//		// 문자열 출력
//		std::cout << line << std::endl;
//
//		// 문자열 길이 비교
//		maxLength = (maxLength < (line.size() + 6)) ? line.size() + 6 : maxLength;
//	}
//
//#pragma region Border 출력
//
//	// 수평 테두리 문자열 설정
//	std::string horizontalBorder = "+";
//	horizontalBorder.append(maxLength, '-');
//	horizontalBorder.append("+");
//
//	// 상단 테두리 출력
//	SetTextCursorLocation(0, 1);
//	std::cout << horizontalBorder;
//
//	// 좌우 테두리 출력
//	for (int i = 2; i < index; ++i)
//	{
//		// 좌측 테두리 출력
//		SetTextCursorLocation(0, i);
//		std::cout << '|';
//
//		// 우측 테두리 출력
//		SetTextCursorLocation(maxLength + 1, i);
//		std::cout << '|';
//	}
//
//	// 하단 테두리 출력
//	SetTextCursorLocation(0, index);
//	std::cout << horizontalBorder;
//
//#pragma endregion
//
//	// 상단에 메뉴 이름 출력
//	SetTextCursorLocation((maxLength / 2) - 5, 0);
//	std::cout << "* Inventory *";
//
//	// 아이템 선택 인디케이터 출력
//	SetTextCursorLocation(4, selectedIndex + 2);
//	std::cout << ">";

#pragma region 사용자 입력 처리

	//// 사용자 입력 대기
	//while (true)
	//{
	//	if (_kbhit())
	//	{
	//		char inputKey = _getch();

	//		if (inputKey == 72)	// UP_ARROW
	//		{
	//			// 아이템 선택 인덱스 조정
	//			selectedIndex = (selectedIndex + container.size() - 1) % container.size();

	//			std::cout << "커서 위로 이동" << std::endl;
	//			break;
	//		}
	//		if (inputKey == 80)	// DOWN_ARROW
	//		{
	//			// 아이템 선택 인덱스 조정
	//			selectedIndex = (selectedIndex + 1) % container.size();
	//			std::cout << "커서 아래로 이동" << std::endl;
	//			break;
	//		}
	//		if (inputKey == 27)	// ESC
	//		{
	//			std::cout << "ESC 키" << std::endl;
	//			break;
	//		}
	//	}
	//}

#pragma endregion
}

//#define KEY_UP 72
//#define KEY_DOWN 80
