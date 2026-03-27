//TransactionManager.cpp
#include "TransactionManager.h"
#include "Shop.h"
#include "Money.h"
#include "ItemBase.h"
#include <iostream>

bool TransactionManager::buyItem(Shop& shop, std::shared_ptr<ItemBase> item, int count, Money& money)
{
    if (!item) return false;

    if (!shop.hasStock(item, count))
    {
        std::cout << item->itemName << " 재고 부족\n";
        return false;
    }

    size_t cost = item->buyCost * count;

    if (!money.spendMoney(cost))
    {
        std::cout << "돈 부족\n";
        return false;
    }

    shop.reduceStock(item, count);

    std::cout << item->itemName << " " << count << "개 구매 성공\n";
    return true;
}

bool TransactionManager::sellItem(Shop& shop, std::shared_ptr<ItemBase> item, int count, Money& money)
{
    if (!item) return false;

    size_t earn = item->sellCost * count;

    money.getMoney(earn);
    shop.addBuyBack(item, count);

    std::cout << item->itemName << " " << count << "개 판매 성공\n";
    return true;
}

bool TransactionManager::buyBackItem(Shop& shop, std::shared_ptr<ItemBase> item, int count, Money& money)
{
    if (!item) return false;

    if (!shop.hasBuyBack(item, count))
    {
        std::cout << item->itemName << " 재구매 불가\n";
        return false;
    }

    size_t cost = item->buyCost * count;

    if (!money.spendMoney(cost))
    {
        std::cout << "돈 부족\n";
        return false;
    }

    shop.reduceBuyBack(item, count);

    std::cout << item->itemName << " " << count << "개 재구매 성공\n";
    return true;
}