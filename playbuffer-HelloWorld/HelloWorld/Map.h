#pragma once
//#include "Play.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>

#include "Tile.h"
using namespace std;

class Map
{
public:
	vector<vector<Tile*>> map;
	int sizeX;
	int sizeY;

	Map();
	Map(const char* filePath);
	~Map();

	void loadFromFile(const char* filePath);
};

