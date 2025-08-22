#include "Merchant.h"
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

// The : NPC(n, x, y, lines) is needed because the NPC has no default constructor (NPC())
// It simply means "When creating a Merchant, call the NPC constructor with these arguments."
Merchant::Merchant(std::string n, int x, int y, std::vector<std::string> lines) : NPC(n, x, y, lines)
{

}

void Merchant::trade()
{
	std::cout << "\033[1;32m" << name << ": " << "\033[0m";
	typeLine("You want to trade?", 20);
	std::cout << "Do you want to trade? (Y/N): ";
	std::cin >> IsTrade;
	if (IsTrade == 'Y') {
		std::cout << "\033[1;32m" << name << ": " << "\033[0m";
		typeLine("(The items he sell)\n", 20);
	}
	else {
		std::cout << "\033[1;32m" << name << ": " << "\033[0m";
		typeLine("Okay! come back later then.\n", 20);
	}
}

void Merchant::NPCtalk()
{
	for (size_t i = 0; i < dialogue.size(); i++) {
		std::string& line = dialogue[i];

		// make name green
		std::cout << "\033[1;32m" << name << ": " << "\033[0m";
		typeLine(line, 1);

		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
	std::cout << std::endl;
}