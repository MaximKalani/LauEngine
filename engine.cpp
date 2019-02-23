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


bool Game::isRunning = false;
bool Game::drawColliders = false;

auto& player(manager.addEntity());

auto& tiles(manager.getGroup(Game::groupMap));
auto& players(manager.getGroup(Game::groupPlayers));
auto& colliders(manager.getGroup(Game::groupColliders));

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

    mapp = new Map("assets/tilemap2.txt", "assets/tileset.png", 16, 16, 16, 64);

    player.addComponent<TransformComponent>(400, 320, 24, 16, 3);
    player.addComponent<SpriteComponent>("assets/sprite.png", true);
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
    auto pCollider = player.getComponent<ColliderComponent>();
    
    if(pVel.x != 0 || pVel.y != 0)
    {
        player.getComponent<SpriteComponent>().Play("Walk");
    }
    else 
    {
        player.getComponent<SpriteComponent>().Play("Idle");
    }
    
    if(pVel.x != 0 && pVel.y != 0)
    {
        pSpeed = 2;
    }
    
    //try to move
    for(auto c : colliders)
    {
        c->getComponent<ColliderComponent>().collider.x += -(pVel.x * pSpeed);
        c->getComponent<ColliderComponent>().collider.y += -(pVel.y * pSpeed);
    }
    
    //if (collides) - move back
    for (auto c : colliders)
    {
        if(Collision::AABB(c->getComponent<ColliderComponent>(), pCollider))
        {
            if(c->getComponent<ColliderComponent>().tag == "terrain")
            {
                collides = true;
            }
        }
        
        
    }

    if(!collides) //move tiles if does not collide
    {
            
        for (auto t : tiles)
        {
            t->getComponent<TileComponent>().destRect.x += -(pVel.x * pSpeed);
            t->getComponent<TileComponent>().destRect.y += -(pVel.y * pSpeed);
        }

    }
    else //if collide - do not move tiles and move colliders back
    {
        for(auto c : colliders)
        {
            c->getComponent<ColliderComponent>().collider.x += (pVel.x * pSpeed);
            c->getComponent<ColliderComponent>().collider.y += (pVel.y * pSpeed);
        }
        collides = false;
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

