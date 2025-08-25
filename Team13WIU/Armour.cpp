#include "Armour.h"
#include <iostream>

std::string Armour::getItemName()
{
	return name;
}

//INITIALISE ITEMATYPE
Armour::Armour(std::string n, armourType type, int price, int qty)
{
	name = n;
	itemAType = type;
	quantity = qty;
	this->price = price;
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

Armour* Armour::duplicate()
{	
	Armour* clone = new Armour(*this);
	clone->setItemID(this->getItemID()); //set clone ID to be same as previous so that no "change" is done. 
	return clone;
}

Armour::~Armour() {}
