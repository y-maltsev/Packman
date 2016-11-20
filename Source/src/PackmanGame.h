#ifndef PACKMANGAME_H
#define PACKMANGAME_H
#include "main.h"
#include "GameState.h"
#include "Packman.h"
#include "Ghost.h"
#include "Bonus.h"
#include "PackmanUI.h"

class PackmanGame: public GameState
{

protected:
    static Packman* packman;
    vector<Ghost*> ghosts;
    vector<Bonus*> bonuses;
    PackmanUI* packmanUI;
    int* iMap;
    int cellSize,mapWidth,mapHeight;
    bool isPaused;
public:
    PackmanGame(GameWindow *win);
    ~PackmanGame();
    GameState* OnUpdate();
    void Render();
    void HandleEvents();
    void OnLeave();
    void OnEnter();
    void ResetPackmanAndGhostsPositions();
};


#endif // PACKMANGAME_H
