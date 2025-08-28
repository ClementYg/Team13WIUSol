#pragma once
#include "Entity.h"
#include "Player.h"
#include "obstacle.h"
class Puzzle
{
private:
	Player* MC;
	int oldplayerX;
	int oldplayerY;
	obstacle* obstacleList[2];

public:
	Puzzle(Entity*);
	void Print();
	void doPuzzle();
};