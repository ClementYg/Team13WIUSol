#pragma once
#include "NPC.h"
class Enemy : public NPC
{
public:
	Enemy(std::string n, int y, int x, char s, std::vector<std::string> lines = {});
	~Enemy();


	void NPCtalk();
};

