#include "EventHandler.hpp"

void EventHandler::handleInput(Entity* player)
{
        transform = &player->getComponent<TransformComponent>();
        sprite = &player->getComponent<SpriteComponent>();
        
        while (SDL_PollEvent(&Game::event))
        {
            if(Game::event.type == SDL_QUIT)
                Game::isRunning = false;
            else if(Game::event.type == SDL_KEYDOWN)
            {
                switch(Game::event.key.keysym.sym)
                {
                    case SDLK_w:

                        transform->velocity.y = -1;
                        sprite->Play("Walk");

                        break;
                    case SDLK_a:
                        transform->velocity.x = -1;
                        sprite->Play("Walk");
                        sprite->spriteFlip = SDL_FLIP_HORIZONTAL;
                        break;
                    case SDLK_s:
                        transform->velocity.y = 1;
                        sprite->Play("Walk");
                        break;
                    case SDLK_d:
                        transform->velocity.x = 1;
                        sprite->Play("Walk");
                        sprite->spriteFlip = SDL_FLIP_NONE;
                        break;
                    default:
                        break;
                }
            }
        
            else if(Game::event.type == SDL_KEYUP)
            {
                switch(Game::event.key.keysym.sym)
                {
                    case SDLK_w:

                        transform->velocity.y = 0;
                        sprite->Play("Idle");

                        break;
                    case SDLK_a:
                        transform->velocity.x = 0;
                        sprite->Play("Idle");
                    
                        break;
                    case SDLK_s:
                        transform->velocity.y = 0;
                        sprite->Play("Idle");
                        break;
                    case SDLK_d:
                        transform->velocity.x = 0;
                        sprite->Play("Idle");
                        break;
                    case SDLK_ESCAPE:
                        Game::isRunning = false;
                    default:
                        break;
                }
            }

            
        
        }
        
}