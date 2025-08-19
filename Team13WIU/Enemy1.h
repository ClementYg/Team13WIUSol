#pragma once
#include "Entity.h"
class Enemy1 : public Entity
{
public:
	Enemy1(int row, int col);
	~Enemy1();

	void move(Entity* gameObjects[], int entityCount) override;
	void move(Position playerPos, Entity* gameObjects[], int entityCount);

}
;
