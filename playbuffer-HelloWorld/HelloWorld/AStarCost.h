#pragma once
#include "Tile.h"
#include "map"

//struct MinTileCostCondition 
//{
//	bool operator()(const map<Tile*, AStarCost>* a, const map<Tile*, AStarCost>* b) const
//	{
//		
//		return a->begin()->second.fCost > b->begin()->second.fCost; // Min-heap condition
//	}
//};

class AStarCost
{
public:
	int gCost = 0;
	int hCost = 0;
	int fCost = 0;

	AStarCost(): gCost(0), hCost(0), fCost(0) {};
	~AStarCost() {};

	int calculateHCost(Tile* start, Tile* target);
};

