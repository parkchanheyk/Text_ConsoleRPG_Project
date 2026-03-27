//Shop.cpp
#include "Shop.h"
#include "ItemBase.h"

class ItemBase;

void Shop::addStock(std::shared_ptr<ItemBase> item, int count)
{
    if (!item) return;
    stock[item] += count;
}

bool Shop::hasStock(std::shared_ptr<ItemBase> item, int count) const
{
    auto it = stock.find(item);
    return (it != stock.end() && it->second >= count);
}

void Shop::reduceStock(std::shared_ptr<ItemBase> item, int count)
{
    auto it = stock.find(item);
    if (it == stock.end()) return;

    it->second -= count;
    if (it->second <= 0)
        stock.erase(it);
}

void Shop::addBuyBack(std::shared_ptr<ItemBase> item, int count)
{
    if (!item) return;
    buyBackStock[item] += count;
}

bool Shop::hasBuyBack(std::shared_ptr<ItemBase> item, int count) const
{
    auto it = buyBackStock.find(item);
    return (it != buyBackStock.end() && it->second >= count);
}

void Shop::reduceBuyBack(std::shared_ptr<ItemBase> item, int count)
{
    auto it = buyBackStock.find(item);
    if (it == buyBackStock.end()) return;

    it->second -= count;
    if (it->second <= 0)
        buyBackStock.erase(it);
}

const std::map<std::shared_ptr<ItemBase>, int>& Shop::getStock() const
{
    return stock;
}

const std::map<std::shared_ptr<ItemBase>, int>& Shop::getBuyBack() const
{
    return buyBackStock;
}