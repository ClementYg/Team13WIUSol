#pragma once
#include "Entity.h"

class Enemy1 : public Entity
{
private:
	std::string name;

public:
	Enemy1(std::string n, int y, int x, char s);
	~Enemy1();

	void move(Entity* gameObjects[], int entityCount);
	//void move(Position playerPos, Entity* gameObjects[], int entityCount);

	void move(Position playerPos, Entity* gameObjects[], int entityCount);

}
;
