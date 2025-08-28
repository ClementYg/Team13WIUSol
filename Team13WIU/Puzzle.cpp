#include "Puzzle.h"
#include "Player.h"
#include "obstacle.h"
#include <iostream>
Puzzle::Puzzle(Entity* player) : MC(static_cast<Player*>(player)), oldplayerX(0), oldplayerY(0), hole1active(true), hole2active(true) {
	obstacleList[0] = new obstacle(33,3);
	obstacleList[1] = new obstacle(41, 14);
	for (int r = 0; r < 18; ++r)
		for (int c = 0; c < 49; ++c)
			if (((c == 19 || c == 29) && r != 8) || ((c > 19 && c < 29) && (r == 7 || r == 9)))
				grid[r][c] = 'X';
			else if ((c == 27 && r == 8) || (c == 22 && r == 8))
				grid[r][c] = 'O';
			else
				grid[r][c] = ' ';
}

void Puzzle::Print() {

	MC->setActive(true);

	for (int r = 0; r < 18; ++r)
		for (int c = 0; c < 49; ++c)
			if (((c == 19 || c == 29) && r != 8) || ((c > 19 && c < 29) && (r == 7 || r == 9)))
				grid[r][c] = 'X';
			else if ((c == 27 && r == 8) || (c == 22 && r == 8))
				grid[r][c] = 'O';
			else
				grid[r][c] = ' ';

	for (int i = 0; i < 2; ++i) {
		if (obstacleList[i] != nullptr) {
			int r = obstacleList[i]->getY();
			int c = obstacleList[i]->getX();
			if (r >= 0 && r < 18 && c >= 0 && c < 49) {
				grid[r][c] = obstacleList[i]->getSymbol();
			}
		}
	}
	if (MC != nullptr) {
		if (MC->getActive())
		{
			int r = MC->getY();
			int c = MC->getX();
			if (r >= 0 && r < 18 && c >= 0 && c < 47) {
				grid[r][c] = MC->getSymbol();
			}
		}
	}
	for (int i = 0; i < 98; i++) {
		std::cout << '-';
		if (i == 97) std::cout << "\n"; // New line after the border
	}

	for (int r = 0; r < 18; ++r) {
		for (int c = 0; c < 49; ++c) std::cout << " " << grid[r][c];
		std::cout << " \n";
	}

	for (int i = 0; i < 98; i++) {
		std::cout << '-';
		if (i == 97) std::cout << "\n" << "Push the rocks (#) into the holes (O) to continue."; // New line after the border
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
				if (grid[obstacleList[i]->getY()][obstacleList[i]->getX()] == 'X')
				{
					MC->move((oldplayerX - obstacleList[i]->getX()) / 2, (oldplayerY - obstacleList[i]->getY()) / 2);
					obstacleList[i]->move((oldplayerX - obstacleList[i]->getX())/2, (oldplayerY - obstacleList[i]->getY())/2);
				}
				if (grid[obstacleList[i]->getY()][obstacleList[i]->getX()] == 'O')
				{
					obstacleList[i]->setActive(false);
					grid[obstacleList[i]->getY()][obstacleList[i]->getX()] = ' ';
				}
				if (obstacleList[i]->getY() < 0)
				{
					obstacleList[i]->setPosition(obstacleList[i]->getX(), 1);
				}
				if (obstacleList[i]->getY() > 17)
				{
					obstacleList[i]->setPosition(obstacleList[i]->getX(), 16);
				}
			}
		}
	}
	if (grid[MC->getY()][MC->getX()] == 'O' || grid[MC->getY()][MC->getX()] == 'X')
	{
		MC->move(oldplayerX - MC->getX(), oldplayerY - MC->getY());
	}
	oldplayerX = MC->getX();
	oldplayerY = MC->getY();
}