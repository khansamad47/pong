#include "pong_game.h"

#include<SDL2/SDL.h>

namespace pong {

Game::Game()
{

}

bool Game::initialize()
{
    if (0 != SDL_Init(SDL_INIT_VIDEO))
    {
        SDL_Log("Failed to initialize SDL: %s", SDL_GetError());
        return false;
    }
    d_window = SDL_CreateWindow("Pong", 100, 100, WIDTH, HEIGHT, 0);
    if (d_window == nullptr)
    {
        SDL_Log("Failed to create SDL window: %s", SDL_GetError());
        return false;
    }

    d_renderer = SDL_CreateRenderer(d_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (d_renderer == nullptr)
    {
        SDL_Log("Failed to create SDL renderer: %s", SDL_GetError());
        return false;
    }
    d_isRunning = true;
    return true;
}

void Game::runLoop()
{
    while(d_isRunning)
    {
        processInput();
        updateGame();
        generateOutput();
    }
}

void Game::stop()
{
    SDL_DestroyRenderer(d_renderer);
    SDL_DestroyWindow(d_window);
    SDL_Quit(); // opposite of SDL_Init
}

void Game::processInput()
{
    // First process all events
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT: {
                d_isRunning = false;
            } break;
            default: {
                SDL_Log("Unhandled event: %i", event.type);
            }
        };
    }
    SDL_Log("All events processed.");

    const Uint8* state = SDL_GetKeyboardState(NULL);
    // if (state[SDL_SCANCODE_ESCAPE]) {
    //     d_isRunning = false;
    // }
    // if (state[SDL_KEYUP])
    // {
    //     paddleDirection = -1;
    // }
    // if (state[SDL_KEYDOWN])
    // {
    //     paddleDirection = 1;
    // }
}

void Game::updateGame()
{
    // const paddleSpeed = 5; // 5 unit per tick?
    // d_paddlePos.x += (paddleSpeed * paddleDirection)
}
void Game::generateOutput()
{
    SDL_SetRenderDrawColor(d_renderer, 0, 0, 255, 255);
    // Clearing back buffer to the set color
    SDL_RenderClear(d_renderer);

    // Draw entire game scene
    
    // Draw walls
    SDL_SetRenderDrawColor(d_renderer, 255, 255, 255, 255);
    {
        SDL_Rect wall{0,0,WIDTH,THICKNESS};
        SDL_RenderFillRect(d_renderer, &wall);
    }
    {
        SDL_Rect wall{0,HEIGHT-THICKNESS,WIDTH,THICKNESS};
        SDL_RenderFillRect(d_renderer, &wall);
    }
    {
        SDL_Rect wall{WIDTH-THICKNESS,0,THICKNESS,HEIGHT};
        SDL_RenderFillRect(d_renderer, &wall);
    }

    // Draw Paddle
    {
        SDL_Rect paddle{0,static_cast<int>(d_paddlePos.y - HEIGHT/20.0),THICKNESS, HEIGHT/10};
        SDL_RenderFillRect(d_renderer, &paddle);
    }
    {
        SDL_Rect ball{static_cast<int>(d_ballPos.x - THICKNESS/2.0),static_cast<int>(d_ballPos.y - THICKNESS/2.0),THICKNESS,THICKNESS};
        SDL_RenderFillRect(d_renderer, &ball);
    }

    // Flush the back buffer to front
    SDL_RenderPresent(d_renderer);
}

}
