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
	/// <summary>
	/// 인벤토리 UI를 화면에 출력하고 사용자 입력을 처리하는 함수
	/// </summary>
	/// <param name="inventory">인벤토리</param>
	static void UpdateInventoryUITick(std::shared_ptr<Inventory> inventory)
	{
		// Inventory UI 최초 출력 시 Index 인디케이터는 0으로 초기화
		size_t selectedIndex = 0;

		// Inventory UI 반복 출력
		while (true)
		{
			// 인벤토리 UI 출력
			ShowItemList(inventory, selectedIndex);

			// 키보드 입력 대기
			char inputKey = _getch();

#pragma region 입력된 키에 따른 동작
			
			if (inputKey == 13)	// Enter
			{
				// 선택한 아이템 정보 얻어오기
				for (auto it = inventory->container.begin(); it != inventory->container.end(); ++it)
				{
					if (selectedIndex == 0)
					{
						std::shared_ptr<ItemBase> item = (*it).first;
						// 아이템 제거 및 메뉴 나가기
						if (inventory->RemoveItem(item, 1) == true)
						{
							// BattleManager에서 아이템 효과 적용 시도
							return;
						}
					}
					--selectedIndex;
				}

				// 아이템 제거 실패 시 인벤토리 UI 화면 유지
			}
			if (inputKey == 27)	// ESC
			{
				// 메뉴 나가기
				return;
			}
			if (inputKey == 72)	// UP Key
			{
				--selectedIndex;
			}
			if (inputKey == 80)	// Down Key
			{
				++selectedIndex;
			}

#pragma endregion
		}
	}

	/// <summary>
	/// 인벤토리를 출력하는 함수
	/// </summary>
	/// <param name="inventory">인벤토리</param>
	/// <param name="selectedIndex">선택 인디케이터의 위치</param>
	static void ShowItemList(std::shared_ptr<Inventory> inventory, size_t selectedIndex)
	{
		// 인디케이터 인덱스 조정
		selectedIndex %= inventory->container.size();
		if (selectedIndex < 0)
		{
			selectedIndex = inventory->container.size() - selectedIndex;
		}

		// UI 좌우 크기 조절을 위한 최대 길이 저장 변수
		size_t maxLength = 12;	// "Inventory"의 길이를 최소값으로 설정

		// 아이템을 출력할 줄의 Y좌표
		size_t locationY = 2;

		for (const auto& pair : inventory->container)
		{
			// 커서 위치 이동 (앞쪽 공백 6칸 고정)
			SetTextCursorLocation(2, locationY++);

			// 출력할 문자열 설정
			std::string line = "    ";
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
		for (int i = 2; i < locationY; ++i)
		{
			// 좌측 테두리 출력
			SetTextCursorLocation(0, i);
			std::cout << '|';

			// 우측 테두리 출력
			SetTextCursorLocation(maxLength + 1, i);
			std::cout << '|';
		}

		// 하단 테두리 출력
		SetTextCursorLocation(0, locationY);
		std::cout << horizontalBorder << std::endl;

#pragma endregion

		// 입력 안내 문구 출력
		std::cout << "[▲ / ▼ 방향키] : 커서 이동" << std::endl;
		std::cout << "[Enter 키] : 아이템 사용" << std::endl;
		std::cout << "[ 키] : 아이템 설명 보기" << std::endl;

		// 상단에 메뉴 이름 출력
		SetTextCursorLocation((maxLength / 2) - 5, 0);
		std::cout << "* Inventory *";

		// 아이템 선택 인디케이터 출력
		if (inventory->container.size() > 0)
		{
			SetTextCursorLocation(4, selectedIndex + 2);
			std::cout << ">";
		}
	}

	static void ShowMenu()
	{
	}
};
