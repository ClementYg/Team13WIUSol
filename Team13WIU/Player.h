#pragma once
#include "Entity.h"
#include "Inventory.h"

class Inventory; 

class Player : public Entity
{
private:
	bool interaction;
	Inventory* playerInv;
	bool moveinter;
	int Morale;
	bool inPuzzle;


	//COMBAT SYSTEM AND ITEM USAGE
	int playerX , playerY;

	const int MAX_HP = 5;
	int playerHP;
	const int MAX_MANA = 100;
	int playerMana;

public:
	std::string name;
	Player(std::string n, int y, int x, char s);
	~Player();
	// void puzzleSet(int);


	Inventory* getInv();
	bool interactionGet();
	bool movingGet();

	int getMaxHP();
	int getMaxMana();

	void setPlayerX(int newValue);
	void setPlayerY(int newValue);

	void addPlayerX(int change);
	void addPlayerY(int change);

	int getPlayerX();
	int getPlayerY();

	int getPlayerHP();
	int getPlayerMana();

	void addPlayerHP(int change); 
	void addPlayerMana(int change); 


	void move(Entity* gameObjects[], int entityCount);
	int getMorale();
	void setMorale(int);
};

