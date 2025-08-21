#pragma once
#include <string>
#include <vector> //added use of vector here as its more flexible/dynamic for adding row and column of map into a container

class Map
{
private:
	int mapMAX_ROW = 35;
	int mapMAX_COL = 28; 
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
		SPACE
	};

	void townMap(); 

	void printTMap();

	void townGameArea(); 

	Map();
	~Map();
private:
	textType translateText(std::string string);
	std::vector<textType> TMap;
};

