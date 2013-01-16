#include "GameStaticObjectBatch.h"

GameStaticObjectBatch::GameStaticObjectBatch(Ogre::StaticGeometry *geom)
{
    mStaticGeom = geom;
}

GameStaticObjectBatch::GameStaticObjectBatch()
{


}

        Ogre::StaticGeometry* GameStaticObjectBatch::getStaticGeometry()
        {
            return mStaticGeom;
        }


GameStaticObjectBatch::~GameStaticObjectBatch()
{
    //dtor
}
