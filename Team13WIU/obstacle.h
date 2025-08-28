#pragma once
#include "Entity.h"
class obstacle : public Entity
{
public:
	void move(Entity* unused[], int);
	obstacle(int, int);
	void move(int, int);
};