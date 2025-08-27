#include "Enemy.h"
#include <chrono>
#include <thread>
#include <string>
#include <iostream>

Enemy::Enemy(std::string n, int y, int x, char s, std::vector<std::string> lines) : NPC(n, y, x, s, lines)
{

}

Enemy::~Enemy()
{

}

void Enemy::NPCtalk()
{
	for (size_t i = 0; i < dialogue.size(); i++) {
		std::string& line = dialogue[i];

		// make name green
		std::cout << "\033[1;31m" << name << ": " << "\033[0m";
		typeLine(line, 1);

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
	std::cout << std::endl;
}