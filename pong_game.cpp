#include "pong_game.h"

#include<SDL2/SDL.h>

namespace pong {

template<typename T1, typename T2>
auto max(T1 t1, T2 t2)
{
    return t1 > t2? t1 : t2;
}

template<typename T1, typename T2>
auto min(T1 t1, T2 t2)
{
    return t1 < t2? t1 : t2;
}

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
        // Comute how much time has passed:
        d_deltaTime = 0.1;
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
    if (state[SDL_SCANCODE_K])
    {
        d_paddleDirection = -1;
    }
    if (state[SDL_SCANCODE_J])
    {
        d_paddleDirection = 1;
    }
    if (state[SDL_SCANCODE_ESCAPE]) {
        d_isRunning = false;
    }
}

void Game::updateGame()
{
    // Update paddle position
    d_paddlePos.y += (d_paddleSpeed * d_paddleDirection) * d_deltaTime;

    // Handle paddle/wall collision
    d_paddlePos.y = max(d_paddlePos.y, THICKNESS + PADDLE_HEIGHT/2.0);
    d_paddlePos.y = min(d_paddlePos.y, HEIGHT - THICKNESS - PADDLE_HEIGHT/2.0);

    // Update ball position
    d_ballPos.x += (d_ballSpeed * d_ballDirection.x) * d_deltaTime;
    d_ballPos.y += (d_ballSpeed * d_ballDirection.y) * d_deltaTime;

    // Handle ball/wall collision
    if (d_ballPos.y <= THICKNESS + BALL_HEIGHT/2.0)
    {
        d_ballDirection.y *= -1;
    }
    if (d_ballPos.y >= HEIGHT - THICKNESS - BALL_HEIGHT/2.0)
    {
        d_ballDirection.y *= -1;
    }
    if (d_ballPos.x >= WIDTH - THICKNESS - BALL_WIDTH/2.0)
    {
        d_ballDirection.x *= -1;
    }

    // ball and paddle collision
    if (d_ballPos.x <= THICKNESS + BALL_WIDTH/2.0)
    {
        if (d_paddlePos.y - PADDLE_HEIGHT/2.0 <= d_ballPos.y  && d_paddlePos.y + PADDLE_HEIGHT/2.0 >= d_ballPos.y)
        {
            d_ballDirection.x *= -1;
        }
        else {
            SDL_Log("Lost");
        }
    }
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
        SDL_Rect paddle{
            0,
            static_cast<int>(d_paddlePos.y - PADDLE_HEIGHT/2.0),
            PADDLE_WIDTH,
            PADDLE_HEIGHT};

        SDL_RenderFillRect(d_renderer, &paddle);
    }
    // Draw Ball
    {
        SDL_Rect ball{
            static_cast<int>(d_ballPos.x - BALL_WIDTH/2.0),
            static_cast<int>(d_ballPos.y - BALL_HEIGHT/2.0),
            BALL_WIDTH,
            BALL_HEIGHT};

        SDL_RenderFillRect(d_renderer, &ball);
    }

    // Flush the back buffer to front
    SDL_RenderPresent(d_renderer);
}

}
