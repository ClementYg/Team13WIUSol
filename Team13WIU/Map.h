#pragma once
#include <string>
#include <vector> //added use of vector here as its more flexible/dynamic for adding row and column of map into a container
#include <Windows.h>

class Map
{
private:
	char townGameMap[5][49];
public:
	enum textType {
		HYPHEN,
		STRAIGHT,
		EQUAL,
		HASH,
		UNDERSCORE,
		SLASH,
		BACKSLASH,
		ASTERISK,
		LETTERO,
		CARET,
		ATSIGN,
		MORETHAN,
		LESSTHAN,
		GRAVE,
		RIGHTCURLY,
		PERIOD,
		LEFTSQUAREB,
		RIGHTSQUAREB,
		UPGRAVE,
		SPACE
	};

	void townMap();
	void ForestMap();
	void HarbourMap();
	void EntranceCaveMap();
	void InnerCaveMap();
	void Inn();

	std::vector<std::vector<std::string>> ShipF1();

	void printCutscene(std::vector<std::string>& frames);
	void ShipCutscene();

	void clearScreen();

	Map();
	~Map();
private:
	textType translateText(std::string string);
	std::vector<textType> TMap;
};

