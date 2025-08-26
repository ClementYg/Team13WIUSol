#include "Game.h"
#include "Player.h"
#include "Enemy1.h"
#include "NPC.h"
#include "Merchant.h"
#include "Enemy.h"
#include "Map.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdlib>
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
	BKAlive = true;
	
	for (int i = 0; i < 12; ++i)
	{
		gameObjects[i] = nullptr;
	}
}

Game::~Game() {
	for (int i = 0; i < 12; ++i) {
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
	gameObjects[1] = new NPC("Inn Keeper", 0, 39, 'I', InnKeeperSpeech);
	for (int i = 2;i < 7;i++) {
		gameObjects[i] = new NPC("Villager", 0, 0, 'V', TSvillagersBeforeSpeech);
	}
	gameObjects[7] = new Enemy("Brave Knight", 2, 40, 'K', TSBraveKnightSpeech);
	// 7 should be brave knight instead of Merchant
	gameObjects[8] = new Merchant("Travelling Merchant", 2, 40, 'M', johnSpeech);
	gameObjects[9] = new Enemy1("Bear", 2, 30, 'B');
	gameObjects[10] = new NPC("Kid", 2, 15, 'k', KidSpeech);
	gameObjects[11] = new NPC("Villager", 4, 40, 'V', HvillagersSpeech);
	gameObjects[12] = new Enemy("Hero", 2, 5, 'H');

	gameObjects[2]->setPosition(23, 4);
	gameObjects[3]->setPosition(8, 1);
	gameObjects[4]->setPosition(13, 4);
	gameObjects[5]->setPosition(20, 0);
	gameObjects[6]->setPosition(30, 2);

	//Merchant* john = static_cast<Merchant*>(gameObjects[1]);

	//Inventory playerInv;

	//Item* test1 = Item::create("Sword", Item::FIRE_SWORD, 10, 3);
	//Item* test2 = Item::create("Chestplate", Item::WOOD_CHEST, 10, 1);

	//playerInv.setGold(500);

	//john->addStock(test1);
	//john->addStock(test2);

	//john->sellStock(0, playerInv, 1);

	//	playerInv.requestInventory();



}

void Game::drawWorld() {

	char grid[5][49];
	for (int r = 0; r < 5; ++r)
		for (int c = 0; c < 49; ++c)
			grid[r][c] = ' ';

	for (int i = 0; i < 13; ++i) {
		if (gameObjects[i] != nullptr) {
			if (gameObjects[i]->getActive()) {
				if (i != 1 && i != 8) {
					int r = gameObjects[i]->getY();
					int c = gameObjects[i]->getX();
					if (r >= 0 && r < 5 && c >= 0 && c < 49) {
						grid[r][c] = gameObjects[i]->getSymbol();
					}
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
	system("cls");


	Player* player = static_cast<Player*>(gameObjects[0]);
	NPC* innkeeper = static_cast<NPC*>(gameObjects[1]);
	NPC* villager1 = static_cast<NPC*>(gameObjects[2]);
	NPC* villager2 = static_cast<NPC*>(gameObjects[3]);
	NPC* villager3 = static_cast<NPC*>(gameObjects[4]);
	NPC* villager4 = static_cast<NPC*>(gameObjects[5]);
	NPC* villager5 = static_cast<NPC*>(gameObjects[6]);
	Enemy* braveknight = static_cast<Enemy*>(gameObjects[7]);
	Merchant* merchant = static_cast<Merchant*>(gameObjects[8]);
	NPC* kid = static_cast<NPC*>(gameObjects[10]);
	NPC* harbourvillager = static_cast<NPC*>(gameObjects[11]);
	Enemy* hero = static_cast<Enemy*>(gameObjects[12]);
	

	// gameObjects[0] = player
	// gameObjects[7] = Merchant (john)
	// gameObjects[8] = Enemy1 (bear)
	// 
	// if player go right of the Inn, exit to TS
	if (InInn == true && gameObjects[0]->getX() > 47)
	{
		InInn = false;
		InTown = true;
		gameObjects[0]->setPosition(9, 0); 
	}
	// if player go left of the TS, go to Forest
	else if (InTown == true && gameObjects[0]->getX() < 1)
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
	else if (InForest == true && gameObjects[0]->getX() < 1)
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
		gameObjects[0]->setActive(true);
		gameObjects[1]->setActive(false);
		for (int i = 2;i < 7;i++) {
			gameObjects[i]->setActive(false);
		}
		gameObjects[7]->setActive(false);
		gameObjects[8]->setActive(false);
		gameObjects[9]->setActive(false);
		gameObjects[10]->setActive(false);
		gameObjects[11]->setActive(false);
		gameObjects[12]->setActive(false);
	}
	else if (InTown == true)
	{
		mapObj.townMap();
		if (BKAlive) {
			gameObjects[0]->setActive(true);
			gameObjects[1]->setActive(false);
			for (int i = 2;i < 7;i++) {
				gameObjects[i]->setActive(true);
			}
			gameObjects[7]->setActive(true);
			gameObjects[8]->setActive(false);
			gameObjects[9]->setActive(false);
			gameObjects[10]->setActive(false);
			gameObjects[11]->setActive(false);
			gameObjects[12]->setActive(false);
		}
		else {
			gameObjects[0]->setActive(true);
			gameObjects[1]->setActive(false);
			for (int i = 2;i < 7;i++) {
				gameObjects[i]->setActive(true);
			}
			gameObjects[7]->setActive(false);
			gameObjects[8]->setActive(false);
			gameObjects[9]->setActive(false);
			gameObjects[10]->setActive(false);
			gameObjects[11]->setActive(false);
			gameObjects[12]->setActive(false);

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
		gameObjects[0]->setActive(true);
		gameObjects[1]->setActive(false);
		for (int i = 2;i < 7;i++) {
			gameObjects[i]->setActive(false);
		}
		gameObjects[7]->setActive(false);
		gameObjects[8]->setActive(false);
		gameObjects[9]->setActive(true);
		gameObjects[10]->setActive(true);
		gameObjects[11]->setActive(false);
		gameObjects[12]->setActive(false);
	}
	else if (InHarbour == true)
	{
		mapObj.HarbourMap();
		gameObjects[0]->setActive(true);
		gameObjects[1]->setActive(false);
		for (int i = 2;i < 7;i++) {
			gameObjects[i]->setActive(false);
		}
		gameObjects[7]->setActive(false);
		gameObjects[8]->setActive(false);
		gameObjects[9]->setActive(false);
		gameObjects[10]->setActive(false);
		gameObjects[11]->setActive(true);
		gameObjects[12]->setActive(false);
	}
	else if (InOusideCave == true)
	{
		mapObj.EntranceCaveMap();
		gameObjects[0]->setActive(true);
		gameObjects[1]->setActive(false);
		for (int i = 2;i < 7;i++) {
			gameObjects[i]->setActive(false);
		}
		gameObjects[7]->setActive(false);
		gameObjects[8]->setActive(false);
		gameObjects[9]->setActive(false);
		gameObjects[10]->setActive(false);
		gameObjects[11]->setActive(false);
		gameObjects[12]->setActive(false);
	}
	else if (InInsideCave == true)
	{
		mapObj.InnerCaveMap();
		gameObjects[0]->setActive(true);
		gameObjects[1]->setActive(false);
		for (int i = 2;i < 7;i++) {
			gameObjects[i]->setActive(false);
		}
		gameObjects[7]->setActive(false);
		gameObjects[8]->setActive(false);
		gameObjects[9]->setActive(false);
		gameObjects[10]->setActive(false);
		gameObjects[11]->setActive(false);
		gameObjects[12]->setActive(true);
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
			if (gameObjects[0]->getX() == 17 && gameObjects[0]->getY() == 0)
			{
				std::cout << "Press SPACE to listen on their conversation" << std::endl;
				if (player->interactionGet())
				{
					std::cout << "\033[0;33m" << "Guy on left: " << "\033[0m";
					std::cout << "Have you heard? Apparently the hero subdued the notorious killer!" << std::endl;
					std::cout << "\033[0;36m" << "Guy on right: " << "\033[0m";
					std::cout << "Yeah! Now I can finally sleep in peace knowing I won't be targeted!" << std::endl;
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
			else if (gameObjects[0]->getX() == gameObjects[7]->getX() && (gameObjects[0]->getY() == gameObjects[7]->getY() + 1 || gameObjects[0]->getY() == gameObjects[7]->getY() - 1)) {
				if (BKAlive) {
					braveknight->NPCtalk();
					std::cout << "Go into combat scene" << std::endl;
					BKAlive = false;
					return;
				}
				
			}
			else if (gameObjects[0]->getY() == gameObjects[7]->getY() && (gameObjects[0]->getX() == gameObjects[7]->getX() + 1 || gameObjects[0]->getX() == gameObjects[7]->getX() - 1)) {
				if (BKAlive) {
					braveknight->NPCtalk();
					std::cout << "Go into combat scene" << std::endl;
					BKAlive = false;
					return;
				}
				
			}
			else{
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
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "Phew, that was close" << std::endl;
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "Wait, what's happening over there?" << std::endl;
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "Is someone being attacked?" << std::endl;
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "I got to go help them!" << std::endl << std::endl;
			if (gameObjects[0]->getY() == gameObjects[10]->getY() && (gameObjects[0]->getX() == gameObjects[10]->getX() + 1 || gameObjects[0]->getX() == gameObjects[10]->getX() - 1)) {
				std::cout << "Press SPACE to interact with the kid" << std::endl;
				if (player->interactionGet()) {
					kid->NPCtalk();
				}
			}
			else if (gameObjects[0]->getX() == gameObjects[10]->getX() && (gameObjects[0]->getY() == gameObjects[10]->getY() + 1 || gameObjects[0]->getY() == gameObjects[10]->getY() - 1)) {
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
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "Wow, I didn't know this place existed, is this a harbour?" << std::endl;
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "Maybe the villagers here would have an idea on where the hero might be." << std::endl;
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "Let me explore the area first." << std::endl << std::endl;
			if (gameObjects[0]->getX() == 28 && gameObjects[0]->getY() == 0) {
				std::cout << "Press SPACE to talk to the travelling merchant" << std::endl;
				if (player->movingGet()) {
					merchant->NPCtalk();
					std::cout << "Do you want to buy anything from him? (Y/N): ";
					std::cin >> Isbuy;
					if (Isbuy == 'Y') {
						std::cout << "\033[1;32m" << merchant->name << ":" << "\033[0m";
						merchant->typeLine("1. Sword\n	2. Sheild\n	3. Potion", 1);
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
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "I'm lucky that I wasn't discovered sneaking onto that ship" << std::endl;
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "Or else I was as good as dead" << std::endl;
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "This island is pretty big, let’s start finding the cave." << std::endl;
			if (gameObjects[0]->getX() == 25 && gameObjects[0]->getY() == 0) {
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				std::cout << "This must be the cave the villagers were talking about" << std::endl << std::endl;
				std::cout << "Press SPACE to enter the cave" << std::endl << std::endl;
				if (player->movingGet()) {
					InOusideCave = false;
					InInsideCave = true;
					gameObjects[0]->setPosition(2, 2);
					return;
				}
			}
		}
	}

	else if (gameObjects[0] != nullptr && InInsideCave == true) {
		if (gameObjects[0]->getActive()) {
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "Woah, this cave looks really big, I wonder where the hero might be." << std::endl;
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "Wait a second … is that what I think it is?" << std::endl;
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "What is the demon altar doing here?" << std::endl;
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "I remember using it back then, but I don't remember using it here." << std::endl;
			std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
			std::cout << "I need to check it out to make sure it actually is the altar." << std::endl << std::endl;
		}
	}


	int oldX = player->getX();
	int oldY = player->getY();


	if (player != nullptr) {
		player->move(gameObjects, 13);
	}


	// Move enemies
	for (int i = 1; i < 13; ++i) {
		if (gameObjects[i] != nullptr && player != nullptr) {
			Enemy1* enemy1 = static_cast<Enemy1*>(gameObjects[i]);
			// capture player's position before any possible deletion later
			int playerX = player->getX();
			int playerY = player->getY();
			enemy1->move(playerPos, gameObjects, 12);
		}
	}

	// Check collisions
	for (int i = 1; i < 13; ++i) {
		if (gameObjects[i] != nullptr && player != nullptr) {
			if (gameObjects[i]->getActive()) {
				if (i != 1 && i != 8) {
					if (gameObjects[i]->getX() == (player->getX()) && gameObjects[i]->getY() == (player->getY())) {
						player->setPosition(oldX, oldY);
						break;
					}
				}
			}
		}
	}
}
