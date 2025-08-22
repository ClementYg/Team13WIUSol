#include "Game.h"
#include <iostream>
#include "Item.h"
#include "Inventory.h"
#include "Map.h"
#include "startScreen.h"

#include <string>
#include "NPC.h"
#include "Master.h"
#include "Merchant.h"
#include "Position.h"

int main() {
	// STEPS FOR INVENTORY 
	//Item* sword = Item::create("HP_Potion", Item::HP_POT); //Declare name, SpecificItem
	//Item* sword1 = Item::create("Sword", Item::WOOD_SWORD);

	//Inventory Bag;

	//Bag.addItem(sword); 
	//Bag.addItem(sword1);
	//sword->useItem();
	//sword1->useItem();
	//sword->addDesc("SWORD");
	//
	//Bag.requestInventory();

	//// STEPS FOR MAP 
	Map MapObj;
	MapObj.HarbourMap();
	MapObj.InnerCaveMap();

	/*startScreen();

	Game game;
	game.initGame();

	while (true) {
		game.doTurn();
	}*/

}
//                      _
//                     / \
//                    /|-|\
//  ____________     /_|_|_\
// |            |   /| | | |\
// |            |  /_|#####|_\               __
// |       _    | /| |#####| |\   ==         ||
// |______/ \___|/_|_|_|_|_|_|_\==||=========||=
//  |_|  /   \  |==============|[___]_[_]_[][_]|
//    | /     \ |--------------|[__][_][]_[__]_|
//____|/       \| /-----\|----||***************|___
//oooo| __      | |     ||    ||^----^^--^--^--|ooo
//oooo|| o| []  | |     ||    ||               |ooo
//oooo||  |     | |     ||    ||               |ooo
//=================================================





// kz's design
//                 ^                 ^
//         ^      / \     ^^            ^^
//        / \    /   \   / \          ^/ \^
//       /   \  /     \ /   \    ^    /   \
//      /     \/       \     \  / \  /     \
//     /      /         \     \/   \/       \
//    /      /___________\     \   /         \
//   /___________\| /___________\ /___________\
//        | |     | |    | |/         \| |
//        | |     | |    | |___________| |
//        | |     | |    | |    | |    | |
//        | |     | |    | |    | |    | |
//        | |     | |    | |    | |    | |
//=================================================
//
//                     P
//
//=================================================