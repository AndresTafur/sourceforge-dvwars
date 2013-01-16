#include "BoidObstacle.h"



BoidObstacle::BoidObstacle()
{

}

BoidObstacle::BoidObstacle(int x, int y)
{
    mPosition = Vector2(x,y);
}


    Vector2 BoidObstacle::getPosition()
    {
        return mPosition;
    }


    void BoidObstacle::setPosition(Vector2 pos)
    {
        mPosition = pos;
    }
