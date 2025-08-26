#include "Weapon.h"
#include <iostream>

std::string Weapon::getItemName()
{
	return name;
}

void Weapon::useItem()
{
	switch (itemWType) {
	case WOOD_SWORD:
	{
		std::cout << "Wood Sword equipped\n";
		WSequipped = true;
		break;
	}
	case STEEL_SWORD:
	{
		std::cout << "Steel Sword equipped\n";

	}
	case FIRE_SWORD: 
	{
		std::cout << "Fire Sword equipped\n"; 
		FSequipped = true; //add in combat system later. If specific type of weapon in use, +10 to dmg etc... 
		break;
	}
	default: std::cout << "error equipping weapon\n";

	}
}

Weapon* Weapon::duplicate() {
	return new Weapon(*this);
}

Weapon::Weapon(std::string n, weaponType type,int price,int qty)
{
	itemWType = type;
	name = n;
	this->price = price;
	quantity = qty;
	FSequipped = false; 
	WSequipped = false;
	std::cout << "A weapon created\n";
}

Weapon::~Weapon() {}
