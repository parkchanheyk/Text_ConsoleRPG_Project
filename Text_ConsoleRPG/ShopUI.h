#pragma once
#include <memory>
#include <vector>
#include <map>
#include <deque>
#include <string>

class Shop;
class Money;
class ItemBase;

class ShopUI
{
public:
    static bool updateShopTick(Shop& shop, Money& money);

private:
    static void showMenu(int row);
    static void showItemLists(Shop& shop, int startRow);
    static std::shared_ptr<ItemBase> selectItem(
        const std::map<std::shared_ptr<ItemBase>, int>& items, int startRow);

    static void gotoxy(int x, int y);
    static void clearLine(int row);
    static void pushLog(const std::string& msg);
    static void renderLog(int startRow);

    static std::deque<std::string> s_logs;
    static constexpr int MAX_LOGS = 5;
};