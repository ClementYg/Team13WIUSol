#include "Merchant.h"
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

// The : NPC(n, x, y, lines) is needed because the NPC has no default constructor (NPC())
// It simply means "When creating a Merchant, call the NPC constructor with these arguments."
Merchant::Merchant(std::string n, int y, int x, char s,std::vector<std::string> lines) : NPC(n, y, x, s,lines)
{

}

Merchant::~Merchant()
{

}

void Merchant::NPCtalk()
{
	for (size_t i = 0; i < dialogue.size(); i++) {
		std::string& line = dialogue[i];

		// make name green
		std::cout << "\033[1;32m" << name << ": " << "\033[0m";
		typeLine(line, 1);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	std::cout << std::endl;
}

void Merchant::addStock(Item* item)
{
	stock.push_back(item);
}

void Merchant::sellStock(int ID, Inventory& playerInv, int qty = 1) // What item to buy, put into player bag, default amount of 1. 
{
	if (ID < 0 || ID >=	 stock.size()) return; //if player choose ID that is not within what Merchant has, return since invalid choice


	Item* itemBought = stock[ID];
	int totalprice = itemBought->getPrice() * qty;  //set to deduct player gold by price of item bought. 
	
	if (itemBought->getQuantity() < qty || playerInv.getGold() < totalprice) //check that shopkeeper has stock and has player enough gold
	{
		std::cout << "You either have insufficient funds to pay for this item or the shopkeeper has no stock left.\n";
		return;
	}

	playerInv.setGold(-totalprice); //deduct gold

	Item* itemDupe = itemBought->duplicate(); 
	itemDupe->setQuantity(qty);
	playerInv.addItem(itemDupe, qty); //add amount of items into playerInv

	itemBought->addQuantity(-qty); //decrease shop stock.

	//if no more stock
	if (itemBought->getQuantity() == 0) {
		stock.erase(stock.begin() + ID); //erase element data of vector at that ID since now bought. 
	}
}
void Merchant::showStock() {
	std::cout << "Stock:\n";
	for (int i = 0; i < stock.size(); i++) {
		std::cout << "ID " << i << " | " << stock[i]->getItemName() << " | Price: " << stock[i]->getPrice() << " | Quantity: " << stock[i]->getQuantity() << '\n';
	}
}