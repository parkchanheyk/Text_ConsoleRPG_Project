//ShopUI.cpp
#include "ShopUI.h"
#include "Shop.h"
#include "Money.h"
#include "TransactionManager.h"
#include "ItemBase.h"
#include <iostream>
#include <vector>
#include <conio.h>

void ShopUI::showMenu()
{
    std::cout << "\n{ 1. 구매  2. 판매  3. 재구매  4. 종료 }\n";
}

std::shared_ptr<ItemBase> ShopUI::selectItem(const std::map<std::shared_ptr<ItemBase>, int>& items)
{
    std::vector<std::shared_ptr<ItemBase>> itemList;

    int index = 1;
    for (auto& pair : items)
    {
        auto item = pair.first;
        int count = pair.second;

        std::cout << index << ". " << item->itemName
            << " (수량: " << count
            << ", 가격: " << item->buyCost << ")\n";

        itemList.push_back(item);
        index++;
    }

    int choice;
    std::cin >> choice;

    if (choice < 1 || choice > itemList.size())
        return nullptr;

    return itemList[choice - 1];
}

void ShopUI::run(Shop& shop, Money& money)
{
    while (true)
    {
        std::cout << "\n==============={상점 입장}===============" << std::endl;
        std::cout << "[현재 돈: " << money.getCurrentMoney() << "]\n";
        showMenu();

        int key = _getch();

        if (key == '4')
        {
            std::cout << "\n==============={상점 퇴장}===============" << std::endl;
            break;
        }

        int count;
        std::shared_ptr<ItemBase> item = nullptr;

        switch (key)
        {
        case '1': // 구매
            item = selectItem(shop.getStock());
            if (!item) break;

            std::cout << "수량 입력: ";
            std::cin >> count;

            TransactionManager::buyItem(shop, item, count, money);
            break;

        case '2': // 판매
            item = selectItem(shop.getStock());
            if (!item) break;

            std::cout << "수량 입력: ";
            std::cin >> count;

            TransactionManager::sellItem(shop, item, count, money);
            break;

        case '3': // 재구매
            item = selectItem(shop.getBuyBack());
            if (!item) break;

            std::cout << "수량 입력: ";
            std::cin >> count;

            TransactionManager::buyBackItem(shop, item, count, money);
            break;
        default:
            std::cout << "(*경고) 잘못된 입력입니다." << std::endl;
            break;
        }
    }
}