#include "Armour.h"
#include <iostream>

std::string Armour::getItemName()
{
	return name;
}

Armour::Armour(std::string n)
{
	name = n;
	std::cout << "Armour created\n";
}

Armour::~Armour() {}
