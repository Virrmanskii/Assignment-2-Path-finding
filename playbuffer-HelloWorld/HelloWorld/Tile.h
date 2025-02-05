#pragma once
#include "Play.h"
#include <vector>
#include <queue>
using namespace std;
enum TileType
{
	WALKABLE,
	NOT_WALKABLE,
	GOAL,
	START
};

struct Offset
{
	const int x = 10;
	const int y = 10;
};

//struct MinTileCondition
//{
//	bool operator()(const Tile* a, const Tile* b) const
//	{
//		return a->fCost > b->fCost; // Min-heap condition
//	}
//};

class Tile
{
public:
	TileType type;
	Play::Colour color = Play::cBlack;
	Tile* parent;
	vector<Tile*> neighbor;
	int posX;
	int posY;

	Tile();
	Tile(TileType type, Play::Colour color, int xPos, int yPos);
	~Tile();

	void setParent(Tile* parent);
};

