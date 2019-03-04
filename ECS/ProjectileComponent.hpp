#ifndef PROJECTILECOMPONENT_HPP_INCLUDED
#define PROJECTILECOMPONENT_HPP_INCLUDED

#include "ECS.hpp"
#include "Components.hpp"
#include "../TextureManager.hpp"
#include "../Vector2D.hpp"
#include "../Collision.hpp"

class ProjectileComponent : public Component
{
public:
    SDL_Rect srcRect = { 0,0,16,16 };
    SDL_Rect destRect, position;
    SDL_Texture* tex;
    int speed;
    int dist;
    int track = 0;
    int scale;
    Vector2D direction;
    ProjectileComponent (int x, int y, int h, int w, int spd, int dis, int sc, const char* t, float dx, float dy)
    {
        position = { x, y, h*sc, w*sc };
        tex = TextureManager::LoadTexture(t);
        speed = spd;
        dist = dis;
        scale = sc;
        direction = { dx, dy };
    }
    ~ProjectileComponent(){}
    void update() override
    {
        track += speed;
        if( track > dist ) 
            entity->destroy();
        if( !Collision::AABB(destRect, Game::camera))
            entity->destroy();
        position.x += static_cast<int>( direction.x * speed);
        position.y += static_cast<int>( direction.y * speed);
        
        destRect.x = position.x - Game::camera.x;
        destRect.y = position.y - Game::camera.y;
        destRect.w = position.w;
        destRect.h = position.h;
        
        
    }
    void draw() override
    {
        TextureManager::Draw(tex, srcRect, destRect, SDL_FLIP_NONE);
    }
};

#endif