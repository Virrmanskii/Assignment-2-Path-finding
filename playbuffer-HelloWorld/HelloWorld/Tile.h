#pragma once
#include "Play.h"
enum TileType
{
	WALKABLE,
	NOT_WALKABLE
};

struct Offset
{
	const int x = 10;
	const int y = 10;
};

class Tile
{
public:
	TileType type;
	Play::Colour color = Play::cBlack;
	Tile* parent;
	int posX;
	int posY;

	Tile();
	Tile(TileType type, Play::Colour color, int xPos, int yPos);
	~Tile();

	void setParent(Tile* parent);
};

