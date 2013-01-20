#include "SelectionManager.h"


SelectionManager* SelectionManager::smInstance = 0;


SelectionManager::SelectionManager()
{
       mScnMgr  = Ogre::Root::getSingletonPtr()->getSceneManager("MainManager");
       mCamera  = mScnMgr->getCamera("RTSCam");
       InputSystem::getInstancePtr()->addMouseListener(this);
}


        SelectionManager* SelectionManager::getInstance()
        {
                if(!smInstance)
                    smInstance = new SelectionManager();
                return smInstance;
        }



        bool SelectionManager::mouseMoved( const OIS::MouseEvent &e )
        {
                return true;
        }

        bool SelectionManager::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id)
        {
                return true;
        }



        bool SelectionManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id)
        {
            Ogre::RaySceneQuery* mRayScnQuery = mScnMgr->createRayQuery( mCamera->getCameraToViewportRay( e.state.X.abs/float(e.state.width), e.state.Y.abs/float(e.state.height))  );
            Ogre::RaySceneQueryResult &result = mRayScnQuery->execute();
            Ogre::RaySceneQueryResult::iterator itr;
            std::list<SelectionListener*>::iterator iter;


                        mRayScnQuery->setQueryTypeMask(Ogre::SceneManager::ENTITY_TYPE_MASK);
                        mRayScnQuery->setSortByDistance(true);


                        //TODO: set 2 std::list one for tiles and another for entities, register SquadManager in both (in terrain only if a batch has been selected)
                        for ( itr = result.begin( ); itr != result.end(); itr++ )
                        {
                                if ( itr->worldFragment )
                                {
                                    for(iter = mObservers.begin(); iter != mObservers.end(); iter++)
                                            (*iter)->onWorldSelection(itr->worldFragment,id);
                                }

                                else if ( itr->movable  &&  itr->movable->getName().find("tile") == std::string::npos )
                                {
                                    fprintf(stderr,"Selected:  %s", itr->movable->getName().c_str() );

                                    if( itr->movable->getName() == "MiniMapCamera" )
                                        continue;

                                    for(iter = mObservers.begin(); iter != mObservers.end(); iter++ )
                                            (*iter)->onSelection(itr->movable,id);
                                    break;
                                }
                        }
                       delete mRayScnQuery;

                return true;
        }




SelectionManager::~SelectionManager()
{
    //dtor
}
