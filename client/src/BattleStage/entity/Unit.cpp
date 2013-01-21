#include "BattleStage/entity/Unit.h"

Unit::Unit(Ogre::Entity *obj, size_t id)
{
    mEntity  = obj;
    mObject  = Ogre::Root::getSingleton().getSceneManager("MainManager")->getRootSceneNode()->createChildSceneNode();
    mId      = id;
    mSpeed   = 0;

    mObject->attachObject(mEntity);

    setPosition( Ogre::Vector3(0,0,0));
}


        void Unit::setPosition( Ogre::Vector3 pos)
        {
            if(!mFlyable)
            {
                Ogre::SceneManager  *mgr = Ogre::Root::getSingletonPtr()->getSceneManager("MainManager");
                Ogre::RaySceneQuery *raySceneQuery = mgr->createRayQuery( Ogre::Ray( Ogre::Vector3(0,0,0), Ogre::Vector3::NEGATIVE_UNIT_Y));
                Ogre::RaySceneQueryResult::iterator it;
                Ogre::RaySceneQueryResult qryResult;

                        pos.y = 0;
                        raySceneQuery->setRay( Ogre::Ray(pos, Ogre::Vector3::UNIT_Y) );
                        qryResult = raySceneQuery->execute();

                        it = qryResult.begin();

                        if (it != qryResult.end() && it->worldFragment)
                        pos.y =  it->worldFragment->singleIntersection.y+mObject->getScale().y*10;
            }
            else
                pos.y = 20;

            mObject->setPosition(pos);
        }



        Ogre::Vector3 Unit::getPosition()
        {
            return  mObject->getPosition();
        }


        void Unit::orientate(Ogre::Vector3 pos)
        {
          Ogre::Quaternion quat;
          Ogre::Vector3  src;


                    src  = mObject->getOrientation() * Ogre::Vector3::UNIT_X;
                    quat = src.getRotationTo(pos);
                    mObject->rotate(quat);
        }


Unit::~Unit()
{
    //dtor
}
