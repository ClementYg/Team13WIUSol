#include "Inventory.h"
#include <iostream>



void Inventory::showInventory()
{
	bool exitInventory = false;
	while (!exitInventory) {
		for (int i = 0; i < 10; i++) { // SET TO 10 BECAUSE THATS TOTAL SLOTS SO FAR
			if (container[i] != nullptr) { //check that this slot has an item
				{
					if (container[i]->checkItemSelect()) {
						std::cout << ">> ";
					}
					std::cout << "[" << container[i]->getItemID() << "] " << container[i]->getItemName();
					std::cout << std::endl;


					if (container[i]->checkItemSelect()) {
						std::cout << "Description: " << container[i]->getItemDesc() << '\n' << '\n';
					}
				}
			}
		}
		selectItem(); //Ask user if want to select item.
	}
}

void Inventory::selectItem()
{
	int choice;
	std::cout << "Do you want to select an item?\n";
	std::cin >> choice; //used for container ID.
	if (container[choice] != nullptr && choice < 5) { //DOESNT HAVE TO BE 4, TEMPORARY TOTAL AMOUNT OF ITEMS
		if (prevChoice != -1 && container[prevChoice] != nullptr) { // if previous Choice exists, run this code
			container[prevChoice]->select(0); // change selection to false, DESELECT
		}
		container[choice]->select(1);
		prevChoice = choice;
	}
} //tells user to select and also deselects previously selected


void Inventory::addItem(Item* itemObj)
{
	container[itemObj->getItemID()] = itemObj; // get itemID and assign item pointer to container ID.
}
void Inventory::removeItem(Item* itemObj) {
	container[itemObj->getItemID()] = nullptr; 
	delete itemObj; 
}

Inventory::Inventory() {
	for (int i = 0; i < 10; i++) { //Initialisation. Over here is 10 for Max Size of Inventory. SUBJECT TO CHANGE.
		container[i] = nullptr;
	}
	prevChoice = -1;
}