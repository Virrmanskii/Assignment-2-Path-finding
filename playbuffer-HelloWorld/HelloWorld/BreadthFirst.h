#pragma once
#include <vector>
#include <queue>
#include "Tile.h"
using namespace std;

struct BreadthFirstTile
{
	Tile* tile;
	bool visited;
	BreadthFirstTile(Tile* t) : tile(t), visited(false) {};
};

class BreadthFirst
{
	BreadthFirst();
	~BreadthFirst();

	vector<Tile*> findPath(Tile* start, Tile* target); 
};
