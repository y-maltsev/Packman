#ifndef PACKMAN_H
#define PACKMAN_H
#include "MovingObject.h"

class Packman: public MovingObject
{
    enum Direction { Left,Right,Up,Down };
protected:
    int nextdx, nextdy;
    int score, lives, level;
    int dyingAnimationCount;
    int animationDirection;
    SDL_Surface *up1, *up2, *up3;
    SDL_Surface *down1, *down2, *down3;
    SDL_Surface *left1, *left2, *left3;
    SDL_Surface *right1, *right2, *right3;
    SDL_Surface *dying1, *dying2, *dying3, *dying4;
    SDL_Surface *dying5, *dying6, *dying7, *dying8;
public:
    Packman(GameWindow *win);
    ~Packman();
    void Init();
    void Update();
    void UpdateAnimation();

    void SetDirection(int dirX, int dirY);
    int  GetScore();
    int  GetLives();
    int  GetLevel();
    void IncreaseScoreBy(int scoreModif);
    void IncreaseLivesBy(int livesModif);
    void IncreaseLevel();
    void SetDying();
    void SetAlive();
    bool IsDying();
    bool IsDead();

};



#endif // PACKMAN_H
