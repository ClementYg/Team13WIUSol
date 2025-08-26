#pragma once
#include "Item.h"
class Inventory // is just a storage of items
{
private:
	Item* container[10]; // storage container for items
	int prevChoice;
	int goldStored = 0; 
public: 

	void showInventory();
	void requestInventory();
	void selectItem();
	void printInventory();

	void addItem(Item* itemObj, int);
	void useItem(int slot);
	void removeItem(Item* itemObj);
	
	int getGold();
	void setGold(int);
	Inventory();
};

