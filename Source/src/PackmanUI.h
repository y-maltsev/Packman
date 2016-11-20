#ifndef PACKMANUI_H
#define PACKMANUI_H
#include "Object.h"
#include "Packman.h"

class PackmanUI: public Object
{
protected:
    Packman* packman;
    SDL_Color textColor;
    TTF_Font *font;
    SDL_Surface* scoreText;
    SDL_Surface* scoreNumber;
    SDL_Surface* livesText;
    SDL_Surface* livesNumber;
    SDL_Surface* levelText;
    SDL_Surface* levelNumber;
    SDL_Surface* gameOver;
public:
    PackmanUI(GameWindow *win);
    ~PackmanUI();
    void Init();
    void Update();
    void Render();
    void SetPackmanTarget(Packman* packmanTarget);
};

#endif // PACKMANUI_H
