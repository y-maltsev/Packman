#ifndef MOVINGOBJECT_H
#define MOVINGOBJECT_H
#include "Object.h"

class MovingObject: public Object
{
protected:
    int *iMap;
    unsigned mapWidth,mapHeight;
    unsigned mapCellSize; //cell size of the map in pixels
    int x,y; // position on the map:  x = Math.Floor(xPix/cellSize)
    int dx,dy; // moving direction
    float xFloat,yFloat; //actual cordinates
    float speedMult;
public:
    MovingObject(GameWindow *win);
    ~MovingObject();
    virtual bool IsColidingWithMap(unsigned xTmp, unsigned yTmp);
    void Init();
    void SetMap(int* mapTmp, int mapW,int mapH, int cellSize, int xTmp, int yTmp);
    int GetX();
    int GetY();
    void RemoveMap();

};

#endif // MOVINGOBJECT_H
