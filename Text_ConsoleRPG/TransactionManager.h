//TransactionManager.h
#pragma once
#include <memory>

class Shop;
class ItemBase;
class Money;

class TransactionManager
{
public:
    static bool buyItem(Shop& shop, std::shared_ptr<ItemBase> item, int count, Money& money);
    static bool sellItem(Shop& shop, std::shared_ptr<ItemBase> item, int count, Money& money);
    static bool buyBackItem(Shop& shop, std::shared_ptr<ItemBase> item, int count, Money& money);
};