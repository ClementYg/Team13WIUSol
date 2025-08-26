#pragma once
#include "Entity.h"
#include "Inventory.h"

class Player : public Entity
{
private:
	std::string name;
	bool interaction;
	Inventory playerInv;
	int Morale;
public:
	Player(std::string n, int y, int x, char s);
	~Player();
	bool interactionGet();
	void move(Entity* gameObjects[], int entityCount);
	int getMorale();
	void setMorale(int);
};

