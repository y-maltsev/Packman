#ifndef GHOST_H
#define GHOST_H
#include "MovingObject.h"

class Ghost: public MovingObject
{
protected:
    int startX,startY;
    int barrierX,barrierY;
    int vulnerableCount; //time when the ghost can be eaten
    int chaseCountDown; //time before ghost starts chasing its target
    bool isInGraveyard,isDead;
    MovingObject* target;

    SDL_Surface* deadFrame1;
    SDL_Surface* deadFrame2;
    SDL_Surface* normalFrame1;
    SDL_Surface* normalFrame2;
    SDL_Surface* vulnerableFrame;
public:
    Ghost(GameWindow *win);
    ~Ghost();
    void Init();
    void Update();
    void UpdateAnimation();

    void SetBarrier();
    void SetStartAndBarrier(int stX,int stY,int barrX, int barrY);
    void SetDead();
    void SetInGraveyard();
    void SetVulnerable(int time);
    void SetGhostType(int type);
    void SetTarget(MovingObject* targetTmp);
    bool IsVulnerable();
    void SetVulnerableFor(int time);
    void ReverseDirection();
    bool IsColidingWithMap(int xTmp, int yTmp);

    void GenerateRandomDirection();

    void ChageDirToTarget(int xTmp, int yTmp); //A* algorithm that changes dir according to the found path
    int CDTT_Heuristic(int StartMapIndex, int GoalMapIndex); // ChageDirToTarget Heuristic
    int CDTT_GetMapIndex(int xTmp, int yTmp); // ChageDirToTarget helper function for easier map cordinate to map index calculations
    vector<int> CDTT_ReconstructPath(map<int,int> &ComeFrom, int current); // path reconstruction of A*
    vector<int> CDTT_GetNeightbors(int mapIndexTmp); // get all neighbors but not the "previous" step of the ghost and get the barrier when Dead
    bool CDTT_GN_IsValid(int xTmp,int yTmp); // is xTmp yTmp a valid Neighbor


};

#endif // GHOST_H
