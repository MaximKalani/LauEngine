#ifndef GAMEOBJECT_HPP_INCLUDED
#define GAMEOBJECT_HPP_INCLUDED

#include "engine.hpp"

class GameObject {

    public:
        GameObject(const char* texturesheet, int x, int y);
        ~GameObject();

        void Update();
        void Render();

    private:

        int xpos;
        int ypos;

        SDL_Texture* objTexture;
        SDL_Rect srcRect, destRect;


};

#endif // GAMEOBJECT_HPP_INCLUDED
