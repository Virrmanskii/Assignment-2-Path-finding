#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"
//#include "Constants.h"
#include "Map.h"
#include "AStar.h"
#include <chrono>
#include <string>



Map map1("maps/Map3.txt");
AStar aStar;
long long dur;

// The entry point for a PlayBuffer program
void MainGameEntry( PLAY_IGNORE_COMMAND_LINE )
{
	Play::CreateManager( DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE );
	map1.updateNeighbor();
	using namespace std::chrono;
	auto start = high_resolution_clock::now();
	vector<Tile*> path = aStar.findPath(map1.start, map1.target);
	auto stop = high_resolution_clock::now();
	auto duration = duration_cast<microseconds>(stop - start);
	dur = duration.count();
	
	aStar.drawPath(path);
	
}

// Called by PlayBuffer every frame (60 times a second!)
bool MainGameUpdate( float elapsedTime )
{
	Play::ClearDrawingBuffer( Play::cOrange );
	//----------------------------------------
	//Play::DrawDebugText( { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, "Uno, Dos, Tres, Shuuuurdaaa!!!" );
	map1.drawMap();
	Play::DrawDebugText({ DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 }, std::to_string(dur).c_str());
	//----------------------------------------
	Play::PresentDrawingBuffer();
	return Play::KeyDown( KEY_ESCAPE );
}

// Gets called once when the player quits the game 
int MainGameExit( void )
{
	Play::DestroyManager();
	return PLAY_OK;
}

