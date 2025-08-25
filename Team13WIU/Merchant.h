#pragma once
#include "NPC.h"
#include <vector>
#include "Item.h"
#include "Inventory.h"
class Merchant : public NPC
{
private:
	std::vector<Item*> stock; //Merchant's inventory of items

public:
	//char IsTrade = ' ';
	Merchant(std::string n, int y, int x, char s,std::vector<std::string> lines = {});
	~Merchant();
	

	void NPCtalk();
	void addStock(Item*); //add in the item u want into the bag
	void sellStock(int ID, Inventory& playerInv, int quantity); //use inventory& as we want to slightly modify bag to hold new items
	void showStock();

	void trade();
};

