#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "GameWindow.h"

class GameState
{
protected:
    GameWindow* window; //for rendering
    bool terminateState;
public:
    GameState(GameWindow* win,bool terSt = false): window(win),terminateState(terSt) {}
    virtual ~GameState() {}
    virtual GameState* OnUpdate() = 0;
    virtual void Render() = 0;
    virtual void HandleEvents() = 0;
    virtual void OnLeave() = 0;
    virtual void OnEnter() = 0;
};

#endif // GAMESTATE_H
