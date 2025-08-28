#include "Consumable.h"
#include <iostream>

std::string Consumable::getItemName()
{
	return name;
}

Consumable::Consumable(std::string n, consumeType type, int price, int qty)
{
	name = n;
	std::cout << "A created\n";
	this->price = price;
	quantity = qty;

	itemCType = type;

}

void Consumable::useItem(Player* playerRef) {

	switch (itemCType) {
	case HP_POT:
	{
		std::cout << "HP RECOVERED BY 10 HERE\n";
		//player restore health function here
		playerRef->addPlayerHP(20);
		addQuantity(-1);
		break;
	}
	case MANA_POT: {
		std::cout << "MANA RECOVERED BY 10 HERE\n";
		//player restore mana here
		playerRef->addPlayerMana(20);
		addQuantity(-1);
		break;
	}
	case STRENGTH_POT: {
		std::cout << "STRENGTH INCREASE BY 10 HERE\n";

		break;
	}
	default: {
		std::cout << "Invalid ItemType given\n";
	}
	}
}

Consumable* Consumable::duplicate() {
	return new Consumable(*this);
}

Consumable::~Consumable() {}
