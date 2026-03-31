#pragma once
#include "Character.h"
#include "Inventory.h"
#include "Money.h"
#include <memory> // std::shared_ptr 사용을 위해 추가

class Player : public Character
{
public:
    // 부모 생성자를 호출해야 합니다.
    Player(std::string name, std::string job);
    virtual ~Player() = default;

    // 순수 가상 함수였던 attack을 반드시 구현해야 합니다. (override 키워드 권장)
    virtual void attack(std::shared_ptr<Character> enemy) override;

    // 부모의 기능을 확장하고 싶다면 printStatus도 재정의할 수 있습니다.
    virtual void printStatus() override;
	virtual void takeDamage(int amount) override; // 데미지를 입는 함수도 재정의

    std::shared_ptr<Inventory> GetInventory() { return inventory; }; // 플레이어의 인벤토리
    std::shared_ptr <Money> GetMoney() { return money; }; // 플레이어의 돈

	bool BuyItem(std::shared_ptr<ItemBase> item, size_t amount);  
    bool SellItem(std::shared_ptr<ItemBase> item, size_t amount);

    void addExp(int amount); // 경험치 획득 함수
    void levelUp();          // 레벨업 처리 함수

    void addMoney(int amount);
    
    // 플레이어가 임의 장비 아이템을 착용하는 함수
    void SetEquipItem(std::shared_ptr<ItemBase> equipItem);

private:
    std::string job; // 플레이어만의 전용 속성 추가

	// 플레이어는 인벤토리와 돈을 가지고 있습니다. (Character에는 없는 속성)
	std::shared_ptr<Inventory> inventory; // 플레이어의 인벤토리
    std::shared_ptr<Money> money; // 플레이어의 돈

    std::shared_ptr<ItemBase> equipItem;    // 플레이어가 현재 장착중인 장비 아이템
};