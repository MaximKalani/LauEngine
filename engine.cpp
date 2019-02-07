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

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};

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

    Map::LoadMap("assets/16x16.map", 16, 16);
    
    player.addComponent<TransformComponent>(100, 500, 48, 38, 3);
    player.addComponent<SpriteComponent>("assets/gothic-hero-idle.png", 4, 100);
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    
    
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
     
     for(auto cc : colliders)
     {
        Collision::AABB(player.getComponent<ColliderComponent>(), *cc);
     }
     
 }

auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));


 void Game::render()
 {
    SDL_RenderClear(renderer);
    for (auto& t : tiles)
    {
        t->draw();
    }
    for (auto& p : players)
    {
        p->draw();
    }
    for (auto& e : enemies)
    {
        e->draw();
    }
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

void Game::AddTile(int id, int x, int y)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(x,y,32,32,id);
    tile.addGroup(groupMap);
}