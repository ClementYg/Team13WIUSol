#include "InnKeeper.h"
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

InnKeeper::InnKeeper(std::string n, int y, int x, char s, std::vector<std::string> lines) : NPC(n, y, x, s, lines)
{

}

InnKeeper::~InnKeeper()
{

}

void InnKeeper::NPCtalk()
{
	for (size_t i = 0; i < dialogue.size(); i++) {
		std::string& line = dialogue[i];

		// make name cyan
		std::cout << "\033[36m" << name << ": " << "\033[0m";
		//std::cout << name << ": ";
		typeLine(line, 1);

		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
	std::cout << std::endl;
}
