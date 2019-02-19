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
        
        static void AddTile(int scrX, int srcY, int x, int y, int scale);
        static SDL_Renderer *renderer;
        static SDL_Event event;
        static std::vector<ColliderComponent*> colliders;
        static bool isRunning;


        
        
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
