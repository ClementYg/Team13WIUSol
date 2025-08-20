#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream> //stringstreams, allows strings to be used for reading/writing. similar to fstream for strings
//------------------------------------------------
//                                                
//
//                      _
//                     / \
//                    /|-|\
//  ____________     /_|_|_\
// |            |   /| | | |\
// |            |  /_|#####|_\               __
// |       _    | /| |#####| |\   ==         ||
// |______/ \___|/_|_|_|_|_|_|_\==||=========||=
//  |_|  /   \  |==============|[___]_[_]_[][_]|
//    | /     \ |--------------|[__][_][]_[__]_|
//____|/       \| /-----\|----||***************|___
//oooo| __      | |     ||    ||^----^^--^--^--|ooo
//oooo|| o| []  | |     ||    ||               |ooo
//oooo||  |     | |     ||    ||               |ooo
//=================================================
//
//
//
//
//
//
//------------------------------------------------

Map::textType Map::translateText(std::string string) { //return enum textType. Translates string to enum Type
	if (string == "1") { return Map::HYPHEN; } // DOUBLE QUOTATIONS USED AS STRING VARIABLE CNT USE ''.
	else if (string == "2") { return Map::STRAIGHT; }
	else if (string == "3") { return Map::HASH; }

	else if (string == "4") { return Map::UNDERSCORE; }


	else if (string == "5") { return Map::EQUAL; }
	else if (string == "6") { return Map::SLASH; }
	else if (string == "7") { return Map::BACKSLASH; }
	else if (string == "8") { return Map::ASTERISK; }




	else return Map::SPACE;
}


void Map::townMap() {
	std::fstream townMap; //creates fstream variable townMap
	townMap.open("townMap.csv", std::fstream::in); //uses townMap to open townMap.csv file and allow for output.
	if (townMap.is_open()) {

		std::string TMtiles = " ";

		while (getline(townMap, TMtiles)) //while program can extract from townMap.csv and input into TMFiles. (TLDR: When there is still lines in .csv)
		{
			std::stringstream tiles(TMtiles); //creates a stringstream variable tiles, while passing in lines in TMtiles to tiles.
			std::string mapIndex;

			while (std::getline(tiles, mapIndex, ','))//gets the line from TILES, then places it in mapIndex string. Last parameter tells function to stop getting line at each comma, as this is a CSV file
			{
				Map::textType tile = translateText(mapIndex);
				switch (tile) {
				case Map::HYPHEN:
					std::cout << '-';
					break;
				case Map::STRAIGHT:
					std::cout << '|';
					break;
				case Map::HASH:
					std::cout << '#';
					break;
				case Map::UNDERSCORE:
					std::cout << '_';
					break;
				case Map::EQUAL:
					std::cout << '=';
					break;
				case Map::SLASH:
					std::cout << '/';
					break;
				case Map::BACKSLASH:
					std::cout << "\\";
					break;
				case Map::ASTERISK:
					std::cout << '*';
					break;
				case Map::SPACE:
					std::cout << ' ';
					break;
				}
			}
			std::cout << std::endl;
		}

	}



	townMap.close(); // closes file successfully

}

Map::Map() {

}

Map::~Map()
{
}

