#ifndef AICOMPONENT_HPP_INCLUDED
#define AICOMPONENT_HPP_INCLUDED

#include "ECS.hpp"
#include "Components.hpp"

class AIComponent : public Component
{
public:
    TransformComponent* transform = nullptr;
    SpriteComponent* sprite = nullptr;
    AIComponent()
    {
        
    }
    
    void init() override
    {
        if(entity->hasComponent<TransformComponent>())
            transform = &entity->getComponent<TransformComponent>();
        if(entity->hasComponent<SpriteComponent>())
            sprite = &entity->getComponent<SpriteComponent>();
    }
    
    void update() override
    {
        
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
            entity->getComponent<SpriteComponent>().Play("Walk");
        }
        else 
        {
            entity->getComponent<SpriteComponent>().Play("Idle");
        }
        
    }
};

#endif