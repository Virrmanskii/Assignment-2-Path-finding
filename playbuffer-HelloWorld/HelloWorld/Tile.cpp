#include "Tile.h"

Tile::Tile()
{
	this->type = TileType::NOT_WALKABLE;
	this->parent = nullptr;
	this->posX = 0;
	this->posY = 0;
}

Tile::Tile(TileType type, Play::Colour color, int xPos, int yPos)
{
	this->type = type;
	this->color = color;
	this->parent = nullptr;
	this->posX = xPos;
	this->posY = yPos;
}

Tile::~Tile()
{
}

void Tile::setParent(Tile* parent)
{
	this->parent = parent;
}
