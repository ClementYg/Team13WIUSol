#pragma once
#include "Entity.h"
#include "Inventory.h"

class Player : public Entity
{
private:
	
	bool interaction;
	bool moveinter;
	Inventory playerInv;
	int Morale;
public:
	std::string name;
	Player(std::string n, int y, int x, char s);
	~Player();
	bool interactionGet();
	bool movingGet();
	void move(Entity* gameObjects[], int entityCount);
	int getMorale();
	void setMorale(int);
};

