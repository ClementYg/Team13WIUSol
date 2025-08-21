#pragma once
#include "NPC.h"
class Master : public NPC
{
public:
	Master(std::string n, int x, int y, std::vector<std::string> lines = {});

	virtual void NPCtalk();
	void trainPlayer();
};

