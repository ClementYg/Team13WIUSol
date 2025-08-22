#include "Consumable.h"
#include <iostream>

std::string Consumable::getItemName()
{
	return name;
}

Consumable::Consumable(std::string n, consumeType type)
{
	name = n;
	std::cout << "A created\n";

	itemCType = type;
}

void Consumable::useItem() {

	switch (itemCType) {

	case HP_POT:
	{
		std::cout << "HP RECOVERED BY 10 HERE\n";

		break;
	}
	case MANA_POT: {
		std::cout << "MANA RECOVERED BY 10 HERE\n";

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

Consumable::~Consumable() {}
