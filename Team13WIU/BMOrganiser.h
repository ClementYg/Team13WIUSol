#pragma once
#include "NPC.h"
class BMOrganiser : public NPC
{
public:
	BMOrganiser(std::string n, int x, int y, std::vector<std::string> lines = {});

	virtual void NPCtalk();
	void rewardPlayer();
};

