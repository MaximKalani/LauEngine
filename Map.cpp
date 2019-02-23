#include "Map.hpp"
#include "engine.hpp"
#include <fstream>
#include "ECS/Components.hpp"
#include "ECS/ECS.hpp"

extern Manager manager;

Map::Map(const char* tilemap, const char* tileset, int sizeX, int sizeY, int sourceTileSize, int destinationTileSize)
{
    levelOneTilemap = tilemap;
    levelOneTileset = tileset;
    srcTileSize = sourceTileSize;
    destTileSize = destinationTileSize;
    LoadMap(levelOneTilemap, sizeX, sizeY);
}

Map::~Map()
{

}


void Map::LoadMap(const char* path, int sizeX, int sizeY)
{
    char tile;
    std::fstream mapFile;
    mapFile.open(path);
    
    int srcX, srcY;
    
    //tiles
    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.get(tile);

            srcY = atoi(&tile) * srcTileSize;
            mapFile.get(tile);

            srcX = atoi(&tile) * srcTileSize;
            AddTile(srcX, srcY, x * destTileSize, y * destTileSize);
            mapFile.ignore();
        }
        mapFile.ignore();

    }
    mapFile.ignore();
    
    //colliders
    for(int y = 0; y < sizeY; y++)
    {
        for(int x = 0; x < sizeX; x++)
        {
            mapFile.ignore();
            mapFile.get(tile);

            if(tile == '1')
            {
                AddCollider("terrain", x*destTileSize, y*destTileSize, destTileSize);

            }
            
        }
        mapFile.ignore();

    }
    mapFile.close();
}

void Map::AddTile(int srcX, int srcY, int xpos, int ypos)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos,ypos, levelOneTileset, srcTileSize, destTileSize);
    tile.addGroup(Game::groupMap);
}


void Map::AddCollider(std::string t, int x, int y, int destTileSize)
{
    auto& tCol(manager.addEntity());
    tCol.addComponent<ColliderComponent>(t);
    tCol.getComponent<ColliderComponent>().collider = {x, y, destTileSize, destTileSize};
    tCol.getComponent<ColliderComponent>().scale = destTileSize/16;
    tCol.addGroup(Game::groupColliders);
}


