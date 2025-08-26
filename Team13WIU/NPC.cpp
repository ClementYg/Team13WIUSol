#include "NPC.h"
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

// Constructor for NPC class
NPC::NPC(std::string n, int y, int x, char s,std::vector<std::string> lines)
{
	name = n;
	dialogue = lines;
	pos.x = x;
	pos.y = y;
	symbol = s;
	// this massage can be comment away as it is for debugging or checking
	//std::cout << name << " spawned at (" << NPCspos.x << ',' << NPCspos.y << ")\n";
}

// Destroy NPC to free memory
NPC::~NPC()
{
	// this can be comment away as it is for debugging or checking
	//std::cout << name << " at " << '(' << NPCspos.x << ',' << NPCspos.y << ')' << " is deleted\n";
}

// this function help to type out the word one character by one
void NPC::typeLine(const std::string& text, int delay)
{
	for (char c : text) {
		// flush means stop
		std::cout << c << std::flush;
		std::this_thread::sleep_for(std::chrono::milliseconds(delay));
	}
	std::cout << std::endl;
}

// function that make the NPC talk
void NPC::NPCtalk()
{
	// size_t is similar to int, its unsigned which means cannot be negative
	for (size_t i = 0; i < dialogue.size(); i++) {
		std::string& line = dialogue[i];

		// make name blue
		std::cout << "\033[36m" << name << ": " << "\033[0m";
		typeLine(line, 1);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));  // wait for 300ms before printing next line
	}
	// one blank line after every line finish, more neat
	std::cout << std::endl;
}

void NPC::move(Entity* gameObjects[], int size)
{

}