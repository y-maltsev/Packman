#ifndef GAMESTATEMACHINE_H
#define GAMESTATEMACHINE_H
#include "GameState.h"

class GameStateMachine
{
    GameState* currentState;
public:
    GameStateMachine();
    ~GameStateMachine();
    bool Update();
    void Render();
    void HandleEvents();
    void ChangeState(GameState *state);

};

#endif // GAMESTATEMACHINE_H
