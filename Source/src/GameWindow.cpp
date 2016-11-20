#include "GameWindow.h"

GameWindow::GameWindow()
    :TICK_RATE(25),
     TIME_PER_TICK(1000 / TICK_RATE),
     FRACTION_TIME_PER_TICK(TIME_PER_TICK / 1000.0f),
     width(580),
     height(380)
{
    SDL_Init( SDL_INIT_VIDEO );
    screen = SDL_SetVideoMode( width, height, 32, SDL_SWSURFACE | SDL_DOUBLEBUF );
    SDL_WM_SetCaption("Packman","Packman");
    TTF_Init();
}

GameWindow::~GameWindow()
{
    SDL_Quit();
    TTF_Quit();
}

int GameWindow::GetWidth() const
{
    return width;
}

int GameWindow::GetHeight() const
{
    return height;
}
DWORD GameWindow::GetTimePerTick() const
{
    return TIME_PER_TICK;
}


SDL_Surface* GameWindow::Screen()
{
    return screen;
}
