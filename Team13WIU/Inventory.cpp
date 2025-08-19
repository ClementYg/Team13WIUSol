#include "Inventory.h"
#include <iostream>



void Inventory::showInventory()
{

	for (int i = 0; i < 10; i++) {
		if (itemSelected) {
			std::cout << ">> "; //Show visually that item is selected
		}
		if (container[i] != nullptr) {
			std::cout << "[" << container[i]->getItemID() << "]" << container[i]->getItemName();
			std::cout << std::endl;
		}
	}

}

void Inventory::selectItem()
{
	std::cout << "Which Item do you want to select: \n";
	int pickedItem = 0; //this is for std::cin, user choice
	std::cin >> pickedItem;

}

void Inventory::addItem(Item* itemObj)
{
	container[itemObj->getItemID()] = itemObj;
}

void Inventory::removeItem(Item* itemObj) {
	container[itemObj->getItemID()] = nullptr; 
	delete itemObj; 
}

Inventory::Inventory() {
	for (int i = 0; i < 10; i++) { //Initialisation. Over here is 10 for Max Size of Inventory. SUBJECT TO CHANGE.
		container[i] = nullptr;
	}
}