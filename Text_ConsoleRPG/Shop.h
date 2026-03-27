//Shop.h
#pragma once
#include <map>
#include <memory>

class ItemBase;

class Shop {
private:
    std::map<std::shared_ptr<ItemBase>, int> stock;
    std::map<std::shared_ptr<ItemBase>, int> buyBackStock;

public:
    void addStock(std::shared_ptr<ItemBase> item, int count);
    bool hasStock(std::shared_ptr<ItemBase> item, int count) const;
    void reduceStock(std::shared_ptr<ItemBase> item, int count);

    void addBuyBack(std::shared_ptr<ItemBase> item, int count);
    bool hasBuyBack(std::shared_ptr<ItemBase> item, int count) const;
    void reduceBuyBack(std::shared_ptr<ItemBase> item, int count);

    const std::map<std::shared_ptr<ItemBase>, int>& getStock() const;
    const std::map<std::shared_ptr<ItemBase>, int>& getBuyBack() const;
};