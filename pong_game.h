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
    static constexpr float              SIZE_FACTOR  =    1;
    static constexpr size_t             WIDTH        = 1024 * SIZE_FACTOR;
    static constexpr size_t             HEIGHT       =  786 * SIZE_FACTOR;
    static constexpr size_t             THICKNESS    =   15 * SIZE_FACTOR;

    static constexpr size_t             PADDLE_WIDTH  = THICKNESS;
    static constexpr size_t             PADDLE_HEIGHT = HEIGHT / 10;

    static constexpr size_t             BALL_WIDTH  = THICKNESS;
    static constexpr size_t             BALL_HEIGHT = THICKNESS;
    // DATA
    SDL_Window*              d_window{nullptr};
    SDL_Renderer*            d_renderer{nullptr};
    bool                     d_isRunning{false};

    double                   d_deltaTime{0.0};

    // Ball
    vector2                  d_ballPos{WIDTH/2.0, HEIGHT/2.0};
    vector2                  d_ballDirection{1,1};
    float                    d_ballSpeed{50.0 * SIZE_FACTOR};

    // Paddle 
    vector2                  d_paddlePos{0.0, HEIGHT/2.0};
    int                      d_paddleDirection{1};
    float                    d_paddleSpeed{50.0 * SIZE_FACTOR};

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
