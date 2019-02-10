#ifndef EVENTHANDLER_HPP_INCLUDED
#define EVENTHANDLER_HPP_INCLUDED

#include "engine.hpp"
#include "ECS/ECS.hpp"
#include "ECS/SpriteComponent.hpp"
#include "ECS/TransformComponent.hpp"


class EventHandler
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;
    void handleInput(Entity* player);
    
};

#endif