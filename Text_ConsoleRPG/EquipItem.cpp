#include "EquipItem.h"
#include "LogMacros.h"
#include "Player.h"

EquipItem::EquipItem(const std::string& name, size_t maxStack, int sellPrice, int buyPrice, int atk, int hp)
{
    itemType = EItemType::Equip;
    itemName = name;
    maxStackCount = maxStack;
    sellCost = sellPrice;
    buyCost = buyPrice;
    additionalAttack = atk;
    additionalHP = hp;
}

bool EquipItem::ApplyEffect(const std::shared_ptr<Character> character)
{
    if (isEquipped)
    {
        LOG_INFO("#EquipItem : 이미 장착된 아이템입니다.");
        return false;
    }

    // 캐릭터 nullptr 방어
    if (character != nullptr)
    {
        // 적용 캐릭터의 타입 Player 확인
        if (auto player = std::dynamic_pointer_cast<Player>(character))
        {
            LOG_INFO("#EquipItem : 아이템(" + itemName + ") 장착");
            player->setATK(player->getATK() + additionalAttack);
            player->setMaxHP(player->getMaxHP() + additionalHP);
            isEquipped = true;

            player->SetEquipItem(shared_from_this());
            return true;
        }
    }
    return false;
}

bool EquipItem::RevertEffect(const std::shared_ptr<Character> character)
{
    if (!isEquipped)
    {
        LOG_INFO("#EquipItem : 장착되지 않은 아이템입니다.");
        return false;
    }

    // 캐릭터 nullptr 방어
    if (character != nullptr)
    {
        // 적용 캐릭터의 타입 Player 확인
        if (auto player = std::dynamic_pointer_cast<Player>(character))
        {
            LOG_INFO("#EquipItem : 아이템(" + itemName + ") 장착해제");
            player->setATK(player->getATK() - additionalAttack);
            player->setMaxHP(player->getMaxHP() - additionalHP);
            isEquipped = false;
            return true;
        }
    }
    return false;
}
