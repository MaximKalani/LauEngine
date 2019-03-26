#ifndef AICOMPONENT_HPP_INCLUDED
#define AICOMPONENT_HPP_INCLUDED

#include "../Collision.hpp"
#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"


extern Manager manager;

class AIComponent : public Component
{
public:
    TransformComponent* transform = nullptr;
    SpriteComponent* sprite = nullptr;
    ColliderComponent* collider = nullptr;
    SDL_Rect result;
    AIComponent()
    {
        
    }
    
    void init() override
    {
        if(entity->hasComponent<TransformComponent>())
            transform = &entity->getComponent<TransformComponent>();
        if(entity->hasComponent<SpriteComponent>())
            sprite = &entity->getComponent<SpriteComponent>();
        if(entity->hasComponent<ColliderComponent>())
            collider = &entity->getComponent<ColliderComponent>();
        
    }
    
    void update() override
    {
        auto& colliders(manager.getGroup(Game::groupColliders));
        
        if(static_cast<int>((SDL_GetTicks() / 1000) % 2) == 1)
        {
            transform->velocity.x = 1;
            sprite->spriteFlip = SDL_FLIP_NONE;
        }
        else
        {
            transform->velocity.x = -1;
            sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
        }
        
        if(transform->velocity.x != 0 || transform->velocity.y != 0)
        {
            sprite->Play("Walk");
        }
        else 
        {
            sprite->Play("Idle");
        }

       for (auto c : colliders)
       {
           if(SDL_IntersectRect(&c->getComponent<ColliderComponent>().destR, &collider->destR, &result) == SDL_TRUE)
           {
               if(c->getComponent<ColliderComponent>().tag == "terrain")
               {
                   transform->position = transform->lastPosition;
               }
           }
       }

    }

};

#endif