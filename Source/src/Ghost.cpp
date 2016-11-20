#include "Ghost.h"

Ghost::Ghost(GameWindow *win):  MovingObject(win),
    deadFrame1(NULL),deadFrame2(NULL),
    normalFrame1(NULL), normalFrame2(NULL),
    vulnerableFrame(NULL)

{
    Init();
}

Ghost::~Ghost()
{
    SDL_FreeSurface(deadFrame1);
    SDL_FreeSurface(deadFrame2);
    SDL_FreeSurface(normalFrame1);
    SDL_FreeSurface(normalFrame2);
    SDL_FreeSurface(vulnerableFrame);
}

void Ghost::Init()
{
    MovingObject::Init();

    SetGhostType(0);

    LoadFrame(deadFrame1,"Media/GhostDead1.bmp");
    LoadFrame(deadFrame2,"Media/GhostDead2.bmp");
    LoadFrame(vulnerableFrame,"Media/VulnerableGhost.bmp");

    currentFrame = normalFrame1;

    dx=1;
    dy=0;
    vulnerableCount = 0;
    isInGraveyard=true;
    isDead=false;
    startX=x;
    startY=y;
    target = NULL;

}

void Ghost::Update()
{
    int oldx, oldy;

    //remember old coords for adjustments at end
    oldx=xPix;
    oldy=yPix;


    //if node is reached
    if ( xPix%mapCellSize == 0 && yPix%mapCellSize == 0 )
    {
        if(isDead)
        {
            //graveyard reached
            if(x == startX && y == startY)
            {
                isDead = false;
                vulnerableCount = 0;
                GenerateRandomDirection();
                isInGraveyard = true;
                speedMult = 4.0f;
            }
            else //go to graveyard
            {
                ChageDirToTarget(startX,startY);
            }
        }
        else //"chase" target
        {
            chaseCountDown--;
            if(chaseCountDown>0 || vulnerableCount > 0)
            {
                GenerateRandomDirection();
            }
            else
            {
                ChageDirToTarget(target->GetX(),target->GetY());
            }
        }

        //close barrier after exiting graveyard
        if(isInGraveyard && x == barrierX && y == barrierY) isInGraveyard = false;
    }

    //MOVEMENT PART STARTS HERE

    //  dir    *       speed
    xFloat +=  (float)( dx * speedMult ) ;
    yFloat +=  (float)( dy * speedMult ) ;


    //COORD ADJUSTMENTS

    if ( xFloat > (float)(x+1)*mapCellSize ) xFloat = (float)(x+1)*mapCellSize;
    if ( yFloat > (float)(y+1)*mapCellSize ) yFloat = (float)(y+1)*mapCellSize;

    if ( xFloat < (float)(x)*mapCellSize && oldx > (float)(x)*mapCellSize )
        xFloat = (float)(x)*mapCellSize;
    if ( yFloat < (float)(y)*mapCellSize && oldy > (float)(y)*mapCellSize)
        yFloat = (float)(y)*mapCellSize;

    //COORD UPDATES

    xPix=(int)xFloat;
    yPix=(int)yFloat;

    x= xPix/mapCellSize;
    y= yPix/mapCellSize;

    UpdateAnimation();
}

void Ghost::UpdateAnimation()
{
    animationCount++;
    if(animationCount>20) animationCount = 0;
    if(isDead)
    {
        if(animationCount/10 == 0)  currentFrame = deadFrame1;
        else currentFrame = deadFrame2;
    }
    else if(vulnerableCount>0)
    {
        if(vulnerableCount<50)
        {
            if(animationCount/10 == 0) currentFrame = vulnerableFrame;
            else currentFrame = normalFrame1;
        }
        else
        {
            currentFrame = vulnerableFrame;
        }
        vulnerableCount--;
        if(vulnerableCount==0) speedMult=4.0f;
    }
    else
    {
        if(animationCount/10 == 0) currentFrame = normalFrame1;
        else currentFrame = normalFrame2;
    }
}

void Ghost::GenerateRandomDirection()
{
    vector<int> possibleMoves;//1 - left, 2 - right, 3 -up, 4 - down
    int result;

    if(!IsColidingWithMap(x+1, y) && !(dx==-1))
    {
        possibleMoves.push_back(1);
    }
    if(!IsColidingWithMap(x-1, y) && !(dx==1))
    {
        possibleMoves.push_back(2);
    }
    if(!IsColidingWithMap(x, y+1) && !(dy==-1))
    {
        possibleMoves.push_back(3);
    }
    if(!IsColidingWithMap(x, y-1) && !(dy==1))
    {
        possibleMoves.push_back(4);
    }

    result = possibleMoves[rand()%(possibleMoves.size())];
    if(result == 1)
    {
        dx = 1;
        dy = 0;
        return;
    }
    if(result == 2)
    {
        dx = -1;
        dy = 0;
        return;
    }
    if(result == 3)
    {
        dx = 0;
        dy = 1;
        return;
    }
    if(result == 4)
    {
        dx = 0;
        dy = -1;
        return;
    }
}



void Ghost::SetStartAndBarrier(int stX,int stY,int barrX, int barrY)
{
    startX=stX;
    startY=stY;
    barrierX=barrX;
    barrierY=barrY;
}

void Ghost::SetDead()
{
    isDead = true;
    speedMult = 4.0f;
}

void Ghost::SetInGraveyard()
{
    isInGraveyard = true;
}

void Ghost::SetVulnerable(int time)
{
    vulnerableCount = time;
    speedMult = 2.0f;
    dx = -dx;
    dy = -dy;
}

void Ghost::SetGhostType(int type)
{
    if(type == 0)
    {
        LoadFrame(normalFrame1,"Media/GhostR1.bmp");
        LoadFrame(normalFrame2,"Media/GhostR2.bmp");
    }
    else if(type == 1)
    {
        LoadFrame(normalFrame1,"Media/GhostP1.bmp");
        LoadFrame(normalFrame2,"Media/GhostP2.bmp");
    }
    else if(type == 2)
    {
        LoadFrame(normalFrame1,"Media/GhostG1.bmp");
        LoadFrame(normalFrame2,"Media/GhostG2.bmp");
    }
    else
    {
        LoadFrame(normalFrame1,"Media/GhostB1.bmp");
        LoadFrame(normalFrame2,"Media/GhostB2.bmp");
    }

    chaseCountDown = 10*25*(type+1); // 10 seconds * tickrate * type
}

void Ghost::SetTarget(MovingObject *targetTmp)
{
    target = targetTmp;
}
bool Ghost::IsVulnerable()
{
    bool result = (vulnerableCount > 0);
    return result;
}

void Ghost::SetVulnerableFor(int time)
{
    vulnerableCount = time;
}


bool Ghost::IsColidingWithMap(int xTmp, int yTmp)
{
    if((isInGraveyard || isDead) && xTmp==barrierX && yTmp==barrierY) return 0;
    else return MovingObject::IsColidingWithMap(xTmp,yTmp);
}

//A* algorithm that changes dir according to the found path
void Ghost::ChageDirToTarget(int xTmp, int yTmp)
{
    vector<int> closedSet;
    vector<int> openSet;
    std::map<int,int> gScore;
    std::map<int,int> fScore;
    std::map<int,int> cameFrom;

    int current;
    vector<int> neighbors;
    int tentative_gScore;

    int GhostMapIndex = CDTT_GetMapIndex(x,y);
    int GoalMapIndex = CDTT_GetMapIndex(xTmp,yTmp);
    openSet.push_back(GhostMapIndex);
    gScore[GhostMapIndex] = 0;
    fScore[GhostMapIndex] = CDTT_Heuristic(GhostMapIndex,GoalMapIndex);

    vector<int> path;

    while(!openSet.empty())
    {

        //find minimal fScore element from the openSet
        vector<int>::iterator foundElement = openSet.begin(); // to not go through the loop twice when erasing it
        current = *foundElement;
        for(vector<int>::iterator it = openSet.begin()+1; it != openSet.end(); ++it)
        {
            if(fScore[*it] < fScore[current])
            {
                current = *it;
                foundElement = it;
            }
        }

        openSet.erase(foundElement);
        closedSet.push_back(current);

        if (current == GoalMapIndex)
        {
            path  =  CDTT_ReconstructPath(cameFrom, current);
            break;
        }

        neighbors = CDTT_GetNeightbors(current);
        for(vector<int>::iterator neighbor = neighbors.begin(); neighbor != neighbors.end(); ++neighbor)
        {
            //if such neighbor is already processed - skip it
            if(std::find(closedSet.begin(), closedSet.end(), (*neighbor)) != closedSet.end())
            {
                continue;
            }

            // The distance from start to a neighbor
            tentative_gScore = gScore[current] + 1;

            // Discover if the neighbor its a new or better
            if(!(std::find(openSet.begin(), openSet.end(), (*neighbor)) != openSet.end()))
            {
                openSet.push_back(*neighbor);
            }
            else if (tentative_gScore >= gScore[*neighbor])
            {
                // This is not a better path.
                continue;
            }

            // This path is valid. Record it. If its better than existing, replace it.
            cameFrom[*neighbor] = current;
            gScore[*neighbor] = tentative_gScore;
            fScore[*neighbor] = tentative_gScore + CDTT_Heuristic(*neighbor,GoalMapIndex);
        }
    }
    if(path.size()<2)
    {
        GenerateRandomDirection();
    }
    else
    {
        int nextX=path[path.size()-2]%mapWidth;
        int nextY=path[path.size()-2]/mapWidth;
        dx=nextX-x;
        dy=nextY-y;
    }
}

// ChageDirToTarget Heuristic
int Ghost::CDTT_Heuristic(int StartMapIndex, int GoalMapIndex)
{
    int xResult = abs(StartMapIndex%mapWidth - GoalMapIndex%mapWidth);
    int yResult = abs(StartMapIndex/mapWidth - GoalMapIndex/mapWidth);
    return xResult+yResult;
}

// ChageDirToTarget helper function for easier map cordinate to map index calculations
int Ghost::CDTT_GetMapIndex(int xTmp, int yTmp)
{
    int result = yTmp*mapWidth + xTmp;
    return result;
}

// path reconstruction of A*
vector<int> Ghost::CDTT_ReconstructPath(map<int,int> &ComeFrom, int current)
{
    vector<int> result;
    result.push_back(current);
    map<int,int>::iterator it;
    while( (it = ComeFrom.find(current)) != ComeFrom.end())
    {
        current = it->second;
        result.push_back(current);
    }
    return result;
}

// get all neighbors but not the "previous" step of the ghost and get the barrier when Dead
vector<int> Ghost::CDTT_GetNeightbors(int mapIndexTmp)
{
    vector<int> result;
    int xTmp = mapIndexTmp%mapWidth;
    int yTmp = mapIndexTmp/mapWidth;
    if(CDTT_GN_IsValid(xTmp+1,yTmp))
    {
        result.push_back(CDTT_GetMapIndex(xTmp+1,yTmp));
    }
    if(CDTT_GN_IsValid(xTmp-1,yTmp))
    {
        result.push_back(CDTT_GetMapIndex(xTmp-1,yTmp));
    }
    if(CDTT_GN_IsValid(xTmp,yTmp+1))
    {
        result.push_back(CDTT_GetMapIndex(xTmp,yTmp+1));
    }
    if(CDTT_GN_IsValid(xTmp,yTmp-1))
    {
        result.push_back(CDTT_GetMapIndex(xTmp,yTmp-1));
    }
    return result;
}

bool Ghost::CDTT_GN_IsValid(int xTmp,int yTmp)
{
    bool result = (iMap[CDTT_GetMapIndex(xTmp,yTmp)] != 0) ;
    result = result || ((isDead || isInGraveyard) && xTmp==barrierX && yTmp==barrierY);
    result = result && !( (xTmp == (x - dx)) && (yTmp == (y - dy)) );
    return result;
}
