#ifndef TILECOMPONENT_HPP_INCLUDED
#define TILECOMPONENT_HPP_INCLUDED

#include "ECS.hpp"
#include <SDL2/SDL.h>
#include "../Vector2D.hpp"
#include "../engine.hpp"
#include "../TextureManager.hpp"

class TileComponent : public Component
{
public:
    
    SDL_Texture* texture;
    SDL_Rect srcRect, destRect;
    Vector2D position;
    
    TileComponent() = default;
    
    ~TileComponent()
    {
        SDL_DestroyTexture(texture);
    }
    
    TileComponent(int srcX, int srcY, int xpos, int ypos, const char* path, int srcTileSize, int destTileSize)
    {
        texture = TextureManager::LoadTexture(path);
        
        srcRect.x = srcX;
        srcRect.y = srcY;
        
        srcRect.w = srcRect.h = srcTileSize;
        
        position.x = static_cast<float>(xpos);
        position.y = static_cast<float>(ypos);
        destRect.w = destRect.h = destTileSize;
        
    }
    
    void update() override
    {

            destRect.x = static_cast<int>(position.x - Game::camera.x);
            destRect.y = static_cast<int>(position.y - Game::camera.y);
        
        
    }
    
    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect, SDL_FLIP_NONE);
    }
};
#endif