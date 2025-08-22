#include "Consumable.h"
#include <iostream>

std::string Consumable::getItemName()
{
	return name;
}

Consumable::Consumable(std::string n)
{
	name = n;
	std::cout << "A created\n";
}

Consumable::~Consumable() {}
