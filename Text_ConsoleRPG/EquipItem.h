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

	EquipItem(const std::string& name, size_t maxStack, int sellCost, int buyCost, int atk, int hp);

	bool isCharacterEquipped() const {
		return isEquipped;
	}

	// IApplicablePattern을(를) 통해 상속됨
	bool ApplyEffect(const std::shared_ptr<Character> character) override;

	// IReversiblePattern을(를) 통해 상속됨
	bool RevertEffect(const std::shared_ptr<Character> character) override;
};