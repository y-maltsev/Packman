#include "GameStateMachine.h"

GameStateMachine::GameStateMachine():currentState(NULL)
{
}

GameStateMachine::~GameStateMachine()
{
    if(currentState != NULL)
        delete currentState;
}

bool GameStateMachine::Update()
{
    GameState* nextState = currentState->OnUpdate();
    if(nextState == NULL)
        return false;
    if(nextState != currentState)
        ChangeState(nextState);
    return true;
}

void GameStateMachine::Render()
{
    currentState->Render();
}

void GameStateMachine::HandleEvents()
{
    currentState->HandleEvents();
}

void GameStateMachine::ChangeState(GameState* state)
{
    if(currentState != NULL)
    {
        currentState->OnLeave();
        delete currentState;
    }
    currentState = state;
    currentState->OnEnter();
}


