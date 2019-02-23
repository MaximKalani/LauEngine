#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <vector>
#include "Vector2D.hpp"

class ColliderComponent;

class Game {
    public:
        Game();
        ~Game();

        void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

        void handleEvents();
        void update();
        void render();
        void clean();

        bool running();
        
        bool collides = false;
        
        static SDL_Renderer *renderer;
        static SDL_Event event;

        static bool isRunning;
        static bool drawColliders;

        
        
        enum groupLabels : std::size_t
        {
            groupMap,
            groupPlayers,
            groupEnemies,
            groupColliders
        };


    private:
        
        SDL_Window *window;

};


#endif // ENGINE_HPP_INCLUDED
