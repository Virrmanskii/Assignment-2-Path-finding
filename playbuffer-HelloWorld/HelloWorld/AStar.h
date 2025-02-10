#pragma once
#include <queue>
#include <unordered_set>
#include <map>
#include <thread>
#include <mutex>
#include <atomic>
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
	std::mutex mtx;
	std::atomic<bool> pathFound = false;
	Tile* meetingTile = nullptr; 

	AStar() {};
	~AStar() {};

	//queue<Tile*> reconstructPath(Tile* from, Tile* current);
	vector<Tile*> findPath(Tile* start, Tile* target);
	void drawPath(vector<Tile*> path);
	void findPath2(Tile* start, Tile* target, bool forward, vector<Tile*>& path);
	vector<Tile*> findPathBidirectional(Tile* start, Tile* goal); 
	
	//queue<Tile*>

};

