#pragma once
#include <vector>
#include <queue>
#include <set>
#include <stack>
#include "Tile.h"

struct DFTile
{
	Tile* tile;
	bool viisited = false;
	DFTile(Tile* t) : tile(t) {};
};


class DeapthFirst
{
public:
	vector<DFTile> path;

	DeapthFirst();
	~DeapthFirst();

	vector<Tile*> findPath(Tile* start, Tile* goal);
	vector<Tile*> reconstructPath(Tile* start, Tile* target);
};

