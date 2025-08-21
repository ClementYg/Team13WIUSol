#pragma once
#include "NPC.h"
class Merchant : public NPC
{
public:
	char IsTrade = ' ';
	Merchant(std::string n, int x, int y, std::vector<std::string> lines = {});
	

	virtual void NPCtalk();
	void trade();
};

