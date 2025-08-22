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

Item* Item::create(std::string name, consumeType consumableType)
{ //If no type is declared of Consumable, i.e Item is not consumable, then it will default to unknown
	IDCounter++;
	return new Consumable(name, consumableType); 
}

Item* Item::create(std::string name, weaponType wType) {
	IDCounter++;
	return new Weapon(name, wType);
}

Item* Item::create(std::string name, armourType aType) {
	IDCounter++;
	return new Armour(name, aType);
}


Item::~Item() {
	std::cout << "item deleted\n";
}

void Item::useItem() {}

