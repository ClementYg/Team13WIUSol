#include "Weapon.h"
#include <iostream>

std::string Weapon::getItemName()
{
	return name;
}

Weapon::Weapon(std::string n)
{
	name = n;
	std::cout << "A weapon created\n";
}

Weapon::~Weapon() {}
