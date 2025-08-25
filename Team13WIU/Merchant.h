#pragma once
#include "NPC.h"
class Merchant : public NPC
{
public:
	//char IsTrade = ' ';
	Merchant(std::string n, int y, int x, char s,std::vector<std::string> lines = {});
	~Merchant();
	

	void NPCtalk();
	void trade();
};

