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
	Item* Sword = new Item("Sword", Item::WEAPON);
	Item* Sword1 = new Item("Sword1", Item::WEAPON);
	Item* Sword2 = new Item("Sword2", Item::WEAPON);
	Item* Sword3 = new Item("Sword3", Item::WEAPON);

	Inventory Container; 
	Container.addItem(Sword);
	Container.addItem(Sword1);
	Container.addItem(Sword2);
	Container.addItem(Sword3);

	Sword->addDesc("This is a wooden sword. This deals -5 HP to enemies."); // use inside () to add Description of item.
	
	Container.showInventory();
	Container.showInventory();

	delete Sword;
	delete Sword1;
	delete Sword2;
	delete Sword3;


}