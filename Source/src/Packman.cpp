#include "Packman.h"

Packman::Packman(GameWindow *win):
    MovingObject(win),
    up1(NULL),up2(NULL),up3(NULL),
    down1(NULL),down2(NULL),down3(NULL),
    left1(NULL),left2(NULL),left3(NULL),
    right1(NULL),right2(NULL),right3(NULL),
    dying1(NULL),dying2(NULL),dying3(NULL),dying4(NULL),
    dying5(NULL),dying6(NULL),dying7(NULL),dying8(NULL)
{
    Init();
}

Packman::~Packman()
{
    SDL_FreeSurface(up1);
    SDL_FreeSurface(up2);
    SDL_FreeSurface(up3);
    SDL_FreeSurface(down1);
    SDL_FreeSurface(down2);
    SDL_FreeSurface(down3);
    SDL_FreeSurface(left1);
    SDL_FreeSurface(left2);
    SDL_FreeSurface(left3);
    SDL_FreeSurface(right1);
    SDL_FreeSurface(right2);
    SDL_FreeSurface(right3);
    SDL_FreeSurface(dying1);
    SDL_FreeSurface(dying2);
    SDL_FreeSurface(dying3);
    SDL_FreeSurface(dying4);
    SDL_FreeSurface(dying5);
    SDL_FreeSurface(dying6);
    SDL_FreeSurface(dying7);
    SDL_FreeSurface(dying8);
}

void Packman::Init()
{
    MovingObject::Init();

    LoadFrame(up1,"Media/PackmanU1.bmp");
    LoadFrame(up2,"Media/PackmanU2.bmp");
    LoadFrame(up3,"Media/PackmanU3.bmp");

    LoadFrame(down1,"Media/PackmanD1.bmp");
    LoadFrame(down2,"Media/PackmanD2.bmp");
    LoadFrame(down3,"Media/PackmanD3.bmp");

    LoadFrame(left1,"Media/PackmanL1.bmp");
    LoadFrame(left2,"Media/PackmanL2.bmp");
    LoadFrame(left3,"Media/PackmanL3.bmp");

    LoadFrame(right1,"Media/PackmanR1.bmp");
    LoadFrame(right2,"Media/PackmanR2.bmp");
    LoadFrame(right3,"Media/PackmanR3.bmp");

    LoadFrame(dying1,"Media/PackmanDying1.bmp");
    LoadFrame(dying2,"Media/PackmanDying2.bmp");
    LoadFrame(dying3,"Media/PackmanDying3.bmp");
    LoadFrame(dying4,"Media/PackmanDying4.bmp");
    LoadFrame(dying5,"Media/PackmanDying5.bmp");
    LoadFrame(dying6,"Media/PackmanDying6.bmp");
    LoadFrame(dying7,"Media/PackmanDying7.bmp");
    LoadFrame(dying8,"Media/PackmanDying8.bmp");

    currentFrame = left1;
    animationDirection = Direction::Left;
    score = 0;
    lives = 3;
    level = 1;
    nextdx = -1;
    nextdy = 0;
    dyingAnimationCount = -1;
}



void Packman::Update()
{
    if(dyingAnimationCount > 0)
    {
        dyingAnimationCount--;
    }
    else // forbid movement while dying
    {
        bool dirclear=false;
        int oldx, oldy;

        //remember old coords for adjustments at end
        oldx=xPix;
        oldy=yPix;


        //if turnaround, apply dirchange immediately
        if ( dx == -nextdx && dy == -nextdy && dx!=dy )
        {
            dx=nextdx;
            dy=nextdy;
        }
        //if node is reached
        if ( xPix%mapCellSize == 0 && yPix%mapCellSize == 0 )
        {
            if ( dx != nextdx || dy != nextdy )
            {
                //if nextdir is clear, apply dirchange
                if ( (dirclear = ( !IsColidingWithMap(x+nextdx, y+nextdy))) )
                {
                    dx=nextdx;
                    dy=nextdy;
                }
            }
        }

        //if nextdir not clear check current dir
        if ( ! dirclear )
        {
            if ( dx >= 0 && dy >= 0)
                dirclear = ! IsColidingWithMap(x+dx,y+dy);
            else if ( dx <= 0 && dy <= 0)
                dirclear = ! IsColidingWithMap( (xPix+dx) / mapCellSize, (yPix+dy) / mapCellSize);
        }

        //MOVEMENT PART STARTS HERE

        if ( dirclear )
        {
            //  dir    *       speed
            xFloat +=  (float)( dx * speedMult ) ;
            yFloat +=  (float)( dy * speedMult ) ;
        }

        //COORD ADJUSTMENTS

        if ( xFloat > (float)(x+1)*mapCellSize ) xFloat = (float)(x+1)*mapCellSize;
        if ( yFloat > (float)(y+1)*mapCellSize ) yFloat = (float)(y+1)*mapCellSize;

        if ( xFloat < (float)(x)*mapCellSize && oldx > (float)(x)*mapCellSize )
            xFloat = (float)(x)*mapCellSize;
        if ( yFloat < (float)(y)*mapCellSize && oldy > (float)(y)*mapCellSize)
            yFloat = (float)(y)*mapCellSize;

        //COORD UPDATES

        xPix=(int)xFloat;
        yPix=(int)yFloat;

        x= xPix/mapCellSize;
        y= yPix/mapCellSize;
    }
    UpdateAnimation();
}

void Packman::SetDirection(int dirX, int dirY)
{
    nextdx = dirX;
    nextdy = dirY;
}

int Packman::GetScore()
{
    return score;
}

void Packman::IncreaseScoreBy(int scoreModif)
{
    score += scoreModif;
}

int Packman::GetLives()
{
    return lives;
}

void Packman::IncreaseLivesBy(int livesModif)
{
    lives += livesModif;
}


int Packman::GetLevel()
{
    return level;
}

void Packman::IncreaseLevel()
{
    level++;
}

void Packman::SetDying()
{
    if(dyingAnimationCount==-1)
    {
        dyingAnimationCount = 50;
    }
}

void Packman::SetAlive()
{
    dyingAnimationCount = -1;
    currentFrame = left1;
}


bool Packman::IsDying()
{
    bool result = (dyingAnimationCount > 0);
    return result;
}

bool Packman::IsDead()
{
    bool result = (dyingAnimationCount == 0);
    return result;
}


void Packman::UpdateAnimation()
{


    if(!IsDying())
    {
        animationCount++;
        if(animationCount>8)
        {
            animationCount = 0;
        }

        if(dx == -1 && dy == 0)  animationDirection = Direction::Left;
        if(dx == 1 && dy == 0)  animationDirection = Direction::Right;
        if(dx == 0 && dy == -1)  animationDirection = Direction::Up;
        if(dx == 0 && dy == 1)  animationDirection = Direction::Down;

        if(animationCount/2 == 0)
        {
            if(animationDirection == Direction::Left)  currentFrame = left1;
            if(animationDirection == Direction::Right) currentFrame = right1;
            if(animationDirection == Direction::Up)    currentFrame = up1;
            if(animationDirection == Direction::Down)  currentFrame = down1;
        }

        if(animationCount/2 == 1)
        {
            if(animationDirection == Direction::Left)  currentFrame = left2;
            if(animationDirection == Direction::Right) currentFrame = right2;
            if(animationDirection == Direction::Up)    currentFrame = up2;
            if(animationDirection == Direction::Down)  currentFrame = down2;
        }

        if(animationCount/2 == 2)
        {
            if(animationDirection == Direction::Left)  currentFrame = left3;
            if(animationDirection == Direction::Right) currentFrame = right3;
            if(animationDirection == Direction::Up)    currentFrame = up3;
            if(animationDirection == Direction::Down)  currentFrame = down3;
        }

        if(animationCount/2 == 3)
        {
            if(animationDirection == Direction::Left)  currentFrame = left2;
            if(animationDirection == Direction::Right) currentFrame = right2;
            if(animationDirection == Direction::Up)    currentFrame = up2;
            if(animationDirection == Direction::Down)  currentFrame = down2;
        }
    }
    else
    {
        if(dyingAnimationCount > 44) currentFrame = dying1;
        else if(dyingAnimationCount > 38) currentFrame = dying2;
        else if(dyingAnimationCount > 32) currentFrame = dying3;
        else if(dyingAnimationCount > 26) currentFrame = dying4;
        else if(dyingAnimationCount > 20) currentFrame = dying5;
        else if(dyingAnimationCount > 14) currentFrame = dying6;
        else if(dyingAnimationCount > 8) currentFrame = dying7;
        else if(dyingAnimationCount > 0) currentFrame = dying8;
    }


}
