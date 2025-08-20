#pragma once
#include <string>
#include <vector> //added use of vector here as its more flexible/dynamic for adding row and column of map into a container

class Map
{
private:
	int mapMAX_ROW = 35;
	int mapMAX_COL = 28; 
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
		SPACE
	};

	void townMap(); 

	Map();
	~Map();
private:
	textType translateText(std::string string);
	std::vector<textType> TMap;
};

