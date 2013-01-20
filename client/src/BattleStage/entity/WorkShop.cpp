#include "WorkShop.h"


WorkShop::WorkShop(unsigned int player, Ogre::SceneManager *sceneMgr, Ogre::String mesh, std::string name) : GameObject(player, sceneMgr, mesh, name)
{
    mAttachPos.push_back(Ogre::Vector3(0,0,50));
    mAttachPos.push_back(Ogre::Vector3(50,0,0));
    mAttachPos.push_back(Ogre::Vector3(0,0,-50));
    mAttachPos.push_back(Ogre::Vector3(-50,0,0));

    mAttached = 0;
    this->getNode()->setDirection(0,0,1);
    this->getEntity()->setQueryFlags(TYPE_WORKSHOP);
    this->getEntity()->setUserAny( Ogre::Any(this) );
}


        void WorkShop::attachBuilding(Building *bld)
        {
                if( mAttached == 4)
                    return; //TODO:Throw no more buildings

                bld->setPosition( this->getNode()->getPosition() + mAttachPos[mAttached] );
                bld->getNode()->scale(5,5,5);
                bld->getEntity()->setQueryFlags(TYPE_BUILDING);

            mAttached++;
        }


WorkShop::~WorkShop()
{
    //dtor
}
