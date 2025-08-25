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
		break;
	}
	case FIRE_SWORD: 
	{
		std::cout << "Fire Sword equipped\n"; 
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
	std::cout << "A weapon created\n";
}

Weapon::~Weapon() {}
