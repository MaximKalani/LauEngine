#ifndef HPCOMPONENT_HPP_INCLUDED
#define HPCOMPONENT_HPP_INCLUDED

#include "ECS.hpp"
#include "Components.hpp"

class HPComponent : public Component
{
private:

    int hp;
    
public:

    HPComponent(int healthpoints)
    {
        hp = healthpoints;
    }
    
    ~HPComponent()
    {}
    
    int getHP()
    {
        return hp;
    }
    
    void addToHP(int n)
    {
        hp += n;
    }
    
    void setHP(int n)
    {
        hp = n;
    }
    
    bool isAlive()
    {
        if(hp <= 0)
            return 0;
        else
            return 1;
    }
    
    void update() override
    {
        if(!isAlive()) //set sprite to dead, remove collider and turn ai off
        {
            printf("something is dead\n");
            entity->destroy();
        }
            
    }
};

#endif