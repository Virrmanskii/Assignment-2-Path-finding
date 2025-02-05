#include "TileWithCost.h"

TileWithCost::~TileWithCost()
{
	this->tile = nullptr;
	delete this->tile;
}
