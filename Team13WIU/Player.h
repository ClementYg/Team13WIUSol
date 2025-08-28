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

	const int MAX_HP = 50;
	int playerHP;
	const int MAX_MANA = 100;
	int playerMana;

	int weaponDmg;

public:
	std::string name;
	Player(std::string n, int y, int x, char s);
	~Player();
	void puzzleSet(bool);


	Inventory* getInv();
	bool interactionGet();
	bool movingGet();


	//COMBAT USE
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

	int getWeaponDmg();

	void setWeaponDmg(int newValue);

	void addPlayerHP(int change); 
	void addPlayerMana(int change); 




	void move(Entity* gameObjects[], int entityCount);
	void move(int, int);
	int getMorale();
	void setMorale(int);
};

