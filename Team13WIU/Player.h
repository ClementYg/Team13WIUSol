#pragma once
#include "Entity.h"
class Player : public Entity
{
private:
	std::string name;

public:
	Player(int row, int col);
	~Player();
	void move(Entity* gameObjects[], int entityCount);

};

