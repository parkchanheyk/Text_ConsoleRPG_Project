#pragma once
#include <iostream>		// std::cout
#include <Windows.h>	// SetConsoleCursorPosition
#include <conio.h>		// _getch
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
	/// <returns>nullptr : 선택한 아이템 없음</returns>
	static std::shared_ptr<ItemBase> UpdateInventoryUITick(std::shared_ptr<Inventory> inventory);

private:
	/// <summary>
	/// 인벤토리를 출력하는 함수
	/// </summary>
	/// <param name="inventory">인벤토리</param>
	/// <param name="selectedIndex">선택 인디케이터의 위치</param>
	static void ShowItemList(std::shared_ptr<Inventory> inventory, int64_t& selectedIndex);
};
