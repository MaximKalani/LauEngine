#ifndef TILECOMPONENT_HPP_INCLUDED
#define TILECOMPONENT_HPP_INCLUDED

#include "ECS.hpp"
#include <SDL2/SDL.h>
#include "../TextureManager.hpp"

class TileComponent : public Component
{
public:
    
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    
    TileComponent() = default;
    
    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }
    
    TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path, int destTileSize)
    {
        texture = TextureManager::LoadTexture(path);
        
        srcRect.x = srcX;
        srcRect.y = srcY;
        
        srcRect.w = srcRect.h = 16;
        
        destRect.x = xpos;
        destRect.y = ypos;
        destRect.w = destRect.h = destTileSize;
        
    }
    
    void draw()
    {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};
#endif