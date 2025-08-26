#include "Game.h"
#include "Player.h"
#include "Enemy1.h"
#include "NPC.h"
#include "Merchant.h"
#include "Map.h"
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

	for (int i = 0; i < 4; ++i)
	{
		gameObjects[i] = nullptr;
	}
}

Game::~Game() {
	for (int i = 0; i < 4; ++i) {
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

	std::vector<std::string> InnKeeperSpeech =
	{
		"If you are wondering why are you here,",
		"A shadowed figure brought you here yesterday.",
		"(WASD to move, SPACE to interact, I to open inventory)"
	};

	std::vector<std::string> TSvillagersBeforeSpeech =
	{
		"I can't help you much, but that man over there might be able to."
	};

	std::vector<std::string> TSBraveKnightSpeech =
	{
		"Civilian, how can I hel-"
		"Wait... You look familiar",
		"OHH! You are the villain!",
		"That have been killing the innocents.",
		"I will kill you in the name of justice!"
	};

	std::vector<std::string> TSvillagersAfterSpeech =
	{
		"He is the wanted villain!",
		"We need to call the royal guards NOW!"
		// MC run into forest to avoid getting arrest
	};

	std::vector<std::string> KidSpeech =
	{
		"OH MY GOD! That was so scary",
		"Thank you my hero, can you bring me back to my village?",
		"In case there are more monsters."
	};

	std::vector<std::string> HvillagersSpeech =
	{
		"The hero? I heard that he was last seen ouside the cave.",
		"The cave is at that island oveer there.",
		"It's impossible to get there without a ship."
	};

	//need interacting part for sneaking into the ship.

	std::vector<std::string> johnSpeech =
	{
		"Hi! I am John, A travelling merchant.",
		"I sell some interesting things.",
		"Do you want to take a look?"
	};

	std::vector<std::string> GHeroSpeech =
	{
		"MC! STOP THERE!",
		"You can't succumb to the devil's power",
		"Once you take it, there is no turning back.",
		"If you still choose to use that horrendous stink of a power",
		"I have no choice but to end your life on my terms!"
	};

	std::vector<std::string> BHeroSpeech =
	{
		"MC! I have already taken the devil's power.",
		"You were right, having this evil power is the meaning of life",
		"You are going to follow me down this path too, right?",
		"Anyways, you can't stop me even if you tried.",
		"Make your choice now, or die by my hands!"
	};

	gameObjects[0] = new Player("MC", 0, 8, 'P');
	gameObjects[1] = new NPC("Inn Keeper", 0, 39, 'I', InnKeeperSpeech);
	for (int i = 2;i < 7;i++) {
		gameObjects[i] = new NPC("Villager", 0, 0, 'V', TSvillagersBeforeSpeech);
	}
	// 7 should be brave knight instead of Merchant
	gameObjects[7] = new Merchant("Travelling Merchant", 2, 40, 'M', johnSpeech);
	gameObjects[8] = new Enemy1("Bear", 2, 30, 'B');
	gameObjects[9] = new NPC("Kid", 2, 15, 'K', KidSpeech);

	gameObjects[2]->setPosition(23, 4);
	gameObjects[3]->setPosition(8, 1);
	gameObjects[4]->setPosition(13, 4);
	gameObjects[5]->setPosition(20, 0);
	gameObjects[6]->setPosition(30, 2);

	Merchant* john = static_cast<Merchant*>(gameObjects[7]);
	Player* player = static_cast<Player*>(gameObjects[0]);

	Inventory* playerInv = player->getInv();

	//ITEM CREATION AREA
	Item* FireSword = Item::create("Fire Sword", Item::FIRE_SWORD, 30, 1);
	Item* WoodChest = Item::create("Wood_Chestplate", Item::WOOD_CHEST, 35, 1);
	Item* WoodHelmet = Item::create("Wood_Helmet", Item::WOOD_HELM, 25, 1);
	Item* WoodLeggings = Item::create("Wood_Leggings", Item::WOOD_CHEST, 25, 1);

	Item* potion = Item::create("HP_Potion", Item::HP_POT, 10, 5);

	playerInv->setGold(500);
	FireSword->addDesc("A blade forged from the depths of the underground\n with molten iron at its peak. +10 DMG.");


	john->addStock(FireSword);
	john->addStock(WoodChest);
	john->addStock(WoodHelmet);
	john->addStock(WoodLeggings);
	john->addStock(potion);


}

void Game::drawWorld() {

	char grid[5][49];
	for (int r = 0; r < 5; ++r)
		for (int c = 0; c < 49; ++c)
			grid[r][c] = ' ';

	for (int i = 0; i < 10; ++i) {
		if (gameObjects[i] != nullptr) {
			if (gameObjects[i]->getActive()) {
				if (i != 1 && i != 7) {
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
	mapObj.clearScreen(); //uses ASCII codes to move player cursor to top-left;


	Player* player = static_cast<Player*>(gameObjects[0]);
	NPC* innkeeper = static_cast<NPC*>(gameObjects[1]);
	NPC* villager1 = static_cast<NPC*>(gameObjects[2]);
	NPC* villager2 = static_cast<NPC*>(gameObjects[3]);
	NPC* villager3 = static_cast<NPC*>(gameObjects[4]);
	NPC* villager4 = static_cast<NPC*>(gameObjects[5]);
	NPC* villager5 = static_cast<NPC*>(gameObjects[6]);
	Merchant* merchant = static_cast<Merchant*>(gameObjects[7]);
	NPC* kid = static_cast<NPC*>(gameObjects[9]);
	

	Inventory* playerInv = player->getInv();

	// gameObjects[0] = player
	// gameObjects[7] = Merchant (john)
	// gameObjects[8] = Enemy1 (bear)
	// 
	// if player go right of the Inn, exit to TS
	if (InInn == true && gameObjects[0]->getX() > 47)
	{
		InInn = false;
		InTown = true;
		gameObjects[0]->setPosition(9, 0); // Set player position in forest
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
	}
	else if (InTown == true)
	{
		mapObj.townMap();
		gameObjects[0]->setActive(true);
		gameObjects[1]->setActive(false);
		for (int i = 2;i < 7;i++) {
			gameObjects[i]->setActive(true);
		}
		gameObjects[7]->setActive(false);
		gameObjects[8]->setActive(false);
		gameObjects[9]->setActive(false);
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
		gameObjects[8]->setActive(true);
		gameObjects[9]->setActive(true);
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
	}


	drawWorld();


	// check for interacting with InnKeeper
	if (gameObjects[0] != nullptr && InInn == true) {
		if (gameObjects[0]->getActive()) {
			if (gameObjects[0]->getX() == 39 && gameObjects[0]->getY() == 0) {
				std::cout << "Press SPACE to talk to inn keeper" << std::endl;
				if (player->interactionGet()) {
					innkeeper->NPCtalk();
				}
			}
		}
	}
	// check for going back to Inn
	else if (gameObjects[0] != nullptr && InTown == true) {
		if (gameObjects[0]->getActive()) {
			if (gameObjects[0]->getX() == 9 && gameObjects[0]->getY() == 0) {
				std::cout << "Press SPACE to enter the Inn" << std::endl;
				if (player->movingGet()) {
					InTown = false;
					InInn = true;
					gameObjects[0]->setPosition(47, 2);
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
			if (gameObjects[0]->getY() == gameObjects[9]->getY() && (gameObjects[0]->getX() == gameObjects[9]->getX() + 1 || gameObjects[0]->getX() == gameObjects[9]->getX() - 1)) {
				std::cout << "Press SPACE to interact with the kid" << std::endl;
				if (player->interactionGet()) {
					kid->NPCtalk();
				}
			}
			else if (gameObjects[0]->getX() == gameObjects[9]->getX() && (gameObjects[0]->getY() == gameObjects[9]->getY() + 1 || gameObjects[0]->getY() == gameObjects[9]->getY() - 1)) {
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
						merchant->sellStock(itemID, *playerInv, quantity);					}
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

		}
	}
	// check for going into cave
	else if (gameObjects[0] != nullptr && InOusideCave == true) {
		if (gameObjects[0]->getActive()) {
			if (gameObjects[0]->getX() == 25 && gameObjects[0]->getY() == 0) {
				std::cout << "Press SPACE to enter the cave" << std::endl;
				if (player->movingGet()) {
					InOusideCave = false;
					InInsideCave = true;
					gameObjects[0]->setPosition(0, 2);
					return;
				}
			}
		}
	}


	int oldX = player->getX();
	int oldY = player->getY();


	//if (gameObjects[0] != nullptr && gameObjects[1] != nullptr) {
	//	if (gameObjects[1]->getActive()) {
	//		if (gameObjects[0]->getY() == gameObjects[1]->getY() && (gameObjects[0]->getX() == gameObjects[1]->getX() + 1 || gameObjects[0]->getX() == gameObjects[1]->getX() - 1)) {
	//			if (player->interactionGet())
	//			{
	//				//std::cout << "Interaction with bro";
	//				merchant->NPCtalk();
	//				std::cout << "Do you want to buy anything from him? (Y/N): ";
	//				std::cin >> Isbuy;
	//				if (Isbuy == 'Y') {
	//					std::cout << "\033[1;32m" << merchant->name << ":" << "\033[0m";
	//					merchant->typeLine("	1. Sword\n	2. Sheild\n	3. Potion", 1);
	//				}
	//				else
	//				{
	//					std::cout << "\033[1;32m" << merchant->name << ": " << "\033[0m";
	//					merchant->typeLine("Alright man, stay safe out there.", 1);
	//				}
	//			}
	//		}
	//		else if (gameObjects[0]->getX() == gameObjects[1]->getX() && (gameObjects[0]->getY() == gameObjects[1]->getY() + 1 || gameObjects[0]->getY() == gameObjects[1]->getY() - 1)) {
	//			//dingle = "Interacting with bro";
	//			if (player->interactionGet())
	//			{
	//				//std::cout << "Interaction with bro";
	//				merchant->NPCtalk();
	//				std::cout << "Do you want to buy anything from him? (Y/N): ";
	//				std::cin >> Isbuy;
	//				if (Isbuy == 'Y') {
	//					std::cout << "\033[1;32m" << merchant->name << ":" << "\033[0m";
	//					merchant->typeLine("	1. Sword\n	2. Sheild\n	3. Potion", 1);
	//				}
	//				else
	//				{
	//					std::cout << "\033[1;32m" << merchant->name << ": " << "\033[0m";
	//					merchant->typeLine("Alright man, stay safe out there.", 1);
	//				}
	//			}
	//		}
	//	}
	//}






	if (player != nullptr) {
		player->move(gameObjects, 10);
	}


	// Move enemies
	for (int i = 1; i < 10; ++i) {
		if (gameObjects[i] != nullptr && player != nullptr) {
			Enemy1* enemy1 = static_cast<Enemy1*>(gameObjects[i]);
			// capture player's position before any possible deletion later
			int playerX = player->getX();
			int playerY = player->getY();
			enemy1->move(playerPos, gameObjects, 3);
		}
	}

	// Check collisions
	for (int i = 1; i < 10; ++i) {
		if (gameObjects[i] != nullptr && player != nullptr) {
			if (gameObjects[i]->getActive()) {
				if (i != 1 && i != 7) {
					if (gameObjects[i]->getX() == (player->getX()) && gameObjects[i]->getY() == (player->getY())) {
						player->setPosition(oldX, oldY);
						break;
					}
				}
			}
		}
	}


	// Clear console (Windows)
   //if (gameObjects[0]->getY() == (gameObjects[1]->getY() - 1) || gameObjects[0]->getY() == (gameObjects[1]->getY() + 1) || gameObjects[0]->getX() == (gameObjects[1]->getX() - 1) || gameObjects[0]->getX() == (gameObjects[1]->getX() + 1))
   //{
   //}

	clearDialogue();
	std::cout.flush();
}

void Game::clearDialogue() { // clears after 22st line which is where dialogue is at 
	for (int i = 0; i < 100; i++) {//clear for 100 lines
		std::cout << "\033[" << (22 + i) << ";1H";   // move to each line start
		std::cout << std::string(98, ' '); // clear each line and replace with space
	}
	std::cout.flush();
}
