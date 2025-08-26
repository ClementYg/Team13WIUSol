#include "Inventory.h"
#include <iostream>
#include "conio.h"


void Inventory::showInventory()
{
	bool exitInventory = false; //local variable declaration

	while (!exitInventory) {
		printInventory();

		std::cout << "What do you wish to do with your backpack?\n" << "Press X to close your Bag.\nPress C to select an item.\n\n";
		char userChoice = _getch();
		if (userChoice == 'X' || userChoice == 'x') {
			exitInventory = true;
		}
		else if (userChoice == 'C' || userChoice == 'c') {
			selectItem();
		}
	}
}

void Inventory::requestInventory() {
	std::cout << "What do you wish to do with your backpack? Press E to Open, Press X to Close.\n";
	char userChoice = _getch();
	if (userChoice == 'E' || userChoice == 'e') {
		showInventory(); //signify open 
	}
	else {}
}

void Inventory::selectItem()
{
	std::cout << "Pick the ID of the item you wish to select\n\n"; //used for container ID.
	int choice = _getch() - 48;
	if (container[choice] != nullptr && choice < 10) { //DOESNT HAVE TO BE 4, TEMPORARY TOTAL AMOUNT OF ITEMS. MINUS 48 BECAUSE OF ASCII
		if (prevChoice != -1 && container[prevChoice] != nullptr) { // if previous Choice exists, run this code
			container[prevChoice]->select(0); // change selection to false, DESELECT
		}
		container[choice]->select(1);
		prevChoice = choice;
	}
} //tells user to select and also deselects previously selected

void Inventory::printInventory()
{
	//display stuff
	for (int i = 0; i < 10; i++) { // SET TO 10 BECAUSE THATS TOTAL SLOTS SO FAR
		if (container[i] != nullptr) { //check that this slot has an item
			{
				if (container[i]->checkItemSelect()) {
					std::cout << ">> ";
				}

				std::cout << "[" << i << "] " << container[i]->getItemName();
				std::cout << std::endl << std::endl;

				if (container[i]->checkItemSelect()) {
					std::cout << "Description: " << container[i]->getItemDesc() << '\n' << '\n';
				}
			}
		}
	}
	for (int i = 0; i < 10; i++) { //use item/active usages
		if (container[i] != nullptr) {
			if (container[i]->checkItemSelect()) {
				std::cout << "Do you wish to use this item? [Y/N] \n";
				char choice = _getch();
				if (choice == 'Y') {
					useItem(i); //use item with that index
				}
			}
		}
	}
}


void Inventory::addItem(Item* itemObj, int qty)
{
	int usableSlot = -1;
	for (int i = 0; i < 10; i++) { //total slots so far. Stacks by checking if there is any duplicate
		if (container[i] == nullptr && usableSlot == -1) {
			usableSlot = i;//check each slot, if no currently no usable slot and container is null, then this slot can be used
		}
		else if (container[i] != nullptr && container[i]->getItemName() == itemObj->getItemName()) { //if item already exists in player Inventory, then say quantity increase instead of 2 same objects
			container[i]->setQuantity(qty);
			delete itemObj;
			return;
		}
	}

	//if doesnt already exist
	if (usableSlot != -1) {// found usableSlot
		container[usableSlot] = itemObj->duplicate();
	}
	else std::cout << "Bag is full\n";



}

void Inventory::useItem(int slot) {
	if (!container[slot]->checkItemSelect()) {
		return;
	} //check if selected

	container[slot]->useItem();

	if (container[slot]->getQuantity() <= 0) {
		delete container[slot];
		container[slot] = nullptr;
	}
}
void Inventory::removeItem(Item* itemObj) {
	container[itemObj->getItemID()] = nullptr;
	delete itemObj;
}

int Inventory::getGold()
{
	return goldStored;
}

void Inventory::setGold(int amountChanged) {
	goldStored += amountChanged;
}

Inventory::Inventory() {
	for (int i = 0; i < 10; i++) { //Initialisation. Over here is 10 for Max Size of Inventory. SUBJECT TO CHANGE.
		container[i] = nullptr;
	}
	prevChoice = -1;
}