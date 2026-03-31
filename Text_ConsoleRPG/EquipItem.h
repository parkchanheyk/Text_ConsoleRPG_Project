#pragma once

#include <iostream>
#include "ItemBase.h"

class EquipItem : public ItemBase, public IApplicablePattern, public IReversiblePattern
{
private:
	int additionalAttack = 0;
	int additionalHP = 0;
	bool isEquipped = false;

public:
	EquipItem() {}

	EquipItem(const std::string& name, int atk, int HP, int buyCost, int sellCost);

	bool isCharacterEquipped() const {
		return isEquipped;
	}

	// IApplicablePattern을(를) 통해 상속됨
	bool ApplyEffect(const std::shared_ptr<Character> character) override;

	// IReversiblePattern을(를) 통해 상속됨
	bool RevertEffect(const std::shared_ptr<Character> character) override;
};