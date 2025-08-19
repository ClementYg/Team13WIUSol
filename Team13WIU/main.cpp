#include <iostream>
#include "Item.h"
#include "Inventory.h"

int main() {

	//for (int i = 0; i < 120; i++) {
	//	std::cout << '-';
	//}
	//for (int i = 0; i < 24; i++) {
	//	std::cout << std::endl;
	//}
	//for (int i = 0; i < 120; i++) {
	//	std::cout << '-';
	//}
	Item* Sword = new Item("Sword");
	Item* Sword1 = new Item("Sword1");
	Item* Sword2 = new Item("Sword2");
	Item* Sword3 = new Item("Sword3");

	Inventory Container; 
	Container.addItem(Sword);
	Container.addItem(Sword1);
	Container.addItem(Sword2);
	Container.addItem(Sword3);
	


	Container.showInventory();


}