#pragma once
//#include "Play.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Tile.h"
//#include "AStarTile.h"
#include "Constants.h"
using namespace std;

class Map
{
public:
	vector<vector<Tile*>> map;
	Tile* start;
	Tile* target;
	int sizeX;
	int sizeY;
	int minPosX;
	int maxPosX;
	int minPosY;
	int maxPosY;

	Map();
	Map(const char* filePath);
	~Map();

	void loadFromFile(const char* filePath);
	void drawMap();
	void updateNeighbor();
};

