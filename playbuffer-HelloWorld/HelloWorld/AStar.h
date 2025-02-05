#pragma once
#include <queue>
#include <unordered_set>
#include <map>
//#include "Tile.h"
//#include "AStarCost.h"
#include "TileWithCost.h"
#include "Play.h"
using namespace std;


class AStar
{
private:
	//Tile* find(priority_queue<TileWithCost*, vector<TileWithCost>, MinTileCostCondition>& openSet, Tile* tile);

public:
	AStar() {};
	~AStar() {};

	//queue<Tile*> reconstructPath(Tile* from, Tile* current);
	vector<Tile*> findPath(Tile* start, Tile* target);
	void drawPath(vector<Tile*> path);
	//queue<Tile*>

};

