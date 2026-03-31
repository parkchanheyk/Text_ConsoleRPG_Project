#include "ShopUI.h"
#include "Shop.h"
#include "Money.h"
#include "TransactionManager.h"
#include "ItemBase.h"
#include "Player.h"
#include <iostream>
#include <vector>
#include <conio.h>
#include <windows.h>

// ────────────────────────────────────────────
// 레이아웃 행 번호 상수
// ────────────────────────────────────────────
//  0   ?????????????? [ 상점 ] ??????????????
//  1   [현재 돈: ...]
//  2   (빈 줄)
//  3   [판매 아이템] ~ 아이템 목록 (최대 STOCK_ROWS줄)
// MENU_ROW    { 1.구매  2.판매  3.재구매  4.종료 }
// INPUT_ROW   수량 입력: ___
// LOG_START   ─── 로그 ───  (5줄 고정)
// ────────────────────────────────────────────
static constexpr int HEADER_ROW = 0;
static constexpr int MONEY_ROW = 1;
static constexpr int LIST_ROW = 3;
static constexpr int STOCK_ROWS = 15;
static constexpr int MENU_ROW = LIST_ROW + STOCK_ROWS + 1;
static constexpr int INPUT_ROW = MENU_ROW + 2;
static constexpr int LOG_START = INPUT_ROW + 2;

// ── 유틸리티 ──────────────────────────────────
void ShopUI::gotoxy(int x, int y)
{
    COORD pos = { (SHORT)x, (SHORT)y };
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

void ShopUI::clearLine(int row)
{
    gotoxy(0, row);
    std::cout << std::string(60, ' ');
    gotoxy(0, row);
}

void ShopUI::pushLog(const std::string& msg)
{
    s_logs.push_back(msg);
    if ((int)s_logs.size() > MAX_LOGS)
        s_logs.pop_front();
}

void ShopUI::renderLog(int startRow)
{
    gotoxy(0, startRow);
    std::cout << "--------------------------------------------";
    for (int i = 0; i < MAX_LOGS; ++i)
    {
        clearLine(startRow + 1 + i);
        if (i < (int)s_logs.size())
            std::cout << " " << s_logs[i];
    }
}

void ShopUI::ResetUIState()
{
    while (_kbhit()) _getch();
}

// ── 메뉴 출력 ────────────────────────────────
void ShopUI::showMenu(int row)
{
    clearLine(row);
    std::cout << "{ 1. 구매  2. 판매  3. 재구매  4. 종료 }";
}

// ── 아이템 목록 출력 ──────────────────────────
void ShopUI::showItemLists(Shop& shop, int startRow)
{
    int row = startRow;

    clearLine(row++);
    std::cout << "[판매 아이템]";
    for (auto& pair : shop.getStock())
    {
        clearLine(row);
        std::cout << "  " << pair.first->itemName
            << "  (수량: " << pair.second
            << ", 가격: " << pair.first->buyCost << ")";
        if (++row >= startRow + STOCK_ROWS - 2) break;
    }

    clearLine(row++); // 구분 빈 줄

    clearLine(row++);
    std::cout << "[재구매 아이템]";
    for (auto& pair : shop.getBuyBack())
    {
        clearLine(row);
        std::cout << "  " << pair.first->itemName
            << "  (수량: " << pair.second
            << ", 가격: " << pair.first->buyCost << ")";
        if (++row >= startRow + STOCK_ROWS) break;
    }

    // 잔상 제거
    while (row < startRow + STOCK_ROWS)
        clearLine(row++);
}

// ── 아이템 선택 ───────────────────────────────
template<typename MapType>
std::shared_ptr<ItemBase> ShopUI::selectItem(const MapType& items, int startRow)
{
    if (items.empty())
    {
        clearLine(startRow);
        std::cout << "아이템이 없습니다.";
        return nullptr;
    }

    std::vector<std::shared_ptr<ItemBase>> itemList;
    static int selectedIndex = 0;

    for (auto& pair : items)
        itemList.push_back(pair.first);

    if (itemList.empty())
        return nullptr;

    if (selectedIndex >= itemList.size())
        selectedIndex = 0;

    int row = startRow;
    clearLine(row++);
    std::cout << "[아이템 선택]";

    for (int i = 0; i < (int)itemList.size(); ++i)
    {
        clearLine(row);
        std::cout << (i == selectedIndex ? " > " : "   ")
            << itemList[i]->itemName
            << "  (수량: " << items.at(itemList[i])
            << ", 가격: " << itemList[i]->buyCost << ")";
        ++row;
    }

    int endRow = startRow + STOCK_ROWS;
    while (row < endRow)
        clearLine(row++);

    if (!_kbhit()) return nullptr;

    int key = _getch();

    if (key == 27)
    {
        ResetUIState();
        s_escaped = true;
        return nullptr;
    }

    if (key == 224)
    {
        key = _getch();

        if (key == 72)
        {
            selectedIndex--;
            if (selectedIndex < 0)
                selectedIndex = (int)itemList.size() - 1;
        }
        else if (key == 80)
        {
            selectedIndex++;
            if (selectedIndex >= (int)itemList.size())
                selectedIndex = 0;
        }
    }
    else if (key == 13)
    {
        ResetUIState();
        return itemList[selectedIndex];
    }

    return nullptr;
}

// ── 메인 틱 ───────────────────────────────────
bool ShopUI::updateShopTick(Shop& shop, std::shared_ptr<Player> player)
{
    enum class EState { Main, SelectItem, InputCount };

    static EState  state = EState::Main;
    static int     action = 0;
    static std::shared_ptr<ItemBase> selectedItem = nullptr;
    static bool    initialized = false;

    // 상점 진입 시 1회 초기화
    if (!initialized)
    {
        while (_kbhit()) _getch();
        s_logs.clear();
        system("cls");
        initialized = true;
    }

    // ── 헤더 (고정) ──
    gotoxy(0, HEADER_ROW);
    std::cout << "==========================================";
    gotoxy(0, HEADER_ROW + 1);
    std::cout << "                  [ 상점 ]               ";
    gotoxy(0, HEADER_ROW + 2);
    std::cout << "==========================================";
    clearLine(MONEY_ROW + 2); // HEADER 3줄 이후 돈 표시
    gotoxy(0, MONEY_ROW + 2);
    std::cout << "[현재 돈: " << player->GetMoney()->getCurrentMoney() << "]";

    switch (state)
    {
        // ── 1. 메인 ──
    case EState::Main:
    {
        showItemLists(shop, LIST_ROW + 2); // 헤더 3줄 보정
        showMenu(MENU_ROW + 2);
        clearLine(INPUT_ROW + 2);

        if (!_kbhit()) break;
        int key = _getch();

        if (key == '4' || key == 27)
        {
            initialized = false;
            s_logs.clear();
            ResetUIState();
            state = EState::Main;
            return false;
        }
        if (key >= '1' && key <= '3')
        {
            action = key - '0';
            ResetUIState();
            state = EState::SelectItem;
        }
        break;
    }

    // ── 2. 아이템 선택 ──
    case EState::SelectItem:
    {
        s_escaped = false;

        selectedItem = nullptr;

        showMenu(MENU_ROW + 2);

        // 목록이 비어있으면 로그 출력 후 메인으로 복귀
        if (action == 3 && shop.getBuyBack().empty())
        {
            pushLog("! 재구매 가능한 아이템이 없습니다.");
            ResetUIState();
            state = EState::Main;
            break;
        }
        if (action == 1 && shop.getStock().empty())
        {
            pushLog("! 판매 중인 아이템이 없습니다.");
            ResetUIState();
            state = EState::Main;
            break;
        }

        if (action == 1) // 구매
        {
            selectedItem = selectItem(shop.getStock(), LIST_ROW + 2);
        }
        else if (action == 2) // 판매
        {
            if (player->GetInventory()->container.empty())
            {
                pushLog("! 인벤토리가 비어 있습니다.");
                ResetUIState();
                state = EState::Main;
                break;
            }

            selectedItem = selectItem(player->GetInventory()->container, LIST_ROW + 2);
        }
        else if (action == 3) // 재구매
        {
            selectedItem = selectItem(shop.getBuyBack(), LIST_ROW + 2);
        }

        if (s_escaped)
        {
            state = EState::Main;
        }
        else if (selectedItem)
        {
            ResetUIState();
            state = EState::InputCount;
        }
        break;
    }

    // ── 3. 수량 입력 ──
    case EState::InputCount:
    {
        static std::string inputBuffer = "";
        static bool        inputInited = false;

        if (!inputInited)
        {
            inputBuffer = "";
            inputInited = true;
        }

        showItemLists(shop, LIST_ROW + 2);
        showMenu(MENU_ROW + 2);

        clearLine(INPUT_ROW + 2);
        std::cout << "수량 입력: " << inputBuffer << "_";

        if (!_kbhit()) break;
        int key = _getch();

        if (key >= '0' && key <= '9')
        {
            inputBuffer += (char)key;
        }
        else if (key == 8 && !inputBuffer.empty())
        {
            inputBuffer.pop_back();
        }
        else if (key == 13) // Enter
        {
            if (inputBuffer.empty())
            {
                pushLog("! 수량을 입력하세요.");
            }
            else
            {
                int count = std::stoi(inputBuffer);

                if (action == 1)
                {
                    if (TransactionManager::buyItem(shop, selectedItem, player, count))
                        pushLog("구매 완료: " + selectedItem->itemName + " x" + std::to_string(count));
                    else
                        pushLog("! 구매 실패");
                }
                else if (action == 2)
                {
                    if (TransactionManager::sellItem(shop, selectedItem, player, count))
                        pushLog("판매 완료: " + selectedItem->itemName + " x" + std::to_string(count));
                    else
                        pushLog("! 판매 실패");
                }
                else if (action == 3)
                {
                    if (TransactionManager::buyBackItem(shop, selectedItem, player, count))
                        pushLog("구매 완료: " + selectedItem->itemName + " x" + std::to_string(count));
                    else
                        pushLog("! 재구매 실패");
                }

                inputInited = false;
                ResetUIState();
                selectedItem = nullptr;
                state = EState::Main;
            }
        }
        else if (key == 27) // ESC
        {
            inputInited = false;
            ResetUIState();
            selectedItem = nullptr;
            state = EState::Main;
        }
        break;
    }
    }

    // 로그 영역 고정 렌더링
    renderLog(LOG_START + 2);

    return true;
}