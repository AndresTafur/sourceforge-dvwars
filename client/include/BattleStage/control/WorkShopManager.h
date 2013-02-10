#ifndef _WORKSHOPMANAGER_H
#define _WORKSHOPMANAGER_H


#include <Ogre.h>
#include <queue>

#include <BattleStage/entity/Game.h>
#include <BattleStage/entity/Building.h>
#include <BattleStage/entity/WorkShop.h>

#include <BattleStage/control/SelectionManager.h>
#include <BattleStage/control/CreationListener.h>

#include <util/Cripto.h>
#include <util/SingletonContainer.h>

#include <engine/AbstractClient.h>
#include <engine/SelectionListener.h>




/**
 * handles workshop request healing, creation, etc) and events.
 */

class WorkShopManager : public ClientListener, public Ogre::FrameListener
{
public:

        WorkShopManager();

        /**
         *  Request a new squad cretion to the server.
         *
         *  @param type squad to be created.
         *  @see SquadBuilder
         */

        void requestBuildingCreation(std::string type);


        void requestCreationTarget(Ogre::Vector3 target);


        void attend(std::vector<std::string> &data);


        bool frameRenderingQueued(const Ogre::FrameEvent &evt);


        void addCreationListener(CreationListener *obj);


        virtual ~WorkShopManager();

protected:


private:

Ogre::SceneManager    *mScnMgr;
Ogre::Camera          *mCamera;

///Ogre entity with material for workshop.
WorkShop              *mWorkShop;
WorkShop              *mWorkShop2;
Building              *mBuilding;

std::vector<CreationListener*> mListeners;
std::queue< std::vector<std::string> > mParams;
};

#endif // _WORKSHOPMANAGER_H
