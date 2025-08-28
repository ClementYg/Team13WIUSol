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
#include <windows.h>

int main() {

	startScreen();

	playTownsquareBurning();  //  the burning town scene

	evilHeroCutscene();


	Game game;
	game.initGame();


	while (true) {
		game.doTurn();
	}
}
