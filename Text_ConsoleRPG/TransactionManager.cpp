//TransactionManager.cpp
#include "TransactionManager.h"
#include "Shop.h"
#include "Money.h"
#include "ItemBase.h"
#include "Player.h"
#include <iostream>

bool TransactionManager::buyItem(Shop& shop, std::shared_ptr<ItemBase> item,
    std::shared_ptr<Player> player, size_t count)
{
    if (!shop.hasStock(item, count)) return false;

    size_t cost = item->buyCost * count;

    if (!player->GetMoney()->canAfford(cost)) return false;

    if (!player->GetInventory()->AddItem(item, count)) return false;

    player->GetMoney()->spendMoney(cost);
    shop.reduceStock(item, count);

    return true;
}

bool TransactionManager::sellItem(Shop& shop, std::shared_ptr<ItemBase> item,
    std::shared_ptr<Player> player, size_t count)
{
    if (!player->GetInventory()->RemoveItem(item, count)) {
        return false;
    }

    size_t earn = item->sellCost * count;

    player->GetMoney()->getMoney(earn);

    shop.addBuyBack(item, count);

    return true;
}

bool TransactionManager::buyBackItem(Shop& shop, std::shared_ptr<ItemBase> item,
    std::shared_ptr<Player> player, size_t count)
{
    if (!shop.hasBuyBack(item, count)) return false;

    size_t cost = item->buyCost * count;

    if (!player->GetMoney()->canAfford(cost)) return false;

    if (!player->GetInventory()->AddItem(item, count)) return false;

    player->GetMoney()->spendMoney(cost);
    shop.reduceBuyBack(item, count);

    return true;
}