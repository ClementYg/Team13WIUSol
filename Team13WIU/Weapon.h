#pragma once
#include "Item.h"
class Weapon : public Item
{
public:

	std::string getItemName();

	void useItem();

	Weapon(std::string n, weaponType);
	virtual ~Weapon();
private:
	weaponType itemWType; 
};

