#pragma once
#include "Item.h"
#include "Player.h"
class Player;
class Item;

class Inventory // is just a storage of items
{
private:
	Item* container[10]; // storage container for items
	int prevChoice;
	int goldStored = 0;
	static int totalItems; 
public: 

	void showInventory(Player* playerRef);
	void requestInventory(Player* playerRef);
	void selectItem();
	void printInventory(Player* playerRef);
	int getTotalItems();

	void addItem(Item* itemObj, int);
	void useItem(int slot, Player* playerRef);
	void removeItem(Item* itemObj);
	
	int getGold();
	void setGold(int);
	Inventory();
};

