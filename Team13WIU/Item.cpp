#include "Item.h"
#include "Consumable.h"
#include "Weapon.h"
#include "Armour.h"
#include <iostream>

int Item::getItemID()
{
	return itemID;
}

bool Item::checkItemSelect()
{
	return isitemSelected;
}

void Item::select(int selected) //if selected 1, means user wants to select. if selected 0, change item to not be selected
{
	if (selected == 1) {
		isitemSelected = true;
	}
	else isitemSelected = false;
}

std::string Item::getItemName() { return name; }

std::string Item::getItemDesc() { return itemDesc; }

void Item::addDesc(std::string description) {
	 this->itemDesc = description;
}

int Item::IDCounter = 0;

Item::Item()
{
	isitemSelected = false;
	itemID = IDCounter;
	std::cout << "A normal item created\n";
}

Item* Item::create(std::string name, Types itemtype) {
	IDCounter++;
	switch (itemtype) {
	case CONSUMABLES:
	{
		return new Consumable(name); 
		break;
	}
	case WEAPON:
	{
		return new Weapon(name);
		break;
	}
	case ARMOUR:
		return new Armour(name);
		break;

	default:
		std::cout << "No identifiable item-type\n";
	}

}


Item::~Item() {
	std::cout << "item deleted\n";
}

