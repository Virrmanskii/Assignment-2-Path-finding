#include "AStar.h"


vector<Tile*> AStar::findPath(Tile* start, Tile* target)
{
	priority_queue<TileWithCost, vector<TileWithCost>, MinTileCostCondition> openMinHeap;
	unordered_set<Tile*> closedSet;

	AStarCost startCost;
	startCost.gCost = 0;
	startCost.hCost = startCost.calculateHCost(start, target);
	startCost.fCost = startCost.gCost + startCost.hCost;
	openMinHeap.push(TileWithCost(start, startCost));

	while (!openMinHeap.empty())
	{
		TileWithCost current = openMinHeap.top();
		openMinHeap.pop();

		Tile* currentTile = current.tile;

		if (currentTile == target)
		{
			vector<Tile*> path;
			while (currentTile != nullptr)
			{
				path.push_back(currentTile);
				currentTile = currentTile->parent;
			}

			reverse(path.begin(), path.end());
			return path;
		}

		closedSet.insert(currentTile);

		for (Tile* neighbor : currentTile->neighbor) {
			if (neighbor->type == NOT_WALKABLE || closedSet.find(neighbor) != closedSet.end())
			{
				continue; // Skip obstacles and already evaluated tiles
			}

			// Calculate movement cost
			int dx = abs(currentTile->posX - neighbor->posX);
			int dy = abs(currentTile->posY - neighbor->posY);
			int movementCost = (dx == 1 && dy == 1) ? 14 : 10; // Diagonal or straight

			//int tentativeGCost = current.cost.gCost + movementCost;
			int tentativeGCost = current.cost.gCost;

			bool isBetterPath = false;
			AStarCost neighborCost;


			if (neighbor->parent == nullptr || tentativeGCost < neighborCost.gCost)
			{
				isBetterPath = true;
			}

			if (isBetterPath)
			{
				neighborCost.gCost = tentativeGCost;
				neighborCost.hCost = neighborCost.calculateHCost(currentTile , target);
				neighborCost.fCost = neighborCost.gCost + neighborCost.hCost;
				neighbor->parent = currentTile;

				openMinHeap.push(TileWithCost(neighbor, neighborCost));
			}
		}

	}
	return {};
}

void AStar::drawPath(vector<Tile*> path)
{
	for (auto tile: path)
	{
		if (tile == path[0] || tile == path[path.size()-1])
		{
			continue;
		}
		tile->color = Play::cBlue;
	}
}
