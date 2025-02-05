#pragma once
#include "Tile.h"
#include "AStarCost.h"

class TileWithCost
{
public:
    Tile* tile;
    AStarCost cost;

	TileWithCost(Tile* t, AStarCost c) : tile(t), cost(c) {};
	~TileWithCost();
};

struct MinTileCostCondition
{
	bool operator()(const TileWithCost& a, const TileWithCost& b) const
	{

		return a.cost.fCost > b.cost.fCost; // Min-heap condition
	}
};

