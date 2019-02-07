#ifndef SPRITECOMPONENT_HPP_INCLUDED
#define SPRITECOMPONENT_HPP_INCLUDED

#include "Components.hpp"
#include "SDL2/SDL.h"
#include "../TextureManager.hpp"


class SpriteComponent : public Component
{
private:
    TransformComponent *transform;
    SDL_Texture *texture;
    SDL_Rect srcRect, destRect;

public:

    SpriteComponent() = default;
    SpriteComponent(const char* path)
    {
        setTex(path);
    }
    
    ~SpriteComponent()
    {
        SDL_DestroyTexture(texture);
    }
    void setTex(const char* path)
    {
        texture = TextureManager::LoadTexture(path);
    }
    void init() override
    {
        transform = &entity->getComponent<TransformComponent>();

        srcRect.x = srcRect.y = 0;
        srcRect.w = transform->width;
        srcRect.h = transform->width;



    }

    void update() override
    {
        destRect.x = (int)transform->position.x;
        destRect.y = (int)transform->position.y;
        
        destRect.w = transform->width * transform->scale;
        destRect.h = transform->width * transform->scale;
    }

    void draw() override
    {
        TextureManager::Draw(texture, srcRect, destRect);
    }




};

#endif // SPRITECOMPONENT_HPP_INCLUDED
