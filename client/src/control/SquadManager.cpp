#include "SquadManager.h"

#include <entity/Game.h>

SquadManager::SquadManager()
{
        mScnMgr    = Ogre::Root::getSingletonPtr()->getSceneManager("MainManager");
        mCamera    = mScnMgr->getCamera("RTSCam");
        mSqBuilder = new SquadBuilder();

        mSelected  = NULL;
        SelectionManager::getInstance()->addSelectionListener(this);

}

        void SquadManager::onSelection(Ogre::MovableObject* ent,  OIS::MouseButtonID id)
        {
          Squad *squad;


                if( ent->getName().find("_Unit") != std::string::npos )
                {
                    squad = Ogre::any_cast<Squad*>(ent->getUserAny());

                    if(squad->getOwner() == Game::getInstancePtr()->getActivePlayer() )
                    {
                        ent->getParentSceneNode()->showBoundingBox(true);
                        mSelected = squad;
                        std::cerr << "MovableObject: " << ent->getName()  << std::endl;
                    }
                }
        }

        void SquadManager::onWorldSelection(Ogre::SceneQuery::WorldFragment * ent,  OIS::MouseButtonID id)
        {
          char buff[100];

            if( id == OIS::MB_Right and mSelected )
            {
                 sprintf(buff,"710|%i|%f&%f",mSelected->getID(), ent->singleIntersection.x, ent->singleIntersection.z  );
                 Client::getInstancePtr()->Send( buff );
            }

            if( id == OIS::MB_Left and mSelected != NULL )
            {
                mSelected->setSelected(false);
                mSelected = NULL;
            }


        }


        void SquadManager::createSquad(std::string type, int id, unsigned short owner, int size, unsigned int speed)
        {
          Squad *squad = mSqBuilder->createSquad(type, id, owner, size, speed);

                mSquads.insert( std::make_pair<int,Squad*>(id,squad)  );
        }


        Squad* SquadManager::getSquad(unsigned int idSquad)
        {
          std::map<int, Squad*>::iterator iter;

                    iter = mSquads.find(idSquad);

                    if( iter !=  mSquads.end() )
                        return iter->second;

                return NULL;
        }

SquadManager::~SquadManager()
{
    //dtor
}
