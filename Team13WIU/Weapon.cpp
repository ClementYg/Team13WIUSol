#include "Weapon.h"
#include <iostream>

std::string Weapon::getItemName()
{
	return name;
}

bool Weapon::checkWeaponEquipped()
{
	return weaponEquipped;
}

Weapon* Weapon::currentWep = nullptr;

void Weapon::useItem(Player* playerRef)
{
	if (currentWep != this) // check if weapon ptr saved i cwep is the one that called function 
	{
		if (currentWep) currentWep->weaponEquipped = false; //set current to false
		currentWep = this;
		weaponEquipped = true;

		switch (itemWType) {
		case WOOD_SWORD:
		{
			playerRef->setWeaponDmg(5); //if equipped, enhance damager
			break;
		}
		case STEEL_SWORD:
		{
			playerRef->setWeaponDmg(15); //if equipped, enhance damager
			break;

		}
		case MYTHRIL_SWORD:
		{
			playerRef->setWeaponDmg(18); //if equipped, enhance damager
			break;
		}
		default: std::cout << "error equipping weapon\n";

		}
		std::cout << "Weapon Equipped\n";
	}
	else {
		weaponEquipped = false;
		currentWep = nullptr;
		playerRef->setWeaponDmg(12);
		std::cout << "Weapon Unequipped\n";

	}

}

Weapon* Weapon::duplicate() {
	return new Weapon(*this);
}


Weapon::Weapon(std::string n, weaponType type, int price, int qty)
{
	itemWType = type;
	name = n;
	this->price = price;
	quantity = qty;
	weaponEquipped = false;
	std::cout << "A weapon created\n";
}

Weapon::~Weapon() {}
