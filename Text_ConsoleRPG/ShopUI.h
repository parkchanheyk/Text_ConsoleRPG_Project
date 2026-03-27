//ShopUI.h
#pragma once
#include <memory>
#include <vector>
#include <map>

class Shop;
class Money;
class ItemBase;

class ShopUI
{
public:
    static void run(Shop& shop, Money& money);

private:
    static void showMenu();
    static std::shared_ptr<ItemBase> selectItem(const std::map<std::shared_ptr<ItemBase>, int>& items);
};