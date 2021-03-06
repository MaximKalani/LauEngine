#ifndef COLLIDERCOMPONENT_HPP_INCLUDED
#define COLLIDERCOMPONENT_HPP_INCLUDED

#include <string>
#include <SDL2/SDL.h>
#include "Components.hpp"
#include "ECS.hpp"

#include "../TextureManager.hpp"


class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;
    SDL_Texture* tex;
    SDL_Rect srcR = {0,0,16,16};
    SDL_Rect destR;
    TransformComponent* transform = nullptr;
    ProjectileComponent* proj = nullptr;
    int x, y, h, w, scale;
    ColliderComponent(std::string t)
    {
        tag = t;
        tex = TextureManager::LoadTexture("assets/collider.png");
    }
    
    ColliderComponent(std::string t, int xpos, int ypos, int hs, int ws, int sc)
    {
        tag = t;
        tex = TextureManager::LoadTexture("assets/collider.png");
        collider = {xpos, ypos, hs, ws};
        scale = sc;
    }
    
    void init() override
    {
        if ( tag != "projectile")
        {
            if(!entity->hasComponent<TransformComponent>())
            {
                    entity->addComponent<TransformComponent>((float)x, (float)y, h, w, scale);
            }
            transform = &entity->getComponent<TransformComponent>();
        }
        else
            if(entity->hasComponent<ProjectileComponent>())
                proj = &entity->getComponent<ProjectileComponent>();
    }
    
    void update() override
    {
        if (tag == "player" || tag == "enemy")
        {
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
        }
        if(tag == "projectile")
        {
            destR.x = proj->destRect.x;  
            destR.y = proj->destRect.y;  
            destR.h = proj->destRect.h;  
            destR.w = proj->destRect.w;  
        }
        else
        {
            destR.x = collider.x - Game::camera.x;
            destR.y = collider.y - Game::camera.y;
            destR.w = collider.w;
            destR.h = collider.h;
        }
    }
    void draw() override
    {
        if(Game::drawColliders)
            TextureManager::Draw(tex, srcR, destR, SDL_FLIP_NONE);
    }
};


#endif