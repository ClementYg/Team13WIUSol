#pragma once
#include "Item.h"
class Weapon : public Item
{
public:
	std::string getItemName();

	Weapon(std::string n);
	virtual ~Weapon();
};

