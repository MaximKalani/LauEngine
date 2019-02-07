#ifndef ANIMATION_HPP_INCLUDED
#define ANIMATION_HPP_INCLUDED

struct Animation
{
    int index;
    int frames;
    int speed;
    
    Animation() {}
    Animation(int i, int f, int s)
    {
        index = i;
        frames = f;
        speed = s;
        
    }
};

#endif 