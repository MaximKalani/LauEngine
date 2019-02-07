#ifndef ENGINE_HPP_INCLUDED
#define ENGINE_HPP_INCLUDED

#include <SDL2/SDL.h>
#include <stdio.h>
#include <SDL2/SDL_image.h>
#include <vector>

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
        int cnt = 0;

        static SDL_Renderer *renderer;
        static SDL_Event event;
        static std::vector<ColliderComponent*> colliders;
        
    private:
        bool isRunning;
        SDL_Window *window;

};


#endif // ENGINE_HPP_INCLUDED
