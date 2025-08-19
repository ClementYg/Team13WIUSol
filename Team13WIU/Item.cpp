#include "Item.h"
#include <iostream>

int Item::getItemID()
{
	return itemID;
}

void Item::selectItem()
{
	isitemSelected = true;
}

std::string Item::getItemName()
{
	return name;
}

int Item::IDCounter = 0;

Item::Item(std::string name)
{
	isitemSelected = false;
	itemID = IDCounter;
	IDCounter++;
	this->name = name; //Assigns object name to be the function parameter name.

}


Item::~Item() {
	std::cout << "item deleted\n";
}

