#ifndef _SELECTIONLISTENER_
#define _SELECTIONLISTENER_


#include <Ogre.h>

/**
 *  Interface for selections on the 3d world.
 *  @see SelectionManager
 */
class SelectionListener
{
public:

        /**
         *  Called wheter an entity has been selected in the world geometry.
         *  @param obj partial selected object.
         *  @param id  Which mouse button has been pressed.
         */
        virtual void onSelection(Ogre::MovableObject *obj, OIS::MouseButtonID id) = 0;


        /**
         *  Called wheter a tile or static geom has been selected.
         *  @param obj Partial selected world fragment.
         *  @param id  Which mouse button has been pressed.
         */
        virtual void onWorldSelection(Ogre::SceneQuery::WorldFragment *obj, OIS::MouseButtonID id) = 0;

};

#endif
