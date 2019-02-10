#ifndef COLLIDERCOMPONENT_HPP_INCLUDED
#define COLLIDERCOMPONENT_HPP_INCLUDED

#include <string>
#include <SDL2/SDL.h>
#include "ECS.hpp"
#include "Components.hpp"
#include "../TextureManager.hpp"


class ColliderComponent : public Component
{
public:
    SDL_Rect collider;
    std::string tag;
    
    TransformComponent* transform;
    
    ColliderComponent(std::string t)
    {
        tag = t;
    }
    
    void init() override
    {
        if(!entity->hasComponent<TransformComponent>())
        {
            entity->addComponent<TransformComponent>();
        }
        transform = &entity->getComponent<TransformComponent>();
        
        Game::colliders.push_back(this);
    }
    
    void update() override
    {
        collider.x = static_cast<int>(transform->position.x);
        collider.y = static_cast<int>(transform->position.y);
        collider.w = transform->width * transform->scale;
        collider.h = transform->height * transform->scale;
    }
    
};


#endif