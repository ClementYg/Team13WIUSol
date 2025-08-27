#include "Game.h"
#include <iostream>
#include "Item.h"
#include "Inventory.h"
#include "Map.h"
#include "startScreen.h"
#include "TownSquareBurning.h"
#include "GrowingUpCutscene.h"
#include <string>
#include "NPC.h"
#include "Merchant.h"
#include "Position.h"

int main() {
	// STEPS FOR INVENTORY. CREATE(NAME, ITEM, PRICE, QUANTITY)
	//Item* sword = Item::create("HP_Potion", Item::HP_POT,50, 1); //Declare name, SpecificItem
	//Item* sword1 = Item::create("Sword", Item::WOOD_SWORD, 50, 1);

	//Inventory Bag;

	//Bag.addItem(sword,1); 
	//Bag.addItem(sword1,1);
	//sword->useItem();
	//sword1->useItem();
	//sword->addDesc("SWORD");
	//
	//Bag.requestInventory();
	

	////// STEPS FOR MAP 
	//Map MapObj;
	//MapObj.HarbourMap();
	//MapObj.ForestMap();
	//MapObj.Inn();

 // Display the animated start screen
	startScreen();


	 playTownsquareBurning();  //  the burning town scene

	 evilHeroCutscene();


	Game game;
	game.initGame();

	while (true) {
 		game.doTurn();
	}
}
