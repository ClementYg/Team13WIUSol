#include "BMOrganiser.h"
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

BMOrganiser::BMOrganiser(std::string n, int x, int y, std::vector<std::string> lines) : NPC(n, x, y, lines)
{

}

void BMOrganiser::NPCtalk()
{
	for (size_t i = 0; i < dialogue.size(); i++) {
		std::string& line = dialogue[i];

		// make name dark gray
		std::cout << "\033[1;30m" << name << ": " << "\033[0m";

		typeLine(line, 20);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
	std::cout << std::endl;
}

void rewardPlayer()
{
	// maybe player addItem(sword);
}