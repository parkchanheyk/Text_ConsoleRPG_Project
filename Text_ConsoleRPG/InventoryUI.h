#pragma once
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <vector>
#include "Inventory.h"

/// <summary>
/// 텍스트 입력 커서를 특정 좌표로 이동
/// <para>Console 화면 좌측 상단 == (0, 0)</para>
/// </summary>
/// <param name="x">수평 좌표</param>
/// <param name="y">수직 좌표</param>
void SetTextCursorLocation(uint32_t x, uint32_t y);

// 인벤토리 UI를 출력하기 위한 정적 클래스
static class InventoryUI
{
public:
	static void UpdateInventoryUITick(std::shared_ptr<Inventory> inventory)
	{
		
		// Inventory UI 최초 출력 시 Index 인디케이터는 -1으로 초기화
		size_t selectedIndex = -1;

		// Esc 키 입력할 때 까지 대기
		while (true)
		{
			// 인벤토리 UI 출력
			ShowItemList(inventory, selectedIndex);

			if (_kbhit())
			{
				char inputKey = _getch();

				if (inputKey == 27)	// ESC
				{
					std::cout << "ESC 키" << std::endl;
					break;
				}
			}
		}
	}

	// 매개변수로 받은 인벤토리를 출력하는 함수
	static void ShowItemList(std::shared_ptr<Inventory> inventory, size_t selectedIndex)
	{
		std::vector<std::shared_ptr<ItemBase>> itemList;
		itemList.reserve(inventory->container.size());

		if (inventory->container.size() > 0)
		{
			selectedIndex = selectedIndex < 0 ? 0 : selectedIndex;
		}

		// UI 좌우 크기 조절을 위한 최대 길이 저장 변수
		size_t maxLength = 12;	// "Inventory"의 길이를 최소값으로 설정

		for (const auto& pair : inventory->container)
		{
			itemList.push_back(pair.first);

			// 커서 위치 이동 (앞쪽 공백 6칸 고정)
			SetTextCursorLocation(6, itemList.size() + 2);

			// 출력할 문자열 설정
			std::string line;
			line.append(pair.first->itemName);	// 아이템 이름
			line.append(" x ");		// 개수 표시를 위한 인디케이터
			line.append(std::to_string(pair.second));	// 보유 개수

			// 문자열 출력
			std::cout << line << std::endl;

			// 문자열 길이 비교
			maxLength = (maxLength < (line.size() + 6)) ? line.size() + 6 : maxLength;
		}

#pragma region Border 출력

		// 수평 테두리 문자열 설정
		std::string horizontalBorder = "+";
		horizontalBorder.append(maxLength, '-');
		horizontalBorder.append("+");

		// 상단 테두리 출력
		SetTextCursorLocation(0, 1);
		std::cout << horizontalBorder;

		// 좌우 테두리 출력
		for (int i = 2; i < itemList.size() + 2; ++i)
		{
			// 좌측 테두리 출력
			SetTextCursorLocation(0, i);
			std::cout << '|';

			// 우측 테두리 출력
			SetTextCursorLocation(maxLength + 1, i);
			std::cout << '|';
		}

		// 하단 테두리 출력
		SetTextCursorLocation(0, itemList.size() + 2);
		std::cout << horizontalBorder;

#pragma endregion

		// 상단에 메뉴 이름 출력
		SetTextCursorLocation((maxLength / 2) - 5, 0);
		std::cout << "* Inventory *";

		// 아이템 선택 인디케이터 출력
		if (selectedIndex >= 0)
		{
			SetTextCursorLocation(4, selectedIndex + 2);
			std::cout << ">";
		}
		
		//// 사용자가 Esc 키 입력할 때까지 반복
		//while (true)
		//{
		//	if (_kbhit())
		//	{
		//		char inputKey = _getch();

		//		if (inputKey == 72)	// UP_ARROW
		//		{
		//			// 아이템 선택 인덱스 조정

		//			std::cout << "커서 위로 이동" << std::endl;
		//			break;
		//		}
		//		if (inputKey == 80)	// DOWN_ARROW
		//		{
		//			// 아이템 선택 인덱스 조정
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
	}
};
