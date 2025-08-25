#pragma once
#include "Item.h"
class Weapon : public Item
{
public:

	std::string getItemName();

	void useItem();

	Weapon* duplicate();

	Weapon(std::string n, weaponType, int, int);
	virtual ~Weapon();
private:
	weaponType itemWType; 
};

