#ifndef GAME_H
#define GAME_H

#include "main.h"

class Game
{
    const int TICK_RATE;
    const DWORD TIME_PER_TICK;
    const float FRACTION_TIME_PER_TICK;

    int iScreenWidth, iScreenHeight;
    bool bIsGameRunning;
    SDL_Surface* screen;
    SDL_Event    event;


public:
    Game();
    virtual ~Game();

    void eventHandler(SDL_Event event);
    void update();
    void render();
    void run();
};

#endif // GAME_H
