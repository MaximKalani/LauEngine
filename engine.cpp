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

SDL_Renderer *Game::renderer = nullptr;
SDL_Event Game::event;
SDL_Rect Game::camera = {0,0,800,640};

bool Game::isRunning = false;
bool Game::drawColliders = false;


auto& player(manager.addEntity());
auto& projectile(manager.addEntity());

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));
auto& projectiles(manager.getGroup(Game::groupProjectiles));

Game::Game()
{}

Game::~Game()
{}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    windowH = height;
    windowW = width;
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

    mapp = new Map("assets/tilemap2.txt", "assets/tileset.png", 16, 16, 16, 64);

    player.addComponent<TransformComponent>(80, 100, 24, 16, 3);
    player.addComponent<SpriteComponent>("assets/sprite.png", true);
    player.addComponent<ColliderComponent>("player");
    player.addGroup(groupPlayers);
    
    projectile.addComponent<ProjectileComponent>(90, 110, 16, 16, 1, 5000, 7, "assets/SiegHeil.png", 1, 1);
    projectile.addComponent<ColliderComponent>("projectile");
    projectile.addGroup(groupProjectiles);
    
 }

void Game::handleEvents()
{
    handler.handleInput(&player);
}

void Game::update()
{
    Vector2D pPos = player.getComponent<TransformComponent>().position;

    manager.refresh();
    manager.update();

    Vector2D pVel = player.getComponent<TransformComponent>().velocity;

    if(pVel.x != 0 && pVel.y != 0)
    {
        player.getComponent<TransformComponent>().speed = 2;
    }
    
    if(pVel.x != 0 || pVel.y != 0)
    {
        player.getComponent<SpriteComponent>().Play("Walk");
    }
    else 
    {
        player.getComponent<SpriteComponent>().Play("Idle");
    }
    

    for (auto c : colliders)
    {
        if(Collision::AABB(c->getComponent<ColliderComponent>().destR, player.getComponent<ColliderComponent>().destR))
        {
            if(c->getComponent<ColliderComponent>().tag == "terrain")
            {
                printf("Wall hit");
                player.getComponent<TransformComponent>().position = pPos;
            }
        }
    }


    camera.x = static_cast<int>(player.getComponent<TransformComponent>().position.x - 400);
    camera.y = static_cast<int>(player.getComponent<TransformComponent>().position.y - 320);

    if (camera.x < 0)
    {
        camera.x = 0;
    }
    if (camera.y < 0) 
    {
        camera.y = 0; 
    }
    if (camera.x + camera.w > mapp->mapSize.x)
    {
        camera.x = mapp->mapSize.x - camera.w;
    }
    if (camera.y + camera.h > mapp->mapSize.y)
    {
        camera.y = mapp->mapSize.y - camera.h;
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
    for (auto& c : colliders)
    {
        c->draw();
    }    
    for (auto& j : projectiles)
    {
        j->draw();
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

