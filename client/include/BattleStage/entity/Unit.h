#ifndef _UNIT_H
#define _UNIT_H

#include <Ogre.h>


/**
 * Encapsulates an ogre entity contained in a Squad.
 * @see Squad
 */
class Unit
{
public:

        /**
         * Default constructor.
         * Create a Unit (called when Squad initializating).
         *
         * @param obj Object to encapsulate.
         * @see Squad.
         */
        Unit(Ogre::Entity* obj, size_t id);



        /**
         *  Changes the position of the entity within ALL 3d geometry.
         *  @param pos New position, it has to be absoulte coordinates (not batch local).
         */
        void setPosition( Ogre::Vector3 pos);


        void setPosition( Ogre::Vector2 pos);


        void orientate(Ogre::Vector3 pos);


        Ogre::Vector3 getPosition();


        inline Ogre::AnimationState* getAnimation(Ogre::String anim) { return mEntity->getAnimationState(anim);  }


        inline Ogre::SceneNode*  getSceneNode() { return mObject;}

        inline Ogre::Entity*    getEntity() { return mEntity; }

        inline unsigned int getID() { return mId;}

        inline void setSpeed(size_t speed) { mSpeed = speed; }

        inline size_t getSpeed() { return mSpeed; }




        virtual ~Unit();

private:
Ogre::SceneNode *mObject;
Ogre::Entity    *mEntity;
size_t mId;
size_t mSpeed;
bool   mFlyable;
};

#endif // _UNIT_H
