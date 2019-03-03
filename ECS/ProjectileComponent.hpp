#ifndef PROJECTILECOMPONENT_HPP_INCLUDED
#define PROJECTILECOMPONENT_HPP_INCLUDED

#include "ECS.hpp"
#include "Components.hpp"
#include "../TextureManager.hpp"
#include "../Vector2D.hpp"

class ProjectileComponent : public Component
{
public:
    SDL_Rect srcRect = { 0,0,16,16 };
    SDL_Rect destRect;
    SDL_Texture* tex;
    int speed;
    int dist;
    int track = 0;
    int scale;
    Vector2D direction;
    ProjectileComponent (int x, int y, int h, int w, int spd, int dis, int sc, const char* t, float dx, float dy)
    {
        destRect = { x, y, h*sc, w*sc };
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
        destRect.x += static_cast<int>( direction.x * speed ) - Game::camera.x;
        destRect.y += static_cast<int>( direction.y * speed ) - Game::camera.y;
    }
    void draw() override
    {
        TextureManager::Draw(tex, srcRect, destRect, SDL_FLIP_NONE);
    }
};

#endif