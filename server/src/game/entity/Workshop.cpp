#include "entity/Workshop.h"

Workshop::Workshop(Vector2 coord)
{
    mPosition = coord;
    mTarget   = coord + Vector2(100,100);
}


    void Workshop::setTarget(Vector2 target)
    {
        mTarget = target;
    }



Workshop::~Workshop()
{
    //dtor
}
