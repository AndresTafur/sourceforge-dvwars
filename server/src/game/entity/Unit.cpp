#include "entity/Unit.h"
#include "entity/Squad.h"
#include "entity/Game.h"

Unit::Unit(unsigned long id, Squad *sqd) : Boid()
{
        mID    = id;
        mSquad = sqd;
}


    Vector2 Unit::getVelocity()
    {
        return mVelocity;
    }


    void Unit::setVelocity(Vector2 vel)
    {
            mVelocity = vel;
    }


    void Unit::setPosition(Vector2 pos)
    {
       char buff[100];
       Game *gm;
       int x,y, oldx, oldy;

                x = int(pos.mXcoord);
                y = int(pos.mYcoord);

                oldx = int(mPos.mXcoord);
                oldy = int(mPos.mYcoord);

                mPos = pos;

                mContext->mDomainMatrix[oldx][oldy] = 0;
                mContext->mDomainMatrix[x][y] = -1;

                sprintf(buff,"710|%i|%li|%i&%i", mSquad->getID(), mID, x, y);
                fprintf(stderr,"%s\n",buff);
                gm = mSquad->getGame();
                gm->sendMulticast(buff);
    }



Unit::~Unit()
{

}
