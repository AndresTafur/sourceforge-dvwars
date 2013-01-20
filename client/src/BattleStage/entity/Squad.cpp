#include <entity/Squad.h>
#include <entity/Game.h>

int Squad::mSquadCount = 0;


Squad::Squad(unsigned int id, unsigned short owner, unsigned int speed)
{
  GameObject  *wshop;
  Ogre::Vector3 pos;

            mID      = id;
            mOwner   = owner;
            wshop    = (owner == 1)?Game::getInstancePtr()->getWorkShop1() : Game::getInstancePtr()->getWorkShop2();
            mPos     = wshop->getNode()->getPosition();
            mSpeed   = speed;

  }


    void Squad::addUnit(Unit *obj)
    {
        obj->setPosition(mPos+Ogre::Vector3(mUnits.size()*10,40,10*mSquadCount));
        obj->setSpeed(mSpeed);
        obj->getEntity()->setUserAny( Ogre::Any(this));
        mUnits.insert( std::make_pair<size_t,Unit*>(obj->getID(),obj));
    }


    void Squad::setSelected(bool val)
    {
       std::map<size_t,Unit*>::iterator it;

        for ( it=mUnits.begin() ; it != mUnits.end(); it++ )
                (*it).second->getSceneNode()->showBoundingBox(val);
    }



    Unit* Squad::getUnit(size_t id)
    {
      std::map<size_t,Unit*>::iterator iter;

            iter =  mUnits.find(id);

            if( iter != mUnits.end())
                  return iter->second;

            return NULL;
    }


Squad::~Squad()
{
    //dtor
}
