#include "Item.h"
#include "Consumable.h"
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

Item::Item(std::string name)
{
	isitemSelected = false;
	itemID = IDCounter; 
	IDCounter++;
	this->name = name; //Assigns object name to be the function parameter name.	
}

Item* Item::create(Types itemtype) {
	createType = itemtype;
	switch (createType) {
	case CONSUMABLES:
	{
		std::cout << "Consumable Item created\n";
		return new Consumable; 
		break;
	}
	case WEAPON:
	{
		std::cout << "Weapon Item created\n";
		return new Weapon;
		break;
	}
	case ARMOUR:
		std::cout << 
			;
		return new Armour;
		break;

	default:
		std::cout << "No identifiable item-type\n";
	}

}


Item::~Item() {
	std::cout << "item deleted\n";
}

