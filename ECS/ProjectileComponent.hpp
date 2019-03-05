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
    bool hurtsPlayer;
    ProjectileComponent (int x, int y, int h, int w, int spd, int dis, int sc, const char* t, float dx, float dy)
    {
        printf("Constructor");
        position = { x, y, h*sc, w*sc };
        tex = TextureManager::LoadTexture(t);
        speed = spd;
        dist = dis;
        scale = sc;
        direction = { dx, dy };
    }
    
    ProjectileComponent(Vector2D pos, std::string projType, Vector2D dir, bool hurtsP)
    {
        position.x = pos.x;
        position.y = pos.y;
        direction = dir;
        hurtsPlayer = hurtsP;
        if(projType == "fireball")
        {
            tex = TextureManager::LoadTexture("assets/fireball.png");
            speed = 4;
            dist = 500;
            scale = 2;
        }
        else
        {
            tex = TextureManager::LoadTexture("assets/collider.png");
            speed = 1;
            dist = 100;
            scale = 1;
        }
        
        position.w = position.h = 16*scale;
    }
    ~ProjectileComponent(){}
    void update() override
    {
        track += speed;
        if( track > dist ) 
            entity->destroy();
        //if( !Collision::AABB(destRect, Game::camera))
            //entity->destroy();
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