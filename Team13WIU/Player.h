#pragma once
#include "Entity.h"
#include "Inventory.h"

class Player : public Entity
{
private:
	std::string name;
	bool interaction;
	Inventory* playerInv;
	bool moveinter;

public:
	Player(std::string n, int y, int x, char s);
	~Player();
	Inventory* getInv();
	bool interactionGet();
	bool movingGet();
	void move(Entity* gameObjects[], int entityCount);

};

