#pragma once
#include <vector>
#include <queue>
#include <set>
#include "Tile.h"
using namespace std;

struct BreadthFirstTile;

struct BreadthFirstTile
{
	Tile* tile;
	bool visited;
	vector<BreadthFirstTile> neighbors;
	BreadthFirstTile(Tile* t) : tile(t), visited(false) {
		//for (auto n : tile->neighbor)
		//{
		//	neighbors.push_back(BreadthFirstTile(n));
		//}
	};
};

class BreadthFirst
{
public:
	BreadthFirst();
	~BreadthFirst();

	vector<Tile*> findPath(Tile* start, Tile* target);
	vector<Tile*> reconstructPath(Tile* start, Tile* target);
	void drawPath(vector<Tile*> path);
};

struct BreadthFirstTileCondition
{
	bool operator()(const BreadthFirstTile& a, const BreadthFirstTile& b) const
	{
		return a.tile > b.tile;
	}
};