#ifndef MAP_HPP_INCLUDED
#define MAP_HPP_INCLUDED

#include "engine.hpp"

class Map {

public:
    Map();
    ~Map();

    void LoadMap(int arr[20][25]);
    void DrawMap();


private:

    SDL_Rect src, dest;
    SDL_Texture* wall_mid; //wall_mid.png
    SDL_Texture* wall_right; //wall_right.png
    SDL_Texture* wall_left; //wall_left.png
    SDL_Texture* floor_1;
    int map[20][25];
};
#endif // MAP_HPP_INCLUDED
