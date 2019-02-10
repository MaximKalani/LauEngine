#include "engine.hpp"
#include "TextureManager.hpp"

#include "Map.hpp"
#include "ECS/Components.hpp"
#include "Vector2D.hpp"

#include "Collision.hpp"

#include "EventHandler.hpp"


EventHandler handler;
Map* mapp;
Manager manager;

std::vector<ColliderComponent*> Game::colliders;

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;


bool Game::isRunning = false;

auto& player(manager.addEntity());


const char* tileset = "assets/tileset.png";

enum groupLabels : std::size_t
{
    groupMap,
    groupPlayers,
    groupEnemies,
    groupColliders
};


auto& tiles(manager.getGroup(groupMap));
auto& players(manager.getGroup(groupPlayers));
auto& enemies(manager.getGroup(groupEnemies));

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

    Map::LoadMap("assets/tilemap.txt", 16, 16, 64);
    
    player.addComponent<TransformComponent>(400, 320, 24, 16, 4);
    player.addComponent<SpriteComponent>("assets/sprite.png", true);
    //player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    
    
 }

 void Game::handleEvents()
 {

    handler.handleInput(&player);

 }

 void Game::update()
 {
     manager.refresh();
     manager.update();
     
     Vector2D pVel = player.getComponent<TransformComponent>().velocity;
     int pSpeed = player.getComponent<TransformComponent>().speed;
     
    for (auto t : tiles)
    {
        t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
        t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
        
    }

 }



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

void Game::AddTile(int srcX, int srcY,int xpos, int ypos, int destTileSize)
{
    auto& tile(manager.addEntity());
    tile.addComponent<TileComponent>(srcX, srcY, xpos,ypos, tileset, destTileSize);
    tile.addGroup(groupMap);
}