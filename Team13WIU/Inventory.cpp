#include "Inventory.h"
#include <iostream>



void Inventory::showInventory()
{

	for (int i = 0; i < 10; i++) {
		if (container[i] != nullptr && container[i]->checkItemSelect()) {
			std::cout << ">> ";
		}
		if (container[i] != nullptr) {
			std::cout << "[" << container[i]->getItemID() << "]" << container[i]->getItemName();
			std::cout << std::endl;
		}
	}

}

void Inventory::selectItem()
{
	int choice;
	std::cout << "select Item\n";
	std::cin >> choice;

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