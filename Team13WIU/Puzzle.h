#pragma once
#include "Entity.h"
#include "Player.h"
class Puzzle
{
private:
	Player* MC;
public:
	Puzzle(Entity*);
	void Print();
};