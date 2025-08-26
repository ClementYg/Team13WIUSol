#pragma once
#include "NPC.h"
class Master : public NPC
{
public:
	Master(std::string n, int x, int y, char s,std::vector<std::string> lines = {});
	~Master();

	void NPCtalk();
	void trainPlayer();
};

