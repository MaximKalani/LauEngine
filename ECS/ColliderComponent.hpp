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
   //SDL_Rect destR;
    TransformComponent* transform;
    int x, y, h, w, scale;
    ColliderComponent(std::string t)
    {
        tag = t;
        tex = TextureManager::LoadTexture("collider.png");
    }
    
    ColliderComponent(std::string t, int xpos, int ypos, int hs, int ws, int sc)
    {
        tag = t;
        tex = TextureManager::LoadTexture("collider.png");
        collider = {xpos, ypos, hs, ws};
        scale = sc;
    }
    
    void init() override
    {
        if(!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>((float)x, (float)y, h, w, scale);
        }
        transform = &entity->getComponent<TransformComponent>();
        
        //Game::colliders.push_back(this);
    }
    
    void update() override
    {
        if (tag != "terrain")
        {
            
        
            collider.x = static_cast<int>(transform->position.x);
            collider.y = static_cast<int>(transform->position.y);
            collider.w = transform->width * transform->scale;
            collider.h = transform->height * transform->scale;
            //destR = {collider.x, collider.y, collider.w, collider.h};
            
        }
        //destR = {collider.x, collider.y, collider.w, collider.h};
    }
    void draw() override
    {
        TextureManager::Draw(tex, srcR, collider, SDL_FLIP_NONE);
    }
};


#endif