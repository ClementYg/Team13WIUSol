#include "Game.h"
#include "Player.h"
#include "Enemy1.h"
#include "NPC.h"
#include "Merchant.h"
#include "Map.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <cstdlib>
using namespace std;



Game::Game() :InTown(true), InForest(false)
{
	for (int i = 0; i < 3; ++i)
	{
		gameObjects[i] = nullptr;
	}
}

Game::~Game() {
	for (int i = 0; i < 3; ++i) {
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
		"A shadowed figure brought you here.",
		"(WASD to move, K to interact, I to open inventory)"
	};

	std::vector<std::string> TSvillagersBeforeSpeech =
	{
		"I think there is a weird man in front there",
		"He looks like the BRAVE KNIGHT!"
	};

	std::vector<std::string> TSBraveKnightSpeech =
	{
		"You look familiar.",
		"OHH! You are the villain!",
		"That have been killing the innocents.",
		"I will kill you for the justice!"
	};

	std::vector<std::string> TSvillagersAfterSpeech =
	{
		"He is the wanted villain!",
		"We need to call police NOW!"
		// MC run into forest to avoid getting arrest
	};

	std::vector<std::string>  KidSpeech =
	{
		"OH MY GOD! That is so scary",
		"Thank you my hero, can you bring me back to my village.",
		"In case there is more monsters."
	};

	std::vector<std::string> HvillagersSpeech =
	{
		"The hero? I heard that he was last seen ouside the cave.",
		"The cave is at the other island.",
		"It's impossible to get there without ship."
	};

	std::vector<std::string> johnSpeech =
	{
		"Hi! I am John, A travelling merchant.",
		"I sell some interesting things.",
		"Do you want to take a look?"
	};

	gameObjects[0] = new Player("MC", 0, 10, 'P');
	gameObjects[1] = new Merchant("John", 2, 44, 'M', johnSpeech);
	gameObjects[2] = new Enemy1("Bear", 2, 30, 'B');

	Merchant* john = static_cast<Merchant*>(gameObjects[1]);

	Inventory playerInv;

	Item* test1 = Item::create("Sword", Item::FIRE_SWORD, 10, 3);
	Item* test2 = Item::create("Chestplate", Item::WOOD_CHEST, 10, 1);

	playerInv.setGold(500);

	john->addStock(test1);
	john->addStock(test2);

	john->sellStock(0, playerInv, 1);

		playerInv.requestInventory();



}

void Game::drawWorld() {

	char grid[5][49];
	for (int r = 0; r < 5; ++r)
		for (int c = 0; c < 49; ++c)
			grid[r][c] = ' ';

	for (int i = 0; i < 3; ++i) {
		if (gameObjects[i] != nullptr) {
			if (gameObjects[i]->getActive())
			{
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
	system("cls");


	Player* player = static_cast<Player*>(gameObjects[0]);
	Merchant* john = static_cast<Merchant*>(gameObjects[1]);


	if (InTown == true && gameObjects[0]->getX() < 1) {
		InTown = false;
		InForest = true;
		gameObjects[0]->setPosition(47, gameObjects[0]->getY()); // Set player position in forest
	}
	else if (InForest == true && gameObjects[0]->getX() > 47) {
		InForest = false;
		InTown = true;
		gameObjects[0]->setPosition(1, gameObjects[0]->getY()); // Set player position in town
	}
	if (InTown == true)
	{
		mapObj.townMap();
		gameObjects[0]->setActive(true);
		gameObjects[1]->setActive(true);
		gameObjects[2]->setActive(false);
	}
	else {
		mapObj.ForestMap();
		gameObjects[0]->setActive(true);
		gameObjects[1]->setActive(false);
		gameObjects[2]->setActive(true);
	}



	drawWorld();


	int oldX = player->getX();
	int oldY = player->getY();


	if (gameObjects[0] != nullptr && gameObjects[1] != nullptr) {
		if (gameObjects[1]->getActive()) {
			if (gameObjects[0]->getY() == gameObjects[1]->getY() && (gameObjects[0]->getX() == gameObjects[1]->getX() + 1 || gameObjects[0]->getX() == gameObjects[1]->getX() - 1)) {
				if (player->interactionGet())
				{
					//std::cout << "Interaction with bro";
					john->NPCtalk();
					std::cout << "Do you want to buy anything from him? (Y/N): ";
					std::cin >> Isbuy;
					if (Isbuy == 'Y') {
						std::cout << "\033[1;32m" << john->name << ":" << "\033[0m";
						john->typeLine("	1. Sword\n	2. Sheild\n	3. Potion", 1);
					}
					else
					{
						std::cout << "\033[1;32m" << john->name << ": " << "\033[0m";
						john->typeLine("Alright man, stay safe out there.", 1);
					}
				}
			}
			else if (gameObjects[0]->getX() == gameObjects[1]->getX() && (gameObjects[0]->getY() == gameObjects[1]->getY() + 1 || gameObjects[0]->getY() == gameObjects[1]->getY() - 1)) {
				//dingle = "Interacting with bro";
				if (player->interactionGet())
				{
					//std::cout << "Interaction with bro";
					john->NPCtalk();
					std::cout << "Do you want to buy anything from him? (Y/N): ";
					std::cin >> Isbuy;
					if (Isbuy == 'Y') {
						std::cout << "\033[1;32m" << john->name << ":" << "\033[0m";
						john->typeLine("	1. Sword\n	2. Sheild\n	3. Potion", 1);
					}
					else
					{
						std::cout << "\033[1;32m" << john->name << ": " << "\033[0m";
						john->typeLine("Alright man, stay safe out there.", 1);
					}
				}
			}
		}
	}




	if (player != nullptr) {
		player->move(gameObjects, 3);
	}
	//if (player->getX() < 1 && InTown == true) {
	//	InTown = false;
	//	InForest = true;
	//}
	//else if (player->getX() < 1 && InForest == true) {
	//	InForest = false;
	//	InTown = true;


	// Move enemies
	for (int i = 1; i < 3; ++i) {
		if (gameObjects[i] != nullptr && player != nullptr) {
			Enemy1* enemy1 = static_cast<Enemy1*>(gameObjects[i]);
			// capture player's position before any possible deletion later
			int playerX = player->getX();
			int playerY = player->getY();
			enemy1->move(playerPos, gameObjects, 3);
		}
	}

	// Check collisions
	for (int i = 1; i < 3; ++i) {
		if (gameObjects[i] != nullptr && player != nullptr) {
			if (gameObjects[i]->getActive()) {
				if (gameObjects[i]->getX() == (player->getX()) && gameObjects[i]->getY() == (player->getY())) {
					player->setPosition(oldX, oldY);
					break;
				}
			}
		}
	}



	// Clear console (Windows)
   //if (gameObjects[0]->getY() == (gameObjects[1]->getY() - 1) || gameObjects[0]->getY() == (gameObjects[1]->getY() + 1) || gameObjects[0]->getX() == (gameObjects[1]->getX() - 1) || gameObjects[0]->getX() == (gameObjects[1]->getX() + 1))
   //{
   //}
}
