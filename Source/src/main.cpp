#include "main.h"
#include "GameWindow.h"
#include "GameStateMachine.h"
#include "PackmanGame.h"

int main( int argc, char* args[] )
{
    GameWindow window;
    GameStateMachine stateMachine;
    PackmanGame* packman = new PackmanGame(&window);
    stateMachine.ChangeState(packman);

    bool isGameRunning = true;
    DWORD lastTime= GetTickCount();
    srand ( time(NULL) );
    while(isGameRunning) //Main loop
    {

        stateMachine.HandleEvents();

        DWORD currentTime = GetTickCount();
        while( currentTime - lastTime >= window.GetTimePerTick())
        {
            isGameRunning = stateMachine.Update();
            lastTime += window.GetTimePerTick();
        }

        stateMachine.Render();
    }

    return 0;
}
