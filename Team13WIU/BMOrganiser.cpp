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

		// Those weird code is to make it green
		std::cout << "\033[1;30m" << name << ": " << "\033[0m";

		for (char c : line) {
			std::cout << c << std::flush;          // print one character
			std::this_thread::sleep_for(std::chrono::milliseconds(20)); // change speed
		}
		std::cout << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
}

void rewardPlayer()
{
	// maybe player addItem(sword);
}