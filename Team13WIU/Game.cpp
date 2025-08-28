#include "Game.h"
#include "Player.h"
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
#include "FinalBattle.h"
#include "EndCredits.h"

using namespace std;

Game::Game() : RiverPuzzle(nullptr)
{
	InInn = false;
	InTown = false;
	InForest = false;
	InHarbour = false;
	InOusideCave = false;
	InInsideCave = true;
	puzzleActive = false;


	NarraInn = true;
	NarraTown = true;
	NarraForest = true;
	NarraHarbour = true;
	NarraOutsideCave = true;
	NarraInsideCave = true;
	NarraInsideCave2 = true;

	
	BKAlive = true;
	BearAlive = true;
	HeroAlive = true;

	interactedrock = true;
	interactedground = true;
	interactedbird = true;
	interactedbarrel = true;
	interactedaltar = true;

	BearAlive = true;
	KidTriggered = false;
	HeroTriggered = false;
	HeroTalk = true;


	for (int i = 0; i < 27; ++i)
	{
		gameObjects[i] = nullptr;
	}
}

Game::~Game() {
	for (int i = 0; i < 27; ++i) {
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
	gameObjects[9] = new NPC("Kid", 2, 15, 'C', KidSpeech);
	gameObjects[10] = new NPC("Villager", 4, 40, 'V', HvillagersSpeech);
	gameObjects[11] = new Merchant("Travelling Merchant", 0, 28, '!', MerchantSpeech);
	gameObjects[12] = new NPC("Old Man", 0, 10, 'M', OldManSpeech);
	gameObjects[13] = new Enemy("Hero", 0, 0, 'H');
	for (int i = 14; i < 27; i++) {
		gameObjects[i] = new NPC("Interaction", 1, 1, '!');
	}

	gameObjects[2]->setPosition(23, 4); //villager
	gameObjects[3]->setPosition(8, 1); //villager
	gameObjects[4]->setPosition(13, 4); //villager
	gameObjects[5]->setPosition(20, 0); //villager
	gameObjects[6]->setPosition(30, 2); //villager
	gameObjects[14]->setPosition(17, 0); //guys at the table
	gameObjects[15]->setPosition(9, 0); //go back to inn
	gameObjects[16]->setPosition(35, 0); // the house in town
	gameObjects[17]->setPosition(23, 0); // forest rock
	gameObjects[18]->setPosition(10, 0); // the birds
	gameObjects[19]->setPosition(35, 4); // the thing on forest floor
	gameObjects[20]->setPosition(37, 0); // the captain
	gameObjects[21]->setPosition(10, 0); // the ship
	gameObjects[22]->setPosition(19, 4); // the barrel
	gameObjects[23]->setPosition(25, 0); // go into the cave
	gameObjects[24]->setPosition(25, 4); // the view
	gameObjects[25]->setPosition(39, 0); // the rock
	gameObjects[26]->setPosition(28, 0); //altar

	Merchant* john = static_cast<Merchant*>(gameObjects[11]);
	Player* player = static_cast<Player*>(gameObjects[0]);

	Inventory* playerInv = player->getInv();

	RiverPuzzle = new Puzzle(player);

	//ITEM CREATION AREA
	Item* MythrilSword = Item::create("Mythril Sword", Item::MYTHRIL_SWORD, 45, 1);
	Item* SteelSword = Item::create("Steel Sword", Item::STEEL_SWORD, 25, 1);
	Item* WoodSword = Item::create("Wood Sword", Item::WOOD_SWORD, 5, 1); 


	Item* HPpotion = Item::create("HP_Potion", Item::HP_POT, 20, 5);
	Item* ManaPotion = Item::create("Mana Potion", Item::MANA_POT, 20, 5);

	MythrilSword->addDesc("A blade forged from the depths of the underground\n. Lightweight, Strong, somewhat resembling the texture of steel. +6 DMG.");
	WoodSword->addDesc("... Why did you buy this? This is a stick. Your fists punch harder than this. -7 DMG.");
	SteelSword->addDesc("Nothing special, nothing normal either. A metallic sword forged to slice your enemies in half. +3 DMG.");

	HPpotion->addDesc("A simple drink of this potion and you will be A-OK. +10 HP");
	ManaPotion->addDesc("Run out of mana? Drink up and cast your spells! +20 MANA");


	john->addStock(MythrilSword);
	john->addStock(SteelSword);
	john->addStock(WoodSword);
	john->addStock(HPpotion);
	john->addStock(ManaPotion);


 }

void Game::drawWorld() {

	char grid[5][49];
	for (int r = 0; r < 5; ++r)
		for (int c = 0; c < 49; ++c)
			grid[r][c] = ' ';

	for (int i = 26; i > -1; --i) {
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

	//morale
	
	std::cout << '|';
	for (int i = 0;i < player->getMorale();i++)
	{
		std::cout << '#';
	}
	for (int i = player->getMorale();i < 96;i++)
	{
		std::cout << ' ';
	}
	std::cout << '|'<<endl;


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
	else if (InForest == true && gameObjects[0]->getX() < 1 && BearAlive == false && KidTriggered == true)
	{
		InForest = false;
		puzzleActive = true;
		gameObjects[0]->setPosition(47, gameObjects[0]->getY()); // Set player position in town
		player->puzzleSet(true);
	}
	// if player go right of the Harbour, go back to Forest
	else if (puzzleActive == true && gameObjects[0]->getX() < 1)
	{
		puzzleActive = false;
		InHarbour = true;
		gameObjects[0]->setPosition(47, 2);
		player->puzzleSet(false);
	}
	else if (puzzleActive == true && gameObjects[0]->getX() > 47)
	{
		puzzleActive = false;
		InForest = true;
		gameObjects[0]->setPosition(0, 2);
		player->puzzleSet(false);
	}
	else if (InHarbour == true && gameObjects[0]->getX() > 47)
	{
		InHarbour = false;
		InForest = true;
		gameObjects[0]->setPosition(1, gameObjects[0]->getY()); // Set player position in town
		player->puzzleSet(true);
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
		for (int i = 0;i < 27;i++) {
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
			for (int i = 0;i < 27;i++) {
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
			for (int i = 0;i < 27;i++) {
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
			for (int i = 0;i < 27;i++) {
				if (i == 0 || i == 8 || i == 9 || i == 17 || i == 18 || i == 19) {
					gameObjects[i]->setActive(true);
				}
				else {
					gameObjects[i]->setActive(false);
				}
			}
		}
		else {
			for (int i = 0;i < 27;i++) {
				if (i == 0 || i == 9 || i == 17 || i == 18 || i == 19) {
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
		for (int i = 0;i < 27;i++) {
			if (i == 0 || i == 10 || i == 11 || i ==  20 || i == 21 || i ==  22) {
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
		for (int i = 0;i < 27;i++) {
			if (i == 0 || i == 12 || i == 23 || i == 24 || i == 25) {
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
		for (int i = 0;i < 27;i++) {


			if (i == 0 || i == 26) {


				gameObjects[i]->setActive(true);
			}
			else if (i != 13) {
				gameObjects[i]->setActive(false);
			}
		}
	}
	else if (puzzleActive == true)
	{
		RiverPuzzle->doPuzzle();
		RiverPuzzle->Print();
	}
	if (puzzleActive == false)
	{
	drawWorld();
	}

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
				GtypeLine("(WASD to move, SPACE to interact, I to open inventory, ! are interactables)", 1);
				GtypeLine("(If player presses WASD while text is writing, the player will move immediately after it finishes)", 1);
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("How did I get here? Wasn't I knocked unconscious by the hero?", 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("I should talk to the Inn Keeper for more details.", 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					std::cout << "\033[0;36m" << "Guy on right: " << "\033[0m";
					GtypeLine("Yeah! Now I can finally sleep in peace knowing I won't be targeted!", 1);
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("I should ask around town for more information.", 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

					// Launch the combat mini-game
					battleArenaScene(player);

					if (player->getPlayerHP() != 0) {
						BKAlive = false;
						return;
					}
					else {
						InTown = false;
						InInn = true;
						player->setPosition(8, 0);
						player->addPlayerHP(50);
					}
				}
			}
			else if (gameObjects[0]->getY() == gameObjects[7]->getY() && (gameObjects[0]->getX() == gameObjects[7]->getX() + 1 || gameObjects[0]->getX() == gameObjects[7]->getX() - 1)) {
				if (BKAlive) {
					braveknight->NPCtalk();

					// Launch the combat mini-game
					battleArenaScene(player);

					if (player->getPlayerHP() != 0) {
						BKAlive = false;
						return;
					}
					else {
						InTown = false;
						InInn = true;
						player->setPosition(8, 0);
						player->addPlayerHP(50);
					}
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
				GtypeLine("Phew, that was close.", 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Wait, what's happening over there?", 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Is someone being attacked?", 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("I got to go help them!", 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				NarraForest = false;
			}
			if (interactedrock) {
				if (gameObjects[0]->getX() == 23 && gameObjects[0]->getY() == 0)
				{
					std::cout << "Press SPACE to interact" << std::endl;
					if (player->interactionGet())
					{
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("This is an ordinary rock. However, there's something ominous about it that keeps your guard up.", 1);
						std::cout << " " << std::endl;
						playerInv->setGold(30);//plus 30 gold
						GtypeLine("+30 gold", 1);
						interactedrock = false;
						delete gameObjects[17];
					}
				}
			}

			if (interactedground) {
				if (gameObjects[0]->getX() == 10 && gameObjects[0]->getY() == 0)
				{
					std::cout << "Press SPACE to observe" << std::endl;
					if (player->interactionGet())
					{
						std::cout << "\033[1;31m" << "Bird" << ": " << "\033[0m";
						GtypeLine("Chirp Chirp.", 1);
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("These birds seem to be hiding something valuable with them.", 1);
						std::cout << " " << std::endl;
						playerInv->setGold(30);
						GtypeLine("+30 gold", 1);
						interactedground = false;
						delete gameObjects[18];
					}

				}
			}

			if (interactedbird) {
				if (gameObjects[0]->getX() == 35 && gameObjects[0]->getY() == 4)
				{
					std::cout << "Press SPACE to pick up" << std::endl;
					if (player->interactionGet())
					{
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("Oh, who left this here? ", 1);
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("Well, as they always say, finders keepers.", 1);
						std::cout << " " << std::endl;
						playerInv->setGold(30);
						GtypeLine("+30 gold", 1);
						interactedbird = false;
						delete gameObjects[19];
					}
				}
			}

			if (gameObjects[0]->getY() == gameObjects[8]->getY() && (gameObjects[0]->getX() == gameObjects[8]->getX() + 1 || gameObjects[0]->getX() == gameObjects[8]->getX() - 1)) {
				if (BearAlive) {
					bear->NPCtalk();
					
					//Added Bear Attack
					battleArenaBearForest(player);

					if (player->getPlayerHP() != 0) {
						BearAlive = false;
						return;
					}
					else {
						InForest = false;
						InTown = true;
						player->setPosition(39, 2);
						player->addPlayerHP(50);
					}
				}
			}
			else if (gameObjects[0]->getX() == gameObjects[8]->getX() && (gameObjects[0]->getY() == gameObjects[8]->getY() + 1 || gameObjects[0]->getY() == gameObjects[8]->getY() - 1)) {
				if (BearAlive) {
					bear->NPCtalk();

					//Added Bear Attack
					battleArenaBearForest(player);

					if (player->getPlayerHP() != 0) {
						BearAlive = false;
						return;
					}
					else {
						InForest = false;
						InTown = true;
						player->setPosition(39, 2);
						player->addPlayerHP(50);
					}
				}
			}
			if (gameObjects[0]->getY() == gameObjects[9]->getY() && (gameObjects[0]->getX() == gameObjects[9]->getX() + 1 || gameObjects[0]->getX() == gameObjects[9]->getX() - 1) && BearAlive == false && KidTriggered == false) {
				std::cout << "Press SPACE to interact with the kid" << std::endl;
				if (player->interactionGet()) {
					kid->NPCtalk();
					KidTriggered = true;
				}
			}
			else if (gameObjects[0]->getX() == gameObjects[9]->getX() && (gameObjects[0]->getY() == gameObjects[9]->getY() + 1 || gameObjects[0]->getY() == gameObjects[9]->getY() - 1) && BearAlive == false && KidTriggered == false) {
				std::cout << "Press SPACE to interact with the kid" << std::endl;
				if (player->interactionGet()) {
					kid->NPCtalk();
					KidTriggered = true;
				}
			}
			if (KidTriggered) {
				if (gameObjects[9]->getX() < 49) {
					gameObjects[9]->pos.x++;
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
					return;
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
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Maybe the villagers here would have an idea on where the hero might be.", 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Let me explore the area first.", 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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

			if (interactedbarrel) {
				if (gameObjects[0]->getX() == 19 && gameObjects[0]->getY() == 4)
				{
					std::cout << "Press SPACE to search" << std::endl;
					if (player->interactionGet())
					{
						std::cout << "\033[1;34m" << "Barrel" << ": " << "\033[0m";
						GtypeLine("This barrel is full of fish. However, there's a glowing item hidden in the fishes...", 1);
						std::cout << " " << std::endl;
						playerInv->setGold(30);
						GtypeLine("+30 gold", 1);
						interactedbarrel = false;
						delete gameObjects[22];
					}
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
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("Or else I was as good as dead", 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
				GtypeLine("This island is pretty big, let's start finding the cave.", 1);
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
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
			else if (gameObjects[0]->getX() == 39 && gameObjects[0]->getY() == 0)
			{
				std::cout << "Press SPACE to interact" << std::endl;
				if (player->interactionGet())
				{
					std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
					GtypeLine("This rock has a person's name written on it. However, I can't make out the name as it has long faded.", 1);
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
			if (gameObjects[0]->getY() == gameObjects[12]->getY() && (gameObjects[0]->getX() == gameObjects[12]->getX() + 1 || gameObjects[0]->getX() == gameObjects[12]->getX() - 1)) {
				std::cout << "Press SPACE to interact with the old man" << std::endl;
				if (player->interactionGet()) {
					oldman->NPCtalk();
				}
			}
			else if (gameObjects[0]->getX() == gameObjects[12]->getX() && (gameObjects[0]->getY() == gameObjects[12]->getY() + 1 || gameObjects[0]->getY() == gameObjects[12]->getY() - 1)) {
				std::cout << "Press SPACE to interact with the old man" << std::endl;
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
				std::this_thread::sleep_for(std::chrono::milliseconds(1000));
				NarraInsideCave = false;
			}
			if (gameObjects[0]->getX() == 10) {
				if (NarraInsideCave2)
				{
					std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
					GtypeLine("Wait a second ... is that what I think it is?", 1);
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
					GtypeLine("What is the demon altar doing here?", 1);
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
					GtypeLine("I remember using it back then, but I don't remember using it here.", 1);
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
					GtypeLine("I need to check it out to make sure it actually is the altar.", 1);
					std::this_thread::sleep_for(std::chrono::milliseconds(1000));
					NarraInsideCave2 = false;
				}
			}

			if (gameObjects[0]->getX() == 28 && gameObjects[0]->getY() == 0 && HeroTriggered == false)
			{
				if (interactedaltar) {
					std::cout << "Press SPACE to check if it is an altar" << std::endl;
					if (player->interactionGet()) {
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("It really is the altar, looks different from before.", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("Should I use it again? I can get more power if I do.", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						interactedaltar = false;
						delete gameObjects[26];
						HeroTriggered = true;
						return;
					}
				}
			}
			if (HeroTriggered) {
				gameObjects[13]->setActive(true);
				if (gameObjects[13]->getX() < 26) {
					gameObjects[13]->pos.x++;
					std::this_thread::sleep_for(std::chrono::milliseconds(50));
					if (gameObjects[13]->getX() == 15)
					{
						clearDialogue();
					}
					return;
				}
				else {
					HeroTriggered = false;
					if (player->getMorale() <= 48) {
						hero->dialogue = GHeroSpeech;
					}
					else{
						hero->dialogue = BHeroSpeech;
					}
					hero->NPCtalk();
				}
			}
			if (gameObjects[0]->getX() == gameObjects[13]->getX() && (gameObjects[0]->getY() == gameObjects[13]->getY() + 1 || gameObjects[0]->getY() == gameObjects[13]->getY() - 1)) {
				std::cout << "Press SPACE to fight with the Hero" << std::endl;
				if (player->interactionGet()) {
					if (HeroAlive) {
						FinalBattle(player);  // launches the ASCII battle scene (blocking until win/lose/quit)

						if (player->getPlayerHP() != 0) {
							HeroAlive = false;
							return;
						}
						else {
							player->setPosition(28, 0);
							player->addPlayerHP(50);
						}
					}
					if (HeroAlive == false && player->getMorale() <= 48)
					{
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("Ughh....", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("MC...stop this no..w...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("I kn..ow you..s..till...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("c..an...c.ha..ng..e....", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("P...leas....e.", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("It's too late hero, give up and pass quietly", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("y..ou....", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("Well, I guess it's time...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("Time to dominate the world", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << " " << std::endl;
						std::cout << "\033[1;36m" << "Narration" << ": " << "\033[0m";
						GtypeLine("To be continued...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));

						system("cls");
						show_end_cutscene();
					}

					else if (HeroAlive == false && player->getMorale() >= 48)
					{
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("Huff ... huff ...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("Thank you for saving me MC, I truly owe you one.", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("If you like, I can clear some of your misdeeds so that you get a lighter sentence.", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("However, I cannot fully clear all your wrongdoings though.", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("Let's go back to the town alright?", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("Yeah...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << " " << std::endl;
						std::cout << "\033[1;36m" << "Narration" << ": " << "\033[0m";
						GtypeLine("To be continued...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));

						system("cls");
						show_end_cutscene();
					}
				}
			}
			else if (gameObjects[0]->getY() == gameObjects[13]->getY() && (gameObjects[0]->getX() == gameObjects[13]->getX() + 1 || gameObjects[0]->getX() == gameObjects[13]->getX() - 1)) {
				std::cout << "Press SPACE to fight with the Hero" << std::endl;
				if (player->interactionGet()) {
					if (HeroAlive) {
						FinalBattle(player); // launches the ASCII battle scene (blocking until win/lose/quit)
						clearDialogue();

						if (player->getPlayerHP() != 0) {
							HeroAlive = false;
							return;
						}
						else {
							player->setPosition(28, 0);
							player->addPlayerHP(50);
						}
					}
					if (HeroAlive == false && player->getMorale() <= 48)
					{
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("Ughh....", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("MC...stop this no..w...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("I kn..ow you..s..till...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("c..an...c.ha..ng..e....", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("P...leas....e.", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("It's too late hero, give up and pass quietly", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("y..ou....", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("Well, I guess it's time...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("Time to dominate the world", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << " " << std::endl;
						std::cout << "\033[1;36m" << "Narration" << ": " << "\033[0m";
						GtypeLine("To be continued...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));

						// Call cutscene
						system("cls");
						show_end_cutscene();
					}

					else if(HeroAlive == false && player->getMorale() >= 48)
					{
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("Huff ... huff ...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("Thank you for saving me MC, I truly owe you one.", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("If you like, I can clear some of your misdeeds so that you get a lighter sentence.", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("However, I cannot fully clear all your wrongdoings though.", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;33m" << "Hero" << ": " << "\033[0m";
						GtypeLine("Let's go back to the town alright?", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << "\033[1;34m" << player->name << ": " << "\033[0m";
						GtypeLine("Yeah...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						std::cout << " " << std::endl;
						std::cout << "\033[1;36m" << "Narration" << ": " << "\033[0m";
						GtypeLine("To be continued...", 1);
						std::this_thread::sleep_for(std::chrono::milliseconds(1000));
						system("cls");

						show_end_cutscene();

					}
				}
			}
			
		}
	}


	int oldX = player->getX();
	int oldY = player->getY();

	if (player != nullptr) {
		player->move(gameObjects, 27);
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


		std::cout << "\033[" << (23 + i) << ";1H";   // move to each line start
		std::cout << std::string(120, ' '); // clear each line and replace with space
	}
	std::cout.flush();
}
