#pragma once
#include <string>
#include <vector> //added use of vector here as its more flexible/dynamic for adding row and column of map into a container

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
		SPACE
	};

	void townMap();
	void ForestMap();


	void printTMap();

	void printFMap();

	void townGameArea(); 

	Map();
	~Map();
private:
	textType translateText(std::string string);
	std::vector<textType> TMap;
};

