#include <iostream>
#include "Item.h"
#include "Inventory.h"
#include "Map.h"

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
	Item* Sword = Item::create("Sword", Item::WEAPON); //create new weapon item.
	Item* Sword1 = Item::create("Chestplate", Item::ARMOUR);
	Item* Sword2 = Item::create("Helmet", Item::ARMOUR);
	Item* Sword3 = Item::create("HealthPot", Item::CONSUMABLES);

	Inventory Container; 
	Container.addItem(Sword);
	Container.addItem(Sword1);
	Container.addItem(Sword2);
	Container.addItem(Sword3);

	Sword->addDesc("This is a wooden sword. This deals -5 HP to enemies."); // use inside () to add Description of item.
	
	Map test;

	test.townMap(); 


	Container.showInventory();
	Container.showInventory();

	delete Sword;
	delete Sword1;
	delete Sword2;
	delete Sword3;

	


}