#pragma once
#include "Item.h"
class Inventory // is just a storage of items
{
private:
	Item* container[10]; // storage container for items
public: 

	void showInventory();

	void addItem(Item* itemObj);

	void removeItem(Item* itemObj);

	Inventory();
};

