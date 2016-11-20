#include "Bonus.h"

Bonus::Bonus(GameWindow *win): Object(win),pill1(NULL),pill2(NULL),pill3(NULL)
{
    Init();
}

Bonus::~Bonus()
{
    SDL_FreeSurface(pill1);
    SDL_FreeSurface(pill2);
    SDL_FreeSurface(pill3);
}

void Bonus::Init()
{
    Object::Init();
    InitType(1);
}

void Bonus::Update()
{
    UpdateAnimation();
}

void Bonus::InitType(int typeTmp)
{
    type = typeTmp;
    if(type == 1)
    {
        LoadFrame(currentFrame,"Media/Bonus.bmp");
    }
    else
    {
        LoadFrame(pill1,"Media/BonusPill1.bmp");
        LoadFrame(pill2,"Media/BonusPill2.bmp");
        LoadFrame(pill3,"Media/BonusPill3.bmp");
        SDL_FreeSurface(currentFrame);
        currentFrame = pill3;
    }
}

int Bonus::GetType()
{
    return type;
}

void Bonus::UpdateAnimation()
{
    if(type == 2)
    {
        animationCount++;
        if(animationCount>6) animationCount=0;

        if(animationCount/2==0) currentFrame = pill1;
        if(animationCount/2==1) currentFrame = pill2;
        if(animationCount/2==2) currentFrame = pill3;
    }
}
