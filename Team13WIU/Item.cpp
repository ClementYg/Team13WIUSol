#include "Item.h"
#include "Consumable.h"
#include "Weapon.h"
#include <iostream>

int Item::getItemID()
{
	return itemID;
}

void Item::setItemID(int change)
{
	itemID = change; 
}

int Item::getPrice()
{
	return price;
}

bool Item::checkItemSelect()
{
	return isitemSelected;
}

int Item::getQuantity() { return quantity; }
void Item::addQuantity(int change) { quantity += change; }
void Item::setQuantity(int change) { quantity = change; }

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
	price = 0;
	quantity = 0;
	isitemSelected = false;
	itemID = IDCounter;
	IDCounter++;
	IDCounter %= 10; //Check if reach max ID already
	std::cout << "A normal item created\n";
}

Item* Item::create(std::string name, consumeType consumableType, int price, int qty)
{ //If no type is declared of Consumable, i.e Ite m is not consumable, then it will default to unknown
	return new Consumable(name, consumableType, price, qty);
}

Item* Item::create(std::string name, weaponType wType, int price, int qty) {
	return new Weapon(name, wType, price, qty);
}


Item::~Item() {
	std::cout << "item deleted\n";
}

void Item::useItem() {}

