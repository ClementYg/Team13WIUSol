#include "NPC.h"
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

// Create a NPC and tell its position
NPC::NPC(std::string n, int x, int y, std::vector<std::string> lines)
{
	name = n;
	dialogue = lines;
	NPCspos.x = x;
	NPCspos.y = y;
	std::cout << name << " spawned at (" << NPCspos.x << ',' << NPCspos.y << ")\n";
}

// Destroy NPC to free memory
NPC::~NPC()
{
	//std::cout << name << " at " << '(' << NPCspos.x << ',' << NPCspos.y << ')' << " is deleted\n";
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

// function that make the NPC talk
void NPC::NPCtalk()
{
	for (size_t i = 0; i < dialogue.size(); i++) {
		std::string& line = dialogue[i];

		// Those weird code is to make it blue
		std::cout << "\033[1;34m" << name << ": " << "\033[0m";

		for (char c : line) {
			std::cout << c << std::flush;          // print one character
			std::this_thread::sleep_for(std::chrono::milliseconds(20)); // wait 50ms
		}
		std::cout << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(300));
	}
}