#include "MovingObject.h"

MovingObject::MovingObject(GameWindow *win): Object(win)
{
    //ctor
}

MovingObject::~MovingObject()
{
    //dtor
}

bool MovingObject::IsColidingWithMap(unsigned xTmp, unsigned yTmp)
{
    if(mapCellSize==1) return 0;
    if (xTmp < 0 || xTmp >= mapWidth || yTmp < 0 || yTmp >= mapHeight ) return 0;
    //collision detection
    if ( iMap[ yTmp * mapWidth + xTmp ] == 0)
        return 1;
    return 0;
}

void MovingObject::Init()
{
    Object::Init();
    RemoveMap();
    x = 0;
    y = 0;
    dx = 0;
    dy = 0;
    xFloat = 0.0f;
    yFloat = 0.0f;
    speedMult = 4.0f;
}

void MovingObject::SetMap(int* mapTmp, int mapW,int mapH, int cellSize, int xTmp, int yTmp)
{
    iMap = mapTmp;
    mapWidth = mapW;
    mapHeight = mapH;
    mapCellSize = cellSize;
    x = xTmp;
    y = yTmp;
    xPix = x*mapCellSize;
    yPix = y*mapCellSize;
    xFloat = (float)xPix;
    yFloat = (float)yPix;
}
int MovingObject::GetX()
{
    return x;
}
int MovingObject::GetY()
{
    return y;
}

void MovingObject::RemoveMap()
{
    iMap = NULL;
    mapWidth = 0;
    mapHeight = 0;
    mapCellSize = 1;

}
