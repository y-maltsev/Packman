#ifndef BONUS_H
#define BONUS_H
#include "Object.h"

class Bonus: public Object
{
protected:
    int type;
    SDL_Surface *pill1,*pill2,*pill3;
public:
    Bonus(GameWindow *win);
    ~Bonus();
    void Init();
    void Update();
    void UpdateAnimation();
    void InitType(int typeTmp);
    int GetType();

};

#endif // BONUS_H
