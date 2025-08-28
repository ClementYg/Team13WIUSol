#include "Puzzle.h"
#include "Player.h"
#include "obstacle.h"
#include <iostream>
Puzzle::Puzzle(Entity* player) : MC(static_cast<Player*>(player)) {
	obstacleList[0] = new obstacle(40,2);
	obstacleList[1] = new obstacle(39, 6);
}

void Puzzle::Print() {

	MC->setActive(true);

	char grid[20][49];
	for (int r = 0; r < 20; ++r)
		for (int c = 0; c < 49; ++c)
			grid[r][c] = ' ';

	for (int i = 0; i < 2; ++i) {
		if (obstacleList[i] != nullptr) {
			if (obstacleList[i]->getActive())
			{
				int r = obstacleList[i]->getY();
				int c = obstacleList[i]->getX();
				if (r >= 0 && r < 20 && c >= 0 && c < 49) {
					grid[r][c] = obstacleList[i]->getSymbol();
				}
			}
		}
	}
	if (MC != nullptr) {
		if (MC->getActive())
		{
			int r = MC->getY();
			int c = MC->getX();
			if (r >= 0 && r < 20 && c >= 0 && c < 49) {
				grid[r][c] = MC->getSymbol();
			}
		}
	}
	for (int i = 0; i < 98; i++) {
		std::cout << '-';
		if (i == 97) std::cout << "\n"; // New line after the border
	}

	for (int r = 0; r < 20; ++r) {
		for (int c = 0; c < 49; ++c) std::cout << " " << grid[r][c];
		std::cout << " \n";
	}

	for (int i = 0; i < 98; i++) {
		std::cout << '-';
		if (i == 97) std::cout << "\n"; // New line after the border
	}
}

void Puzzle::doPuzzle()
{
	for (int i = 0; i < 2; ++i) {
		if (obstacleList[i] != nullptr) {
			if (obstacleList[i]->getActive()) {
				if (MC->getX() == obstacleList[i]->getX() && MC->getY() == obstacleList[i]->getY())
				{
					obstacleList[i]->move(obstacleList[i]->getX() - oldplayerX, obstacleList[i]->getY() - oldplayerY);
				}
			}
		}
	}
	oldplayerX = MC->getX();
	oldplayerY = MC->getY();
}
