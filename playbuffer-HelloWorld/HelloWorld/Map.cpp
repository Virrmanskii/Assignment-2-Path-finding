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
}

void Map::loadFromFile(const char* filePath)
{
	string line;
	ifstream mapFile(filePath);

	if (mapFile.is_open())
	{
		Offset offset;
		while (getline(mapFile, line)) 
		{
			vector<Tile*> row;
			for(const char tile : line)
			{
				if (tile == *"\n") { break;}
				
				//TODO create the actual map
				switch (tile)
				{
				case'X':
					row.push_back(new Tile(TileType::NOT_WALKABLE, Play::cBlack, this->sizeX + offset.x, this->sizeY + offset.y));
					break;
				case'0':
					break;
				case'S':
					break;
				case'G':
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
	}
	else
	{
		cerr << "Can't open file";
	}

}
