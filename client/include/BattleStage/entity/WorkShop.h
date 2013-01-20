#ifndef _WORKSHOP_H_
#define _WORKSHOP_H_

#include <DaVinciGlobals.h>
#include <entity/Building.h>
#include <entity/GameObject.h>


/**
 * Workshop ogre entity.
 */
class WorkShop : public GameObject
{
public:

         WorkShop(unsigned int player, Ogre::SceneManager *sceneMgr, Ogre::String mesh, std::string name);

         /**
          * Recalculates position to attach a building to this workshop
          * @param bld Building to be attached.
          */
         void attachBuilding(Building *bld);

         virtual ~WorkShop();

private:
unsigned short mAttached;
std::vector<Ogre::Vector3> mAttachPos;
};

#endif // _WORKSHOP_H_
