#ifndef TEXTUREMANAGER_HPP_INCLUDED
#define TEXTUREMANAGER_HPP_INCLUDED

#include "engine.hpp"

class TextureManager {
    public:
        static SDL_Texture* LoadTexture(const char* fileName);
        static void Draw(SDL_Texture* tex, SDL_Rect src, SDL_Rect dest);
};
#endif // TEXTUREMANAGER_HPP_INCLUDED
