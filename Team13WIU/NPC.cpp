#include "NPC.h"
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

// Constructor for NPC class
NPC::NPC(std::string n, int x, int y, std::vector<std::string> lines)
{
	name = n;
	dialogue = lines;
	NPCspos.x = x;
	NPCspos.y = y;
	// this massage can be comment away as it is for debugging or checking
	std::cout << name << " spawned at (" << NPCspos.x << ',' << NPCspos.y << ")\n";
}

// Destroy NPC to free memory
NPC::~NPC()
{
	// this can be comment away as it is for debugging or checking
	std::cout << name << " at " << '(' << NPCspos.x << ',' << NPCspos.y << ')' << " is deleted\n";
}

// function to set X position
void NPC::setX(int x)
{
	NPCspos.x = x;
}

// function to set Y position
void NPC::setY(int y)
{
	NPCspos.y = y;
}

// function to get X position
int NPC::getX() const
{
	return NPCspos.x;
}

// function to get Y position
int NPC::getY() const
{
	return NPCspos.y;
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
		std::cout << "\033[1;34m" << name << ": " << "\033[0m";
		typeLine(line, 20);
		std::this_thread::sleep_for(std::chrono::milliseconds(300));  // wait for 300ms before printing next line
	}
	// one blank line after every line finish, more neat
	std::cout << std::endl;
}