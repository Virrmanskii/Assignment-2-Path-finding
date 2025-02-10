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
			if (neighbor->type == NOT_WALKABLE || closedSet.find(neighbor) != closedSet.end())//if (neighbor->type == NOT_WALKABLE || closedSet.find(neighbor) != closedSet.end())
			{
				continue;
			}

			// Calculate movement cost
			int dx = abs(currentTile->posX - neighbor->posX);
			int dy = abs(currentTile->posY - neighbor->posY);
			int movementCost = (dx == 10 && dy == 10) ? 14 : 10; // Diagonal or straight

			//int tentativeGCost = current.cost.gCost + movementCost;
			AStarCost neighborCost;
			//int tentativeGCost = current.cost.gCost + neighborCost.calculateHCost(currentTile, neighbor);
			int tentativeGCost = current.cost.gCost + movementCost;

			bool isBetterPath = false;
			//AStarCost neighborCost;


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


//--------------------------------------------------------------------------------------------------------

//void AStar::findPath2(Tile* start, Tile* target, bool forward, vector<Tile*>& path) {
//	priority_queue<TileWithCost, vector<TileWithCost>, MinTileCostCondition> openMinHeap;
//	unordered_set<Tile*> closedSet;
//
//	AStarCost startCost;
//	startCost.gCost = 0;
//	startCost.hCost = startCost.calculateHCost(start, target);
//	startCost.fCost = startCost.gCost + startCost.hCost;
//	openMinHeap.push(TileWithCost(start, startCost));
//
//	while (!openMinHeap.empty() && !pathFound) {
//		TileWithCost current = openMinHeap.top();
//		openMinHeap.pop();
//
//		Tile* currentTile = current.tile;
//
//		// Check if the other search has reached this tile
//		std::lock_guard<std::mutex> lock(mtx);
//		if (closedSet.find(currentTile) != closedSet.end()) {
//			meetingTile = currentTile;
//			pathFound = true;
//			return;
//		}
//	
//
//		closedSet.insert(currentTile);
//
//		for (Tile* neighbor : currentTile->neighbor) {
//			if (neighbor->type == NOT_WALKABLE || closedSet.find(neighbor) != closedSet.end()) {
//				continue;
//			}
//
//			// Calculate movement cost
//			int dx = abs(currentTile->posX - neighbor->posX);
//			int dy = abs(currentTile->posY - neighbor->posY);
//			int movementCost = (dx == 10 && dy == 10) ? 14 : 10;
//
//			AStarCost neighborCost;
//			int tentativeGCost = current.cost.gCost + movementCost;
//
//			if (neighbor->parent == nullptr || tentativeGCost < neighborCost.gCost) {
//				neighborCost.gCost = tentativeGCost;
//				neighborCost.hCost = neighborCost.calculateHCost(neighbor, target);
//				neighborCost.fCost = neighborCost.gCost + neighborCost.hCost;
//				neighbor->parent = currentTile;
//				openMinHeap.push(TileWithCost(neighbor, neighborCost));
//			}
//		}
//	}
//}
//
//vector<Tile*> AStar::findPathBidirectional(Tile* start, Tile* goal) {
//	vector<Tile*> pathStart, pathGoal;
//
//	// Launch threads for both directions
//	thread threadStart(&AStar::findPath2, this, start, goal, true, std::ref(pathStart));
//	thread threadGoal(&AStar::findPath2, this, goal, start, false, std::ref(pathGoal));
//
//	threadStart.join();
//	threadGoal.join();
//
//	vector<Tile*> finalPath;
//	if (meetingTile) {
//		// Merge the two paths
//		vector<Tile*> reversePath(pathGoal.rbegin(), pathGoal.rend()); // Reverse goal-to-start path
//		finalPath.insert(finalPath.end(), pathStart.begin(), pathStart.end());
//		finalPath.insert(finalPath.end(), reversePath.begin(), reversePath.end());
//	}
//
//	return finalPath;
//}

vector<Tile*> AStar::findPathBidirectional(Tile* start, Tile* goal) {
    priority_queue<TileWithCost, vector<TileWithCost>, MinTileCostCondition> openMinHeapStart;
    priority_queue<TileWithCost, vector<TileWithCost>, MinTileCostCondition> openMinHeapGoal;

    unordered_map<Tile*, Tile*> cameFromStart, cameFromGoal;
    unordered_set<Tile*> visitedStart, visitedGoal;

    AStarCost startCost, goalCost;
    startCost.gCost = goalCost.gCost = 0;
    startCost.hCost = startCost.calculateHCost(start, goal);
    goalCost.hCost = goalCost.calculateHCost(goal, start);
    startCost.fCost = startCost.gCost + startCost.hCost;
    goalCost.fCost = goalCost.gCost + goalCost.hCost;

    openMinHeapStart.push(TileWithCost(start, startCost));
    openMinHeapGoal.push(TileWithCost(goal, goalCost));

    visitedStart.insert(start);
    visitedGoal.insert(goal);

    Tile* meetingTile = nullptr;

    while (!openMinHeapStart.empty() && !openMinHeapGoal.empty()) {
        // Expand from Start
        if (!openMinHeapStart.empty()) {
            TileWithCost current = openMinHeapStart.top();
            openMinHeapStart.pop();

            if (visitedGoal.find(current.tile) != visitedGoal.end()) {
                meetingTile = current.tile;
                break;
            }

            for (Tile* neighbor : current.tile->neighbor) {
                if (neighbor->type == NOT_WALKABLE || visitedStart.find(neighbor) != visitedStart.end())
                    continue;

                int movementCost = (abs(current.tile->posX - neighbor->posX) == 10 &&
                    abs(current.tile->posY - neighbor->posY) == 10)
                    ? 14
                    : 10;

                AStarCost neighborCost;
                neighborCost.gCost = current.cost.gCost + movementCost;
                neighborCost.hCost = neighborCost.calculateHCost(neighbor, goal);
                neighborCost.fCost = neighborCost.gCost + neighborCost.hCost;

                cameFromStart[neighbor] = current.tile;
                visitedStart.insert(neighbor);
                openMinHeapStart.push(TileWithCost(neighbor, neighborCost));
            }
        }

        // Expand from Goal
        if (!openMinHeapGoal.empty()) {
            TileWithCost current = openMinHeapGoal.top();
            openMinHeapGoal.pop();

            if (visitedStart.find(current.tile) != visitedStart.end()) {
                meetingTile = current.tile;
                break;
            }

            for (Tile* neighbor : current.tile->neighbor) {
                if (neighbor->type == NOT_WALKABLE || visitedGoal.find(neighbor) != visitedGoal.end())
                    continue;

                int movementCost = (abs(current.tile->posX - neighbor->posX) == 10 && abs(current.tile->posY - neighbor->posY) == 10)? 14 : 10;

                AStarCost neighborCost;
                neighborCost.gCost = current.cost.gCost + movementCost;
                neighborCost.hCost = neighborCost.calculateHCost(neighbor, start);
                neighborCost.fCost = neighborCost.gCost + neighborCost.hCost;

                cameFromGoal[neighbor] = current.tile;
                visitedGoal.insert(neighbor);
                openMinHeapGoal.push(TileWithCost(neighbor, neighborCost));
            }
        }
    }

    if (!meetingTile)
        return {}; // No path found

    // **Reconstruct the final path**
    vector<Tile*> path;

    // Reconstruct path from Start -> MeetingTile
    Tile* current = meetingTile;
    while (current) {
        path.push_back(current);
        current = cameFromStart[current];
    }
    reverse(path.begin(), path.end());

    // Reconstruct path from MeetingTile -> Goal
    current = cameFromGoal[meetingTile];
    while (current) {
        path.push_back(current);
        current = cameFromGoal[current];
    }

    return path;
}
