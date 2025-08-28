#pragma once
#include "Entity.h"
#include "Inventory.h"

class Player : public Entity
{
private:
	bool interaction;
	Inventory* playerInv;
	bool moveinter;
	int Morale;
	bool inPuzzle;

public:
	std::string name;
	Player(std::string n, int y, int x, char s);
	~Player();
	void puzzleSet(int);
	Inventory* getInv();
	bool interactionGet();
	bool movingGet();
	void move(Entity* gameObjects[], int entityCount);
	int getMorale();
	void setMorale(int);
};

