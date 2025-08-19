#include "Master.h"
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

Master::Master(std::string n, int x, int y, std::vector<std::string> lines) : NPC(n, x, y, lines)
{

}

void Master::trainPlayer()
{
	std::cout << "I will train you";
	// maybe PlayerLevel += 1;
}

void Master::NPCtalk()
{
	for (size_t i = 0; i < dialogue.size(); i++) {
		std::string& line = dialogue[i];

		// Those weird code is to make it green
		std::cout << "\033[38;5;214m" << name << ": " << "\033[0m";

		for (char c : line) {
			std::cout << c << std::flush;          // print one character
			std::this_thread::sleep_for(std::chrono::milliseconds(20)); // change speed
		}
		std::cout << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
}