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
	char grid[20][49];
	bool hole1active;
	bool hole2active;
public:
	Puzzle(Entity*);
	void Print();
	void doPuzzle();
};