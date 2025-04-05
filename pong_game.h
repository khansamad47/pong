#ifndef PONG_GAME
#define PONG_GAME

#include <SDL2/SDL.h>

namespace pong {

struct vector2 
{
    float x;
    float y;
};

class Game {
  private:
    // CLASS DATA
    static constexpr size_t             WIDTH     = 1024;
    static constexpr size_t             HEIGHT    =  786;
    static constexpr size_t             THICKNESS =   15;

    // DATA
    SDL_Window*              d_window;
    SDL_Renderer*            d_renderer;
    bool                     d_isRunning;
    vector2                  d_ballPos   {WIDTH/2.0, HEIGHT/2.0};
    vector2                  d_paddlePos {0.0, HEIGHT/2.0};

  public:
    // CREATORS
    Game();

    // MANIPULATORS
    bool initialize();

    void runLoop();

    void stop();

  private:
    // PRIVATE MANIPULATORS
    void processInput();
    void updateGame();
    void generateOutput();
};

}

#endif
