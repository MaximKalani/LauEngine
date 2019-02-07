#include "engine.hpp"
#include "TextureManager.hpp"

#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"

#include "Collision.hpp"

Map* mapp;
Manager manager;

std::vector<ColliderComponent*> Game::colliders;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());
auto& tile3(manager.addEntity());

 Game::Game()
 {}

 Game::~Game()
 {}

 void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
 {
    int flags = 0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        printf("Subsystems initialized\n");

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if(window)
        {
            printf("Window created\n");
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            printf("Renderer created\n");
        }

        isRunning = true;
    } else {
        isRunning = false;
    }

    mapp = new Map();
    
    tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
    tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
    tile2.addComponent<TileComponent>(150, 150, 32, 32, 2);
    tile3.addComponent<TileComponent>(400, 300, 32, 32, 3);
    
    tile1.addComponent<ColliderComponent>("wall_left");
    tile2.addComponent<ColliderComponent>("wall_right");
    tile3.addComponent<ColliderComponent>("wall_mid");
    
    
    player.addComponent<TransformComponent>(100, 500);
    player.addComponent<SpriteComponent>("assets/sprites/imp_idle_anim_f0.png");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    
    wall.addComponent<TransformComponent>(0, 0, 100, 100, 1);
    wall.addComponent<SpriteComponent>("assets/sprites/wall_mid.png");
    wall.addComponent<ColliderComponent>("wall");
 }

 void Game::handleEvents()
 {
    SDL_PollEvent(&event);
    switch(event.type) {
        case SDL_QUIT:
            isRunning = false;
            break;
        default:
            break;
    }
 }

 void Game::update()
 {
     manager.refresh();
     manager.update();
     
     if(Collision::AABB(player.getComponent<ColliderComponent>().collider, 
        wall.getComponent<ColliderComponent>().collider))
        {
            printf("collision\n");
        }
 }

 void Game::render()
 {
    SDL_RenderClear(renderer);
    //mapp->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);

 }

 void Game::clean()
 {
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    printf("Game cleaned");
 }

bool Game::running()
{
    return isRunning;
}
