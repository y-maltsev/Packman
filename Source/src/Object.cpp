#include "Object.h"

Object::Object(GameWindow *win): window(win), currentFrame(NULL)
{
}

Object::~Object()
{
}

void Object::Render()
{
    SDL_Rect destination;
    destination.x = xPix;
    destination.y = yPix;
    SDL_BlitSurface( currentFrame, NULL, window->Screen(), &destination );
}

void Object::Init()
{
    xPix = 0;
    yPix = 0;
    animationCount = 0;
}

int Object::GetXPix()
{
    return xPix;
}

int Object::GetYPix()
{
    return yPix;
}

void Object::SetXPix(int xTmp)
{
    xPix = xTmp;
}

void Object::SetYPix(int yTmp)
{
    yPix = yTmp;
}

void Object::LoadFrame(SDL_Surface *&frame, string name)
{
    SDL_FreeSurface(frame);
    frame = SDL_LoadBMP(name.c_str());
    Uint32 colorkey = SDL_MapRGB( frame->format, 0, 0, 0);
    SDL_SetColorKey( frame, SDL_SRCCOLORKEY, colorkey );
}






