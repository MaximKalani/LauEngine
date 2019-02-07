#include "Map.hpp"
#include "TextureManager.hpp"


int lvl1[20][25] = {
    {   1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2   },
    {   0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,0   },
    {   1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2   },
    {   0,1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2   },
    {   1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2   },
    {   1,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   },
    {   0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0   }
};

Map::Map()
{
    wall_mid = TextureManager::LoadTexture("assets/sprites/wall_mid.png");
    wall_left = TextureManager::LoadTexture("assets/sprites/wall_left.png");
    wall_right = TextureManager::LoadTexture("assets/sprites/wall_right.png");
    floor_1 = TextureManager::LoadTexture("assets/sprites/floor_1.png");

    LoadMap(lvl1);

    src.x = src.y = 0;
    dest.h= dest.w = 32;
    src.h = src.w  = 16;

    dest.x = dest.y = 0;
}

Map::~Map()
{
    SDL_DestroyTexture(wall_left);
    SDL_DestroyTexture(wall_right);
    SDL_DestroyTexture(wall_mid);
    SDL_DestroyTexture(floor_1);
}


void Map::LoadMap(int arr[20][25])
{
    for(int row = 0; row < 20; row++)
    {
        for(int column = 0; column < 25; column++)
        {
            map[row][column] = arr[row][column];
        }
    }
}

void Map::DrawMap()
{
    int type = 0;
    for(int row = 0; row < 20; row++)
    {
        for(int column = 0; column < 25; column++)
        {
            type = map[row][column];

            dest.x = column * 32;
            dest.y = row * 32;

            switch(type)
            {
                case 0:
                    TextureManager::Draw(floor_1, src, dest);
                    break;
                case 1:
                    TextureManager::Draw(wall_left, src, dest);
                    break;
                case 2:
                    TextureManager::Draw(wall_right, src, dest);
                    break;
                case 3:
                    TextureManager::Draw(wall_mid, src, dest);
                    break;
                default:
                    break;
            }

        }
    }

}

