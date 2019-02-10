#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include <string>


class Map {

public:
    Map(const char* tilemap, const char* tileset, int sizeX, int sizeY, int sourceTileSize, int destinationTileSize);
    ~Map();

    const char* levelOneTileset;
    const char* levelOneTilemap;
    
    int srcTileSize;
    int destTileSize;
        
    void LoadMap(const char* path, int sizeX, int sizeY);
    void AddTile(int srcX, int srcY,int xpos, int ypos);

private:

};
#endif // MAP_HPP_INCLUDED
