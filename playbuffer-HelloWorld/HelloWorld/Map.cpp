#include "Map.h"

Map::Map()
{
	this->sizeX = 0;
	this->sizeY = 0;
}

Map::Map(const char* filePath)
{
	this->sizeX = 0;
	this->sizeY = 0;
	loadFromFile(filePath);
}

Map::~Map()
{
	for (auto row : this->map)
	{
		for (auto col : row)
		{
			delete col;
		}
	}
}

void Map::loadFromFile(const char* filePath)
{
	int makeTileVisable = 10;
	string line;
	ifstream mapFile(filePath);

	if (mapFile.is_open())
	{
		Offset offset;
		while (getline(mapFile, line)) 
		{
			this->sizeX = 0;
			vector<Tile*> row;
			for(const char tile : line)
			{
				if (tile == *"\n") { break;}
				
				//TODO create the actual map
				switch (tile)
				{
				case'X':
					row.push_back(new Tile(TileType::NOT_WALKABLE, Play::cBlack, this->sizeX * offset.x, (DISPLAY_HEIGHT - makeTileVisable) - this->sizeY * offset.y));
					break;
				case'0':
					row.push_back(new Tile(TileType::WALKABLE, Play::cWhite, this->sizeX * offset.x, (DISPLAY_HEIGHT - makeTileVisable) - this->sizeY * offset.y));
					break;
				case'S':
					row.push_back(new Tile(TileType::START, Play::cGreen, this->sizeX * offset.x, (DISPLAY_HEIGHT - makeTileVisable) - this->sizeY * offset.y));
					this->start = row.at(row.size()-1);
					break;
				case'G':
					row.push_back(new Tile(TileType::GOAL, Play::cRed, this->sizeX * offset.x, (DISPLAY_HEIGHT - makeTileVisable) - this->sizeY * offset.y));
					this->target = row.at(row.size() - 1);
					break;
				default:
					break;
				}
				this->sizeX += 1;
			}
			this->sizeY += 1;
			this->map.push_back(row);
		}

		mapFile.close();
		this->minPosX = this->map[0][0]->posX;
		this->maxPosY = this->map[0][0]->posY;

		this->minPosY = this->map[this->sizeY-1][0]->posY;
		this->maxPosX = this->map[0][this->sizeX-1]->posX;   
	}
	else
	{
		cerr << "Can't open file";
	}

}

void Map::drawMap()
{
	Offset offset;
	for (auto row : this->map)
	{
		for (auto col : row)
		{
			Play::DrawRect(Play::Point2D(col->posX, col->posY), Play::Point2D(col->posX + offset.x, col->posY + offset.y), col->color, true);
		}
	}
}

void Map::updateNeighbor()
{

	for (int row = 0; row < this->map.size(); row++)
	{
		for (int col = 0; col < this->map[row].size(); col++)
		{
			if (this->map[row][col]->type == TileType::NOT_WALKABLE)
			{
				continue;
			}
			//if the tile is not a edge tile, it will have 8 neighbors
			if (this->map[row][col]->posX > this->minPosX && 
				this->map[row][col]->posX < this->maxPosX && 
				this->map[row][col]->posY > this->minPosY && 
				this->map[row][col]->posY < this->maxPosY)
			{
				this->map[row][col]->neighbor.push_back(this->map[row - 1][col]); //up
				this->map[row][col]->neighbor.push_back(this->map[row + 1][col]);// down
				this->map[row][col]->neighbor.push_back(this->map[row][col - 1]);//left
				this->map[row][col]->neighbor.push_back(this->map[row][col + 1]);//right

				if (this->map[row-1][col]->type != TileType::NOT_WALKABLE && this->map[row][col + 1]->type != TileType::NOT_WALKABLE)
				{

					this->map[row][col]->neighbor.push_back(this->map[row - 1][col + 1]); //up, right
				}
				if (this->map[row][col + 1]->type != TileType::NOT_WALKABLE && this->map[row +1 ][col]->type != TileType::NOT_WALKABLE)
				{
					this->map[row][col]->neighbor.push_back(this->map[row + 1][col + 1]);//down, right
				}
				if (this->map[row + 1][col]->type != TileType::NOT_WALKABLE && this->map[row][col - 1]->type != TileType::NOT_WALKABLE)
				{
					this->map[row][col]->neighbor.push_back(this->map[row + 1][col - 1]); //down, left 
				}
				if (this->map[row][col - 1]->type != TileType::NOT_WALKABLE && this->map[row -1][col]->type != TileType::NOT_WALKABLE)
				{
					this->map[row][col]->neighbor.push_back(this->map[row - 1][col - 1]);// up, left
				}
				//this->map[row][col]->neighbor.push_back(this->map[row-1][col-1]);// up, left
				//this->map[row][col]->neighbor.push_back(this->map[row-1][col]); //up
				//this->map[row][col]->neighbor.push_back(this->map[row-1][col+1]); //up, right
				//this->map[row][col]->neighbor.push_back(this->map[row][col-1]);//left
				//this->map[row][col]->neighbor.push_back(this->map[row][col+1]);//right
				//this->map[row][col]->neighbor.push_back(this->map[row+1][col-1]); //down, left 
				//this->map[row][col]->neighbor.push_back(this->map[row+1][col]);// down
				//this->map[row][col]->neighbor.push_back(this->map[row+1][col+1]);//down, right
				continue;
			}
			//else if (this->map[row][col]->posX == this->minPosX)// Leftest edge
			//{
			//	if (this->map[row][col]->posY == this->minPosY)
			//	{
			//		this->map[row][col]->neighbor.push_back(this->map[row][col + 1]);//right
			//		this->map[row][col]->neighbor.push_back(this->map[row-1][col]);//up
			//		//this->map[row][col]->neighbor.push_back(this->map[row-1][col + 1]);//up, right
			//		continue;
			//	}
			//	else if(this->map[row][col]->posY == this->maxPosY)
			//	{
			//		this->map[row][col]->neighbor.push_back(this->map[row][col + 1]);//right
			//		this->map[row][col]->neighbor.push_back(this->map[row + 1][col]);//down
			//		//this->map[row][col]->neighbor.push_back(this->map[row+1][col + 1]);//down, right
			//		continue;
			//	}
			//	else
			//	{
			//		this->map[row][col]->neighbor.push_back(this->map[row-1][col]);//up
			//		//this->map[row][col]->neighbor.push_back(this->map[row-1][col + 1]);//up, right
			//		this->map[row][col]->neighbor.push_back(this->map[row][col + 1]);//right
			//		//this->map[row][col]->neighbor.push_back(this->map[row+1][col + 1]);//down, right
			//		this->map[row][col]->neighbor.push_back(this->map[row+1][col]);//down
			//		continue;
			//	}
			//}
			//else if (this->map[row][col]->posX == this->maxPosX)// Rightest edge
			//{
			//	if (this->map[row][col]->posY == this->minPosY)//
			//	{
			//		this->map[row][col]->neighbor.push_back(this->map[row][col - 1]);//left
			//		this->map[row][col]->neighbor.push_back(this->map[row-1][col]);//up
			//		//this->map[row][col]->neighbor.push_back(this->map[row-1][col - 1]);//up, left
			//		continue;
			//	}
			//	else if (this->map[row][col]->posY == this->maxPosY)
			//	{
			//		this->map[row][col]->neighbor.push_back(this->map[row][col-1]);//left
			//		this->map[row][col]->neighbor.push_back(this->map[row+1][col]);//down
			//		//this->map[row][col]->neighbor.push_back(this->map[row+1][col-1]);//down, left
			//		continue;
			//	}
			//	else
			//	{
			//		this->map[row][col]->neighbor.push_back(this->map[row-1][col]);//up
			//		//this->map[row][col]->neighbor.push_back(this->map[row-1][col-1]);//up, left
			//		this->map[row][col]->neighbor.push_back(this->map[row][col-1]);//left
			//		//this->map[row][col]->neighbor.push_back(this->map[row+1][col-1]);//down, left
			//		this->map[row][col]->neighbor.push_back(this->map[row+1][col]);//down
			//		continue;
			//	}
			//}
			//else if (this->map[row][col]->posY == this->maxPosY)// Top egde, except double edges
			//{
			//	this->map[row][col]->neighbor.push_back(this->map[row][col-1]);//left
			//	//this->map[row][col]->neighbor.push_back(this->map[row+1][col-1]);//down, left
			//	this->map[row][col]->neighbor.push_back(this->map[row+11][col]);//down
			//	//this->map[row][col]->neighbor.push_back(this->map[row+1][col+1]);//down, right
			//	this->map[row][col]->neighbor.push_back(this->map[row][col+1]);//right
			//	continue;
			//}
			//else if(this->map[row][col]->posY == this->minPosY)// bottom egde, except double edges
			//{
			//	this->map[row][col]->neighbor.push_back(this->map[row][col-1]);//left
			//	//this->map[row][col]->neighbor.push_back(this->map[row-1][col-1]);//up, left
			//	this->map[row][col]->neighbor.push_back(this->map[row-1][col]);//up
			//	//this->map[row][col]->neighbor.push_back(this->map[row-1][col+1]);//up, right
			//	this->map[row][col]->neighbor.push_back(this->map[row][col+1]);//right
			//	continue;
			//}
		}
	}
}
