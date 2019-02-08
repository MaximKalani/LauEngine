#include "Map.hpp"
#include "engine.hpp"
#include <fstream>

Map::Map()
{

}

Map::~Map()
{

}


void Map::LoadMap(std::string path, int sizeX, int sizeY, int destTileSize)
{
    char tile;
    std::fstream mapFile;
    mapFile.open(path);
    
    int srcX, srcY;
    
    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile);
            srcY = atoi(&tile) * 16;
            mapFile.get(tile);
            srcX = atoi(&tile) * 16;
            Game::AddTile(srcX, srcY, x * destTileSize, y * destTileSize, destTileSize);
            mapFile.ignore();
        }
        mapFile.ignore();
    }
    
    mapFile.close();
}

