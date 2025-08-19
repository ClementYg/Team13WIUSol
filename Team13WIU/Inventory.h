#pragma once
#include "Item.h"
class Inventory // is just a storage of items
{
private:
	Item* container[10]; // storage container for items
	int prevChoice;
public: 

	void showInventory();
	void selectItem();

	void addItem(Item* itemObj);
	void removeItem(Item* itemObj);

	Inventory();
};

