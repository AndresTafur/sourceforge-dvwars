#ifndef _GAMESTATICOBJECT_H_
#define _GAMESTATICOBJECT_H_

#include <Ogre.h>

class GameStaticObjectBatch
{
public:

        GameStaticObjectBatch(Ogre::StaticGeometry *geom);

        GameStaticObjectBatch();


        Ogre::StaticGeometry* getStaticGeometry();

        virtual ~GameStaticObjectBatch();

private:
Ogre::StaticGeometry *mStaticGeom;
};

#endif // _GAMESTATICOBJECT_H_
