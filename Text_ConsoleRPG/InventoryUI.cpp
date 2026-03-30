#include "InventoryUI.h"

/// <summary>
/// 텍스트 입력 커서를 특정 좌표로 이동
/// <para>Console 화면 좌측 상단 == (0, 0)</para>
/// </summary>
/// <param name="x">수평 좌표</param>
/// <param name="y">수직 좌표</param>
void SetTextCursorLocation(uint32_t x, uint32_t y)
{
	COORD pos = { (SHORT)x, (SHORT)y };
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
