#ifndef TILECOMPONENT_HPP_INCLUDED
#define TILECOMPONENT_HPP_INCLUDED

#include "ECS.hpp"

#include <SDL2/SDL.h>

class TileComponent : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    
    SDL_Rect tileRect;
    int tileID;
    const char* path;
    
    TileComponent() = default;
    
    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;
        
        switch (tileID)
        {
            case 0:
                path = "assets/sprites/floor_1.png";
                break;  
            case 1:
                path = "assets/sprites/wall_left.png";
                break;
            case 2:
                path = "assets/sprites/wall_right.png";
                break;
            case 3:
                path = "assets/sprites/wall_mid.png";
                break;
            default:
                break;
        }
    }
        
        void init() override
        {
            entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
            transform = &entity->getComponent<TransformComponent>();
            
            entity->addComponent<SpriteComponent>(path);
            sprite = &entity->getComponent<SpriteComponent>();
        }
    
};
#endif