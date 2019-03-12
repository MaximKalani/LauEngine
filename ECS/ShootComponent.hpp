#ifndef SHOOTCOMPONENT_HPP_INCLUDED
#define SHOOTCOMPONENT_HPP_INCLUDED

#include "ECS.hpp"
#include "Components.hpp"
#include "../Vector2D.hpp"
#include "../engine.hpp"


extern Manager manager;

class ShootComponent : public Component
{
public:
    TransformComponent* transform;
    ColliderComponent* collider;
    bool hurtsPlayer = true;
    Vector2D projPosition;
    ShootComponent()
    {};
    
    ~ShootComponent()
    {};
    void init() override
    {

    }
    void shoot(std::string projType)
    {
        transform = &entity->getComponent<TransformComponent>();
        collider = &entity->getComponent<ColliderComponent>();
        if(collider->tag == "player")
            hurtsPlayer = false;
        
        projPosition.x = (transform->position.x + transform->lastDirection.x * transform->height);
        projPosition.y = (transform->position.y + transform->lastDirection.y * transform->width) + 20;
        

        
        auto& projectile(manager.addEntity());
        projectile.addComponent<ProjectileComponent>(projPosition, projType, transform->lastDirection, hurtsPlayer);
        projectile.addComponent<ColliderComponent>("projectile");
        projectile.addGroup(Game::groupProjectiles);
    }
    
};

#endif