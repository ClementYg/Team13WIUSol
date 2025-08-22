#include "Armour.h"
#include <iostream>

std::string Armour::getItemName()
{
	return name;
}

//INITIALISE ITEMATYPE
Armour::Armour(std::string n,armourType type)
{
	name = n;
	itemAType = type; 
	std::cout << "Armour created\n";
}

void Armour::useItem() {

	switch (itemAType) {
	case WOOD_HELM:
	{
		std::cout << "WOOD_HELMET EQUIPPED\n";
		break;
	}
	case WOOD_CHEST:
	{
		std::cout << "WOOD_CHESTPLATE EQUIPPED\n";
		break;
	}
	case WOOD_LEGGS: {
		std::cout << "WOOD_LEGGINGS EQUIPPED\n";
		break;
	}
	default: std::cout << "NOTHING IS EQUIPPED\n";
	}
}

Armour::~Armour() {}
