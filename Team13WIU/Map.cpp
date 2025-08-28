#include "Map.h"
#include <iostream>
#include <fstream>
#include <sstream> //stringstreams, allows strings to be used for reading/writing. similar to fstream for strings
#include <Windows.h>
#include <thread>
#include <chrono>

//------------------------------------------------
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
	else if (string == "9") { return Map::CARET; }
	else if (string == "10") { return Map::LETTERO; }
	else if (string == "11") { return Map::ATSIGN; }
	else if (string == "12") { return Map::MORETHAN; }
	else if (string == "13") { return Map::LESSTHAN; }
	else if (string == "14") { return Map::GRAVE; }
	else if (string == "15") { return Map::RIGHTCURLY; }
	else if (string == "16") { return Map::PERIOD; }
	else if (string == "17") { return Map::LEFTSQUAREB; }
	else if (string == "18") { return Map::RIGHTSQUAREB; }
	else if (string == "19") { return Map::UPGRAVE; }


	else return Map::SPACE;
}


void Map::townMap() {
	 
	std::fstream townMap; //creates fstream variable townMap
	townMap.open("townMap.csv", std::fstream::in); //uses townMap to open townMap.csv file and allow for output.
	if (!townMap.is_open()) { //if couldn't open map then dont print anything
		return;
	}

	std::string TMtiles = " "; // initialise

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
			case Map::CARET:
				std::cout << '^';
				break;
			case Map::LETTERO:
				std::cout << 'o';
				break;
			case Map::ATSIGN:
				std::cout << '@';
				break;
			case Map::MORETHAN:
				std::cout << '>';
				break;
			case Map::LESSTHAN:
				std::cout << '<';
				break;
			default:
				std::cout << "error";
			}
		}
		std::cout << std::endl;
	}





	townMap.close(); // closes file successfully

}

void Map::ForestMap() {
	std::fstream townMap; //creates fstream variable townMap
	townMap.open("ForestMap.csv", std::fstream::in); //uses townMap to open townMap.csv file and allow for output.
	if (!townMap.is_open()) { //if couldn't open map then dont print anything
		return;
	}

	std::string TMtiles = " "; // initialise

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
			case Map::CARET:
				std::cout << '^';
				break;
			case Map::LETTERO:
				std::cout << 'o';
				break;
			case Map::ATSIGN:
				std::cout << '@';
				break;
			case Map::MORETHAN:
				std::cout << '>';
				break;
			case Map::LESSTHAN:
				std::cout << '<';
				break;
			default:
				std::cout << "error";
			}
		}
		std::cout << std::endl;
	}
	townMap.close(); // closes file successfully
}

void Map::HarbourMap()
{
	std::fstream harbourMap; //creates fstream variable harbourMap
	harbourMap.open("Harbour.csv", std::fstream::in); //uses harbourMap to open harbourMap.csv file and allow for output.
	if (!harbourMap.is_open()) { //if couldn't open map then dont print anything
		return;
	}

	std::string TMtiles = " "; // initialise

	while (getline(harbourMap, TMtiles)) //while program can extract from harbourMap.csv and input into TMFiles. (TLDR: When there is still lines in .csv)
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
			case Map::CARET:
				std::cout << '^';
				break;
			case Map::LETTERO:
				std::cout << 'o';
				break;
			case Map::ATSIGN:
				std::cout << '@';
				break;
			case Map::MORETHAN:
				std::cout << '>';
				break;
			case Map::LESSTHAN:
				std::cout << '<';
				break;
			default:
				std::cout << "error";
			}
		}
		std::cout << std::endl;
	}
	harbourMap.close(); // closes file successfully
}

void Map::EntranceCaveMap()
{
	std::fstream EntranceCaveMap; //creates fstream variable EntranceCaveMap
	EntranceCaveMap.open("EntranceCave.csv", std::fstream::in); //uses EntranceCaveMap to open EntranceCaveMap.csv file and allow for output.
	if (!EntranceCaveMap.is_open()) { //if couldn't open map then dont print anything
		return;
	}

	std::string TMtiles = " "; // initialise

	while (getline(EntranceCaveMap, TMtiles)) //while program can extract from EntranceCaveMap.csv and input into TMFiles. (TLDR: When there is still lines in .csv)
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
			case Map::CARET:
				std::cout << '^';
				break;
			case Map::LETTERO:
				std::cout << 'o';
				break;
			case Map::ATSIGN:
				std::cout << '@';
				break;
			case Map::MORETHAN:
				std::cout << '>';
				break;
			case Map::LESSTHAN:
				std::cout << '<';
				break;
			default:
				std::cout << "error";
			}
		}
		std::cout << std::endl;
	}
	EntranceCaveMap.close(); // closes file successfully
}

void Map::InnerCaveMap()
{
	std::fstream InnerCaveMap; //creates fstream variable InnerCaveMap
	InnerCaveMap.open("InnerCave.csv", std::fstream::in); //uses InnerCaveMap to open InnerCaveMap.csv file and allow for output.
	if (!InnerCaveMap.is_open()) { //if couldn't open map then dont print anything
		return;
	}

	std::string TMtiles = " "; // initialise

	while (getline(InnerCaveMap, TMtiles)) //while program can extract from InnerCaveMap.csv and input into TMFiles. (TLDR: When there is still lines in .csv)
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
			case Map::CARET:
				std::cout << '^';
				break;
			case Map::LETTERO:
				std::cout << 'o';
				break;
			case Map::ATSIGN:
				std::cout << '@';
				break;
			case Map::MORETHAN:
				std::cout << '>';
				break;
			case Map::LESSTHAN:
				std::cout << '<';
				break;
			default:
				std::cout << "error";
			}
		}
		std::cout << std::endl;
	}
	InnerCaveMap.close(); // closes file successfully
}

void Map::Inn()
{
	std::fstream Inn; //creates fstream variable Inn
	Inn.open("Inn.csv", std::fstream::in); //uses Inn to open Inn.csv file and allow for output.
	if (!Inn.is_open()) { //if couldn't open map then dont print anything
		return;
	}

	std::string TMtiles = " "; // initialise

	while (getline(Inn, TMtiles)) //while program can extract from Inn.csv and input into TMFiles. (TLDR: When there is still lines in .csv)
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
			case Map::CARET:
				std::cout << '^';
				break;
			case Map::LETTERO:
				std::cout << 'o';
				break;
			case Map::ATSIGN:
				std::cout << '@';
				break;
			case Map::MORETHAN:
				std::cout << '>';
				break;
			case Map::LESSTHAN:
				std::cout << '<';
				break;
			default:
				std::cout << "error";
			}
		}
		std::cout << std::endl;
	}
	Inn.close(); // closes file successfully
}

std::vector<std::vector<std::string>> Map::ShipF1() {
	std::fstream ShipF1; //creates fstream variable ShipF1
	ShipF1.open("ShipFrame1.csv", std::fstream::in); //uses ShipF1 to open ShipF1.csv file and allow for output.
	std::vector<std::vector<std::string>> allFrames; //contains every keyframe 
	std::vector<std::string> currentFrame; //contain currentFrame out of allFrames by row.

	if (!ShipF1.is_open()) { //if couldn't open map then dont print anything
		return allFrames;
	}

	std::string TMtiles = " "; // initialise

	while (getline(ShipF1, TMtiles)) //while program can extract from ShipF1.csv and input into TMFiles. (TLDR: When there is still lines in .csv)
	{
		std::stringstream tiles(TMtiles); //creates a stringstream variable tiles, while passing in lines in TMtiles to tiles.
		std::string mapIndex;
		bool separateFrames = true;

		while (std::getline(tiles, mapIndex, ','))//gets the line from TILES, then places it in mapIndex string. Last parameter tells function to stop getting line at each comma, as this is a CSV file
		{
			Map::textType tile = translateText(mapIndex);
			if (mapIndex != "A") { // check when value received is 5. if 5, signals for frameSeparation
				separateFrames = false;
				break;
			}
		}
		
		if (separateFrames) {
			if (!currentFrame.empty()) //vector is not empty/null
			{
				allFrames.push_back(currentFrame); //push currentFrame into allFrames
				currentFrame.clear(); //clear currentFrame so that next one has space for next frame
			}
		}
		else //if never hit frame block
		{
			currentFrame.push_back(TMtiles); //if nvr hit separator, then pushback each row descending. (1st row, 2nd row etc)
		}
	}
	if (!currentFrame.empty()) allFrames.push_back(currentFrame); // push last frame inside when detect is last one.
	ShipF1.close(); // closes file successfully
	return allFrames;
}

void Map::printCutscene(std::vector<std::string>& frames) // pass in strings of each row 
{
	for (std::string& eachRow : frames) // initialise eachRow, taking from frames container 
	{
		std::stringstream tiles(eachRow); 
		std::string mapIndex;
		while (std::getline(tiles, mapIndex, ',')) //read every line(of numbers) in tiles (every row) and place in mapIndex to be translated here
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
			case Map::CARET:
				std::cout << '^';
				break;
			case Map::LETTERO:
				std::cout << 'o';
				break;
			case Map::ATSIGN:
				std::cout << '@';
				break;
			case Map::MORETHAN:
				std::cout << '>';
				break;
			case Map::LESSTHAN:
				std::cout << '<';
				break;
			case Map::GRAVE:
				std::cout << '~';
				break;
			case Map::LEFTSQUAREB:
				std::cout << '[';
				break;
			case Map::RIGHTSQUAREB:
				std::cout << ']';
				break;
			case Map::RIGHTCURLY:
				std::cout << '}';
				break;
			case Map::PERIOD:
				std::cout << '.';
				break;
			case Map::UPGRAVE:
				std::cout << '`';
				break;
			default:
				std::cout << "error";
			}
		}
		std::cout << std::endl; // 
	}
}

void Map::ShipCutscene()
{
	std::vector<std::vector<std::string>> ShipFrames = ShipF1();

	for (std::vector<std::string> individualFrame : ShipFrames) {
		clearScreen();
		printCutscene(individualFrame);
		std::this_thread::sleep_for(std::chrono::milliseconds(500)); // adjust speed
	}
	std::this_thread::sleep_for(std::chrono::milliseconds(500));
}

void Map::clearScreen()
{
	std::cout << "\033[H";
}



Map::Map() {
	//INITIALISATION
	for (int row = 0; row < 5; row++) {
		for (int col = 0; col < 49; col++) {
			townGameMap[row][col] = ' ';
		}
	}
}

Map::~Map()
{
}

