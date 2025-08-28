#include "Game.h"
#include "Player.h"
#include "Enemy1.h"
#include "NPC.h"
#include "Merchant.h"
#include "Enemy.h"
#include "Map.h"
#include "BattleArena.h" 
#include "BearBattle.h"
#include <conio.h>
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdlib>
#include <Windows.h>

using namespace std;



Game::Game()
{
	InInn = true;
	InTown = false;
	InForest = false;
	InHarbour = false;
	InOusideCave = false;
	InInsideCave = false;
	
	NarraInn = true;
	NarraTown = true;
	NarraForest = true;
	NarraHarbour = true;
	NarraOutsideCave = true;
	NarraInsideCave = true;

	BKAlive = true;
	BearAlive = true;
	KidSent = false;
	HeroTriggered = false;

	for (int i = 0; i < 24; ++i)
	{
		gameObjects[i] = nullptr;
	}
}

Game::~Game() {
	for (int i = 0; i < 24; ++i) {
		delete gameObjects[i];
		gameObjects[i] = nullptr;
	}
}

void Game::GtypeLine(const std::string& text, int delay)
{
	for (char c : text) {
		// flush means stop
		std::cout << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
	std::cout << std::endl;
}

void Game::initGame() {

	gameObjects[0] = new Player("MC", 0, 8, 'P');
	gameObjects[1] = new NPC("Inn Keeper", 0, 39, '!', InnKeeperSpeech);
	for (int i = 2;i < 7;i++) {
		gameObjects[i] = new NPC("Villager", 0, 0, 'V', TSvillagersBeforeSpeech);
	}
	gameObjects[7] = new Enemy("Brave Knight", 2, 40, 'K', TSBraveKnightSpeech);
	gameObjects[8] = new Enemy("Bear", 2, 17, 'B', BearSpeech);
	gameObjects[9] = new NPC("Kid", 2, 15, 'k', KidSpeech);
	gameObjects[10] = new NPC("Villager", 4, 40, 'V', HvillagersSpeech);
	gameObjects[11] = new Merchant("Travelling Merchant", 0, 28, '!', MerchantSpeech);
	gameObjects[12] = new NPC("Old Man", 0, 10, 'M', OldManSpeech);
	gameObjects[13] = new Enemy("Hero", 2, 5, 'H');
	for (int i = 14; i < 24; i++) {
		gameObjects[i] = new NPC("Interaction", 1, 1, '!');
	}

	gameObjects[2]->setPosition(23, 4);
	gameObjects[3]->setPosition(8, 1);
	gameObjects[4]->setPosition(13, 4);
	gameObjects[5]->setPosition(20, 0);
	gameObjects[6]->setPosition(30, 2);
	gameObjects[14]->setPosition(17, 0);
	gameObjects[15]->setPosition(9, 0);
	gameObjects[16]->setPosition(35, 0);
	gameObjects[17]->setPosition(23, 0);
	gameObjects[18]->setPosition(37, 0);
	gameObjects[19]->setPosition(10, 0);
	gameObjects[20]->setPosition(19, 4);
	gameObjects[21]->setPosition(25, 0);
	gameObjects[22]->setPosition(25, 4);
	gameObjects[23]->setPosition(39, 0);

	Merchant* john = static_cast<Merchant*>(gameObjects[11]);
	Player* player = static_cast<Player*>(gameObjects[0]);

	Inventory* playerInv = player->getInv();

	//ITEM CREATION AREA
	Item* FireSword = Item::create("Fire Sword", Item::FIRE_SWORD, 35, 1);
	Item* SteelSword = Item::create("Steel Sword", Item::STEEL_SWORD, 25, 1);

	Item* HPpotion = Item::create("HP_Potion", Item::HP_POT, 20, 5);
	Item* ManaPotion = Item::create("Mana Potion", Item::MANA_POT, 20, 5);

	playerInv->setGold(500); // EDIT LATER THIS IS TESTING MONEY
	FireSword->addDesc("A blade forged from the depths of the underground\n with molten iron at its peak. +10 DMG.");


	john->addStock(FireSword);
	john->addStock(SteelSword);
	john->addStock(HPpotion);
	john->addStock(ManaPotion);


 }

void Game::drawWorld() {

	char grid[5][49];
	for (int r = 0; r < 5; ++r)
		for (int c = 0; c < 49; ++c)
			grid[r][c] = ' ';

	for (int i = 23; i > -1; --i) {
		if (gameObjects[i] != nullptr) {
			if (gameObjects[i]->getActive()) {
				int r = gameObjects[i]->getY();
				int c = gameObjects[i]->getX();
				if (r >= 0 && r < 5 && c >= 0 && c < 49) {
					grid[r][c] = gameObjects[i]->getSymbol();
				}
			}
		}
	}

	for (int i = 0; i < 98; i++) {
		cout << '-';
		if (i == 97) cout << "\n"; // New line after the border
	}

	for (int r = 0; r < 5; ++r) {
		for (int c = 0; c < 49; ++c) cout << " " << grid[r][c];
		cout << " \n";
	}

	for (int i = 0; i < 98; i++) {
		cout << '-';
		if (i == 97) cout << "\n"; // New line after the border
	}
}

void Game::doTurn() {

	char Isbuy;
	Map mapObj;

	// If player is gone, end game
	mapObj.clearScreen(); //uses ASCII codes to move player cursor to top-left;


	Player* player = static_cast<Player*>(gameObjects[0]);
	NPC* innkeeper = static_cast<NPC*>(gameObjects[1]);
	NPC* villager1 = static_cast<NPC*>(gameObjects[2]);
	NPC* villager2 = static_cast<NPC*>(gameObjects[3]);
	NPC* villager3 = static_cast<NPC*>(gameObjects[4]);
	NPC* villager4 = static_cast<NPC*>(gameObjects[5]);
	NPC* villager5 = static_cast<NPC*>(gameObjects[6]);
	Enemy* braveknight = static_cast<Enemy*>(gameObjects[7]);
	Enemy* bear = static_cast<Enemy*>(gameObjects[8]);
	NPC* kid = static_cast<NPC*>(gameObjects[9]);
	NPC* harbourvillager = static_cast<NPC*>(gameObjects[10]);
	Merchant* merchant = static_cast<Merchant*>(gameObjects[11]);
	NPC* oldman = static_cast<NPC*>(gameObjects[12]);
	Enemy* hero = static_cast<Enemy*>(gameObjects[13]);


	Inventory* playerInv = player->getInv();


	// if player go right of the Inn, exit to TS
	if (InInn == true && gameObjects[0]->getX() > 47)
	{
		InInn = false;
		InTown = true;
		gameObjects[0]->setPosition(9, 0);
	}
	// if player go left of the TS, go to Forest
	else if (InTown == true && gameObjects[0]->getX() < 1 && BKAlive == false)
	{
		InTown = false;
		InForest = true;
		gameObjects[0]->setPosition(47, gameObjects[0]->getY()); // Set player position in forest
	}
	// if player go right of the Forest, go back to TS
	else if (InForest == true && gameObjects[0]->getX() > 47)
	{
		InForest = false;
		InTown = true;
		gameObjects[0]->setPosition(1, gameObjects[0]->getY()); // Set player position in town
	}
	// if player go left of the Forest, go to Harbour (but initially blocked)
	else if (InForest == true && gameObjects[0]->getX() < 1 && BearAlive == false)
	{
		InForest = false;
		InHarbour = true;
		gameObjects[0]->setPosition(47, gameObjects[0]->getY()); // Set player position in town
	}
	// if player go right of the Harbour, go back to Forest
	else if (InHarbour == true && gameObjects[0]->getX() > 47)
	{
		InHarbour = false;
		InForest = true;
		gameObjects[0]->setPosition(1, gameObjects[0]->getY()); // Set player position in town
	}
	//if player go left of Inside cave, go back to outside of the cave
	else if (InInsideCave == true && gameObjects[0]->getX() < 1)
	{
		InInsideCave = false;
		InOusideCave = true;
		gameObjects[0]->setPosition(25, 0);
	}


	if (InInn == true)
	{
		mapObj.Inn();
		for (int i = 0;i < 24;i++) {
			if (i == 0 || i == 1 || i == 14) {
				gameObjects[i]->setActive(true);
			}
			else {
				gameObjects[i]->setActive(false);
			}
		}
	}
	else if (InTown == true)
	{
		mapObj.townMap();
		if (BKAlive) {
			for (int i = 0;i < 24;i++) {
				if (i == 0 || i == 7 || i == 15 || i == 16) {
					gameObjects[i]->setActive(true);
				}
				else {
					gameObjects[i]->setActive(false);
				}
			}
			for (int i = 2;i < 7;i++) {
				gameObjects[i]->setActive(true);
			}
		}
		else {
			for (int i = 0;i < 24;i++) {
				if (i == 0 || i == 15 || i == 16) {
					gameObjects[i]->setActive(true);
				}
				else {
					gameObjects[i]->setActive(false);
				}
			}
			for (int i = 2;i < 7;i++) {
				gameObjects[i]->setActive(true);
			}

			villager1->dialogue = TSvillagersAfterSpeech;
			villager2->dialogue = TSvillagersAfterSpeech;
			villager3->dialogue = TSvillagersAfterSpeech;
			villager4->dialogue = TSvillagersAfterSpeech;
			villager5->dialogue = TSvillagersAfterSpeech;
			gameObjects[2]->setPosition(45, 0);
			gameObjects[3]->setPosition(45, 1);
			gameObjects[4]->setPosition(45, 2);
			gameObjects[5]->setPosition(45, 3);
			gameObjects[6]->setPosition(45, 4);
		}
	}
	else if (InForest == true)
	{
		mapObj.ForestMap();
		if (BearAlive) {
			for (int i = 0;i < 24;i++) {
				if (i == 0 || i == 8 || i == 9 || i == 17) {
					gameObjects[i]->setActive(true);
				}
				else {
					gameObjects[i]->setActive(false);
				}
			}
		}
		else {
			for (int i = 0;i < 24;i++) {
				if (i == 0 || i == 9 || i == 17) {
					gameObjects[i]->setActive(true);
				}
				else {
					gameObjects[i]->setActive(false);
				}
			}
		}
	}
	  
	else if (InHarbour == true)
	{
		mapObj.HarbourMap();
		for (int i = 0;i < 24;i++) {
			if (i == 0 || i == 10 || i == 11 || i == 18 || i == 19 || i == 20) {
				gameObjects[i]->setActive(true);
			}
			else {
				gameObjects[i]->setActive(false);
			}
		}
	}
	else if (InOusideCave == true)
	{
		mapObj.EntranceCaveMap();
		for (int i = 0;i < 24;i++) {
			if (i == 0 || i == 12 || i == 21 || i == 22 || i == 23) {
				gameObjects[i]->setActive(true);
			}
			else {
				gameObjects[i]->setActive(false);
			}
		}
	}
	else if (InInsideCave == true)
	{
		mapObj.InnerCaveMap();
		for (int i = 0;i < 24;i++) {
			if (i == 0) {
				gameObjects[i]->setActive(true);
			}
			else if (i != 13) {
				gameObjects[i]->setActive(false);
			}
		}
		if (gameObjects[0]->getX() > 27) {
			HeroTriggered = true;
		}
		if (HeroTriggered) {
			gameObjects[13]->setActive(true);

			if (gameObjects[13]->getX() < 26) {
				gameObjects[13]->pos.x++;
			}
		}
	}


	drawWorld();

	// 30: Black
	// 31: Red
	// 32: Green
	// 33: Orange
	// 34: Blue
	// 35: Purple
	// 36: Cyan
	// 37: White


	// check for interacting with InnKeeper
	if (gameObjects[0] != nullptr && InInn == true) {
		if (gameObjects[0]->getActive()) {
			if (NarraInn) {
				GtypeLine("(WASD to move, SPACE to interact, I to open inventory)", 1);
				GtypeLine("(If player presses WASD while text is writing, the player will move immediately after it finishes)", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("How did I get here? Wasn't I knocked unconscious by the hero?", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("I should talk to the Inn Keeper for more details.", 1);
				NarraInn = false;
			}
			if (gameObjects[0]->getX() == 39 && gameObjects[0]->getY() == 0) {
				std::cout << "Press SPACE to talk to inn keeper" << std::endl;
				if (player->interactionGet()) {
					innkeeper->NPCtalk();
				}
			}
			else if (gameObjects[0]->getX() == 17 && gameObjects[0]->getY() == 0)
			{
				std::cout << "Press SPACE to listen on their conversation" << std::endl;
				if (player->interactionGet())
				{
					std::cout << "\033[0;33m" << "Guy on left: " << "\033[0m";
					GtypeLine("Have you heard? Apparently the hero subdued the notorious killer!", 1);
					std::cout << "\033[0;36m" << "Guy on right: " << "\033[0m";
					GtypeLine("Yeah! Now I can finally sleep in peace knowing I won't be targeted!", 1);
				}
			}
		}
	}
	// check for going back to Inn
	else if (gameObjects[0] != nullptr && InTown == true) {
		if (gameObjects[0]->getActive()) {
			if (NarraTown) {
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("What should I do now? I need to get more leads on who helped me.", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("I should ask around town for more information.", 1);
				NarraTown = false;
			}
			if (gameObjects[0]->getX() == 9 && gameObjects[0]->getY() == 0) {
				std::cout << "Press SPACE to enter the Inn" << std::endl;
				if (player->movingGet()) {
					InTown = false;
					InInn = true;
					gameObjects[0]->setPosition(47, 2);
					return;
				}
			}
			else if (gameObjects[0]->getX() == 35 && gameObjects[0]->getY() == 0) {
				std::cout << "Press SPACE to interact" << std::endl;
				if (player->interactionGet()) {
					std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
					GtypeLine("This house is really nice. Whoever lives here must be really rich and strong.", 1);
				}
			}
			else if (gameObjects[0]->getX() == gameObjects[7]->getX() && (gameObjects[0]->getY() == gameObjects[7]->getY() + 1 || gameObjects[0]->getY() == gameObjects[7]->getY() - 1)) {
				if (BKAlive) {
					braveknight->NPCtalk();
					std::cout << "Go into combat scene" << std::endl;

					// Launch the combat mini-game
					battleArenaScene(player);

					BKAlive = false;
					return;
				}
			}
			else if (gameObjects[0]->getY() == gameObjects[7]->getY() && (gameObjects[0]->getX() == gameObjects[7]->getX() + 1 || gameObjects[0]->getX() == gameObjects[7]->getX() - 1)) {
				if (BKAlive) {
					braveknight->NPCtalk();
					std::cout << "Go into combat scene" << std::endl;

					// Launch the combat mini-game
					battleArenaScene(player);

					BKAlive = false;
					return;
				}
			}
			else {
				for (int i = 2;i < 7;i++) {
					if (gameObjects[0]->getY() == gameObjects[i]->getY() && (gameObjects[0]->getX() == gameObjects[i]->getX() + 1 || gameObjects[0]->getX() == gameObjects[i]->getX() - 1)) {
						std::cout << "Press SPACE to interact with villager" << std::endl;
						if (player->interactionGet()) {
							if (i == 2) {
								villager1->NPCtalk();
							}
							else if (i == 3) {
								villager2->NPCtalk();
							}
							else if (i == 4) {
								villager3->NPCtalk();
							}
							else if (i == 5) {
								villager4->NPCtalk();
							}
							else if (i == 6) {
								villager5->NPCtalk();
							}
						}
					}
					else if (gameObjects[0]->getX() == gameObjects[i]->getX() && (gameObjects[0]->getY() == gameObjects[i]->getY() + 1 || gameObjects[0]->getY() == gameObjects[i]->getY() - 1)) {
						std::cout << "Press SPACE to interact with villager" << std::endl;
						if (player->interactionGet()) {
							if (i == 2) {
								villager1->NPCtalk();
							}
							else if (i == 3) {
								villager2->NPCtalk();
							}
							else if (i == 4) {
								villager3->NPCtalk();
							}
							else if (i == 5) {
								villager4->NPCtalk();
							}
							else if (i == 6) {
								villager5->NPCtalk();
							}
						}
					}
				}
			}
		}
	}
	// check for interacting with kid
	else if (gameObjects[0] != nullptr && InForest == true) {
		if (gameObjects[0]->getActive()) {
			if (NarraForest) {
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Phew, that was close", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Wait, what's happening over there?", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Is someone being attacked?", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("I got to go help them!", 1);
				NarraForest = false;
			}
			if (gameObjects[0]->getX() == 23 && gameObjects[0]->getY() == 0)
			{
				std::cout << "Press SPACE to interact" << std::endl;
				if (player->interactionGet())
				{
					std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
					GtypeLine("This is an ordinary rock. However, there's something ominous about it that keeps your guard up.", 1);
				}
			}
			if (gameObjects[0]->getY() == gameObjects[8]->getY() && (gameObjects[0]->getX() == gameObjects[8]->getX() + 1 || gameObjects[0]->getX() == gameObjects[8]->getX() - 1)) {
				if (BearAlive) {
					bear->NPCtalk();
					std::cout << "Go into Combat scene" << std::endl;
					//Added Bear Attack
				   battleArenaBearForest(player);

					BearAlive = false;
					return;
				}
			}
			else if (gameObjects[0]->getX() == gameObjects[8]->getX() && (gameObjects[0]->getY() == gameObjects[8]->getY() + 1 || gameObjects[0]->getY() == gameObjects[8]->getY() - 1)) {
				if (BearAlive) {
					bear->NPCtalk();
					std::cout << "Go into Combat scene" << std::endl;
					//Added Bear Attack
					battleArenaBearForest(player);

					BearAlive = false;
					return;
				}
			}
			if (gameObjects[0]->getY() == gameObjects[9]->getY() && (gameObjects[0]->getX() == gameObjects[9]->getX() + 1 || gameObjects[0]->getX() == gameObjects[9]->getX() - 1) && BearAlive == false) {
				std::cout << "Press SPACE to interact with the kid" << std::endl;
				if (player->interactionGet()) {
					kid->NPCtalk();
				}
			}
			else if (gameObjects[0]->getX() == gameObjects[9]->getX() && (gameObjects[0]->getY() == gameObjects[9]->getY() + 1 || gameObjects[0]->getY() == gameObjects[9]->getY() - 1) && BearAlive == false) {
				std::cout << "Press SPACE to interact with the kid" << std::endl;
				if (player->interactionGet()) {
					kid->NPCtalk();
				}
			}
		}
	}
	// check for interacting with Travelling Merchant and the ship
	else if (gameObjects[0] != nullptr && InHarbour == true) {
		if (gameObjects[0]->getActive()) {
			if (NarraHarbour) {
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Wow, I didn't know this place existed, is this a harbour?", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Maybe the villagers here would have an idea on where the hero might be.", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Let me explore the area first.", 1);
				NarraHarbour = false;
			}

			if (gameObjects[0]->getX() == 37 && gameObjects[0]->getY() == 0)
			{
				std::cout << "Press SPACE to interact." << std::endl;
				if (player->interactionGet())
				{
					std::cout << "\033[1;35m" << "Captain" << ": " << "\033[0m";
					GtypeLine("I heard the other ship was going to that island over there.", 1);
					std::cout << "\033[1;35m" << "Captain" << ": " << "\033[0m";
					GtypeLine("Dang it, I wanted to set sail too! I guess next time...", 1);
				}

			}

			if (gameObjects[0]->getX() == 28 && gameObjects[0]->getY() == 0) {
				std::cout << "Press SPACE to talk to the travelling merchant" << std::endl;
				if (player->movingGet()) {
					merchant->NPCtalk();
					std::cout << "Do you want to buy anything from him? (Y/N): \n";
					Isbuy = _getch();
					if (Isbuy == 'y' || Isbuy == 'Y') {
						std::cout << "\033[1;32m" << merchant->name << ":" << "\033[0m";
						std::cout << '\n';
						merchant->showStock();
						std::cout << "Which item do you wish to purchase? Enter the ID\n";
						int itemID = _getch() - 48;
						std::cout << "How much of this item would you want?\n";
						int quantity = _getch() - 48;
						merchant->sellStock(itemID, *playerInv, quantity);
					}
					else
					{
						std::cout << "\033[1;32m" << merchant->name << ": " << "\033[0m";
						merchant->typeLine("Alright man, stay safe out there.", 1);
					}
				}
			}
			else if (gameObjects[0]->getX() == 10 && gameObjects[0]->getY() == 0) {
				std::cout << "Press SPACE to sneak in the ship" << std::endl;
				if (player->movingGet()) {
					InHarbour = false;
					InOusideCave = true;
					gameObjects[0]->setPosition(1, 2);
					system("cls");
					mapObj.ShipCutscene(); 
					return;
				}
			}
			else if (gameObjects[0]->getX() == gameObjects[10]->getX() && (gameObjects[0]->getY() == gameObjects[10]->getY() + 1 || gameObjects[0]->getY() == gameObjects[10]->getY() - 1)) {
				std::cout << "Press SPACE to interact with the villager" << std::endl;
				if (player->interactionGet()) {
					harbourvillager->NPCtalk();
				}
			}
			else if (gameObjects[0]->getY() == gameObjects[10]->getY() && (gameObjects[0]->getX() == gameObjects[10]->getX() + 1 || gameObjects[0]->getX() == gameObjects[10]->getX() - 1)) {
				std::cout << "Press SPACE to interact with the villager" << std::endl;
				if (player->interactionGet()) {
					harbourvillager->NPCtalk();
				}
			}
		}
	}
	// check for going into cave
	else if (gameObjects[0] != nullptr && InOusideCave == true) {
		if (gameObjects[0]->getActive()) {
			if (NarraOutsideCave) {
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("I'm lucky that I wasn't discovered sneaking onto that ship", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Or else I was as good as dead", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("This island is pretty big, let's start finding the cave.", 1);
				NarraOutsideCave = false;
			}
			if (gameObjects[0]->getX() == 25 && gameObjects[0]->getY() == 4) {
				std::cout << "Press SPACE to intertact." << std::endl;
				if (player->interactionGet())
				{
					std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
					GtypeLine("The view looks nice on this island, but it gives off an unsettling energy.", 1);
				}
			}
			else if (gameObjects[0]->getX() == 25 && gameObjects[0]->getY() == 0) {
				std::cout << "Press SPACE to enter the cave" << std::endl << std::endl;
				if (player->movingGet()) {
					InOusideCave = false;
					InInsideCave = true;
					gameObjects[0]->setPosition(2, 2);
					return;
				}
			}
			else if (gameObjects[0]->getX() == gameObjects[12]->getX() && (gameObjects[0]->getY() == gameObjects[12]->getY() + 1 || gameObjects[0]->getY() == gameObjects[12]->getY() - 1)) {
				std::cout << "Press SPACE to talk to the Old Man" << std::endl;
				if (player->interactionGet()) {
					oldman->NPCtalk();
				}
			}
			else if (gameObjects[0]->getY() == gameObjects[12]->getY() && (gameObjects[0]->getX() == gameObjects[12]->getX() + 1 || gameObjects[0]->getX() == gameObjects[12]->getX() - 1)) {
				std::cout << "Press SPACE to talk to the Old Man" << std::endl;
				if (player->interactionGet()) {
					oldman->NPCtalk();
				}
			}
		}
	}
	else if (gameObjects[0] != nullptr && InInsideCave == true) {
		if (gameObjects[0]->getActive()) {
			if (NarraInsideCave) {
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Woah, this cave looks really big, I wonder where the hero might be.", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Wait a second ... is that what I think it is?", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("What is the demon altar doing here?", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("I remember using it back then, but I don't remember using it here.", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("I need to check it out to make sure it actually is the altar.", 1);
				NarraInsideCave = false;
			}
		}
	}


	int oldX = player->getX();
	int oldY = player->getY();


	if (player != nullptr) {
		player->move(gameObjects, 23);
	}


	// Move enemies
	for (int i = 1; i < 23; ++i) {
		if (gameObjects[i] != nullptr && player != nullptr) {
			Enemy1* enemy1 = static_cast<Enemy1*>(gameObjects[i]);
			// capture player's position before any possible deletion later
			int playerX = player->getX();
			int playerY = player->getY();
			enemy1->move(playerPos, gameObjects, 13);
		}
	}

	// Check collisions
	for (int i = 1; i < 14; ++i) {
		if (gameObjects[i] != nullptr && player != nullptr) {
			if (gameObjects[i]->getActive()) {
				if (i != 1 && i != 11) {
					if (gameObjects[i]->getX() == (player->getX()) && gameObjects[i]->getY() == (player->getY())) {
						player->setPosition(oldX, oldY);
						break;
					}
				}
			}
		}
	}
	clearDialogue();
	std::cout.flush();
}

void Game::clearDialogue() { // clears after 22st line which is where dialogue is at 
	for (int i = 0; i < 100; i++) {//clear for 100 lines
		std::cout << "\033[" << (22 + i) << ";1H";   // move to each line start
		std::cout << std::string(100, ' '); // clear each line and replace with space
	}
	std::cout.flush();
}
