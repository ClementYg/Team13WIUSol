#pragma once
#include "Entity.h"

class Player : public Entity
{
private:
	std::string name;
	bool interaction;

public:
	Player(std::string n, int y, int x, char s);
	~Player();
	bool interactionGet();
	void move(Entity* gameObjects[], int entityCount);

};

