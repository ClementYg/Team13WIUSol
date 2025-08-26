#include "Puzzle.h"
#include "Player.h"
#include <iostream>
Puzzle::Puzzle(Entity* player) : MC(static_cast<Player*>(player)) {}

void Puzzle::Print() {

	MC->setActive(true);

	char grid[20][49];
	for (int r = 0; r < 20; ++r)
		for (int c = 0; c < 49; ++c)
			grid[r][c] = ' ';

	for (int i = 0; i < 3; ++i) {
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