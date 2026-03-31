#include "Player.h"
#include <iostream>
#include <windows.h>
#include "EquipItem.h"


// 부모 생성자 Character(name)을 호출하여 이름을 초기화합니다.
Player::Player(std::string name, std::string job) : Character(name)
{
    this->job = job;
    this->level = 1;      // 기본값 초기화
    this->maxHP = 100;
    this->currentHP = 100;
    this->ATK = 12;
    this->exp = 0;
    this->speed = 5;

    // 인벤토리 생성

    inventory = std::make_shared<Inventory>(10);
    money = std::make_shared<Money>(1000);
}

bool Player::BuyItem(std::shared_ptr<ItemBase> item, size_t amount)
{
    size_t totalCost = item->buyCost * amount;

    // 1. 돈이 충분한가?
    if (!money->canAfford(totalCost)) {
        std::cout << "골드가 부족합니다!" << std::endl;
        return false;
    }

    // 2. 인벤토리에 공간이 있는가?
    if (inventory->GetAcceptableAmount(item) < amount) {
        std::cout << "인벤토리에 공간이 부족합니다!" << std::endl;
        return false;
    }

    // 3. 결제 및 아이템 추가
    money->spendMoney(totalCost); // 돈 차감
    inventory->AddItem(item, amount); // 아이템 추가
    return true;
}

bool Player::SellItem(std::shared_ptr<ItemBase> item, size_t amount)
{
    size_t totalCost = item->sellCost * amount;

    // 1. 인벤토리에 아이템이 충분한가?
    for (const auto& pair : inventory->container)
    {
        if (pair.first->itemName != item->itemName)
        {
            std::cout << "아이템이 없습니다!" << std::endl;
            return false;
        }
        if (pair.second < amount)
        {
            std::cout << "수량이 부족합니다!" << std::endl;
            return false;
        }
    }

    // 2. 결제 및 아이템 추가
    money->addMoney(totalCost); // 돈 획득
    inventory->RemoveItem(item, amount); // 아이템 제거
    return true;
}

void Player::attack(std::shared_ptr<Character> enemy)
{
    // 여기에 플레이어만의 공격 로직 구현 (나중에 Enemy의 takeDamage 호출 등)
    if (enemy == nullptr) return;

    bool isCritical = (rand() % 100) < 20; // 20% 확률로 크리티컬 히트
    int finalDamage = isCritical ? this->ATK * 2 : this->ATK;
    if (isCritical)
    {
        // 시각적 연출: 강렬한 문구 출력
        std::cout << "[!! CRITICAL HIT !!]" << std::endl;
        std::cout << "[플레이어] " << this->name << "의 치명적인 일격!" << std::endl;
    }
    else {
        std::cout << "[플레이어] " << this->name << "의 맹렬한 공격!" << std::endl;
    }   
	Sleep(500); // 공격 모션을 표현하기 위한 딜레이 (500ms)

    // 플레이어의 공격력(ATK)을 적의 takeDamage로 전달
    enemy->takeDamage(finalDamage);
}

void Player::printStatus()
{
    std::cout << "========== PLAYER STATUS ==========" << std::endl;
    std::cout << "직업: " << job << std::endl;
    // 부모 클래스의 printStatus 내용을 그대로 사용하고 싶다면 아래처럼 호출 가능합니다.
    Character::printStatus();
    std::cout << "===================================" << std::endl;
}

void Player::addExp(int amount) {
    this->exp += amount;
    std::cout << amount << "의 경험치를 획득했습니다!" << std::endl;

    // 레벨업 조건: 현재 레벨 * 100 이상의 경험치 필요
    if (this->exp >= this->level * 100) {
        levelUp();
    }
    
    std::cout << "(현재 경험치: " << exp << ")" << std::endl;
	Sleep(500); // 경험치 획득 모션을 표현하기 위한 딜레이 (500ms)
}

void Player::levelUp() {
    this->exp -= (this->level * 100);
    this->level++; //

    // 성장 수치 적용
    this->maxHP += 60;
    this->currentHP = this->maxHP; // 레벨업 시 체력 풀회복은 국룰이죠!
    this->ATK += 7;
    this->speed += 8;

    std::cout << "\n LEVEL UP!" << std::endl;
    std::cout << "레벨이 " << level << "이(가) 되었습니다! 모든 능력치가 상승합니다." << std::endl;
    Sleep(1000);
}

void Player::takeDamage(int amount) {
    // 회피 확률 계산 (예: 속도 1당 0.5% 확률, 최대 30%)
    int dodgeChance = (this->speed > 60) ? 30 : this->speed / 2;

    if ((rand() % 100) < dodgeChance) {
        std::cout << "\n 휘릭! " << name << "이(가) 공격을 가볍게 피했습니다!" << std::endl;
        Sleep(500);
        return; // 데미지를 입지 않고 함수 종료
    }

    // 회피 실패 시 부모 클래스의 기본 데미지 로직 실행
    Character::takeDamage(amount);
}

void Player::addMoney(int amount)
{
    this->money->addMoney(amount); // 돈 추가
    std::cout << amount << "골드를 획득했습니다! (현재: " << this->money->getCurrentMoney() << ")" << std::endl;
    Sleep(1000);
}

// 플레이어가 임의 장비 아이템을 착용하는 함수
void Player::SetEquipItem(std::shared_ptr<ItemBase> equipItem)
{
    if (this->equipItem != nullptr)
    {
        // 기존에 장착중인 아이템이 존재할 때,
        if (auto equipment = std::dynamic_pointer_cast<EquipItem>(this->equipItem))
        {
            // 장착중인 아이템의 효과를 제거
            equipment->RevertEffect(this->shared_from_this());
        }
    }
    
    // 장착중인 아이템 설정
    this->equipItem = equipItem;
}

