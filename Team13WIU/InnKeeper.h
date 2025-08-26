#pragma once
#include "NPC.h"
class InnKeeper : public NPC
{
public:
	InnKeeper(std::string n, int y, int x, char s, std::vector<std::string> lines = {});
	~InnKeeper();

	
	void NPCtalk();
};

