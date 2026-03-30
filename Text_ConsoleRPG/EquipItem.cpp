#include "EquipItem.h"

EquipItem::EquipItem(const std::string& name, int atk, int def)
{
    itemType = EItemType::Equip;
    itemName = name;
    additionalAttack = atk;
    additionalDefense = def;
}

void EquipItem::Equip(Character& target)
{
    if (isEquipped)
    {
        std::cout << "이미 장착한 아이템입니다: " << itemName << std::endl;
        return;
    }

    std::cout << "아이템(" << itemName << ") 장착\n";
    target.setATK(target.getATK() + additionalAttack);
    target.setMaxHP(target.getMaxHP() + additionalDefense);
    isEquipped = true;
}

void EquipItem::UnEquip(Character& target)
{
    if (!isEquipped)
    {
        std::cout << "아이템을 장착하고있지 않습니다: " << itemName << std::endl;
        return;
    }

    std::cout << "아이템(" << itemName << ") 장착해제\n";
    target.setATK(target.getATK() - additionalAttack);
    target.setMaxHP(target.getMaxHP() - additionalDefense);
    isEquipped = false;
}