#ifndef OBJECT_H
#define OBJECT_H
#include "main.h"
#include "Entity.h"
#include "GameWindow.h"

class Object: public Entity
{
protected:
    GameWindow* window;
    int xPix,yPix; // x,y in pixels
    SDL_Surface* currentFrame; // can be a single one, or multiple switching through this one.
    unsigned animationCount; // if the object has more than one Frame
public:
    Object(GameWindow *win);
    ~Object();
    void Render();
    void Init();
    int GetXPix();
    int GetYPix();
    void SetXPix(int xTmp);
    void SetYPix(int yTmp);
    void LoadFrame(SDL_Surface *&frame, string name);
    virtual void UpdateAnimation() {}
};

#endif // OBJECT_H
