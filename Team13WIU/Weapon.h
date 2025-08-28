#pragma once
#include "Item.h"
class Weapon : public Item
{
public:

	std::string getItemName();
	bool checkWeaponEquipped();

	void useItem(Player* playerRef);

	Weapon* duplicate();

	Weapon(std::string n, weaponType, int, int);
	virtual ~Weapon();
private:
	static Weapon* currentWep;
	weaponType itemWType; 
	bool weaponEquipped;
};

