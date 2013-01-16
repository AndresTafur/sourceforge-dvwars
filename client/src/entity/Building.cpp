#include "Building.h"

Building::Building( unsigned int player, Ogre::SceneManager *sceneMgr, Ogre::String mesh, std::string name) : GameObject(player, sceneMgr, mesh, name )
{
    this->getEntity()->setQueryFlags(TYPE_BUILDING);
    this->getEntity()->setUserAny( Ogre::Any(this));
}

Building::~Building()
{
    //dtor
}
