#ifndef GAMEWINDOW_H
#define GAMEWINDOW_H
#include "main.h"

class GameWindow
{
    const int   TICK_RATE;
    const DWORD TIME_PER_TICK;
    const float FRACTION_TIME_PER_TICK;
    SDL_Surface* screen;
    int width, height;
public:


    GameWindow();
    ~GameWindow();
    int GetWidth() const;
    int GetHeight() const;
    DWORD GetTimePerTick() const;
    SDL_Surface* Screen();

};

#endif // GAMEWINDOW_H
