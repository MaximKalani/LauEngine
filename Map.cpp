#include "Map.hpp"
#include "engine.hpp"
#include <fstream>

Map::Map()
{

}

Map::~Map()
{

}


void Map::LoadMap(std::string path, int sizeX, int sizeY, int scale)
{
    char tile;
    std::fstream mapFile;
    mapFile.open(path);
    
    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile);
            Game::AddTile(atoi(&tile), x * scale, y * scale, scale);
            mapFile.ignore();
        }
        mapFile.ignore();
    }
    
    mapFile.close();
}

