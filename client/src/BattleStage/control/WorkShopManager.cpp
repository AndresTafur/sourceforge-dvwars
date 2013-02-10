#include "WorkShopManager.h"



WorkShopManager::WorkShopManager()
{
    /*
        mScnMgr    = Ogre::Root::getSingletonPtr()->getSceneManager("MainManager");
        mCamera    = mScnMgr->getCamera("RTSCam");
        mWorkShop  = NULL;
        mWorkShop2 = NULL;
        mBuilding  = NULL;
*/
        SingletonContainer::getInstancePtr()->getObject<AbstractClient*>("client")->addListener(this);
        Ogre::Root::getSingletonPtr()->addFrameListener(this);
}


        void WorkShopManager::attend(std::vector<std::string> &data)
        {
                if( data[0] == "501" )
                {
                    for(size_t iter = 0; iter <   mListeners.size(); iter++)
                            mListeners[ iter ]->onProgressUpdate( atoi(data[2].c_str())  );
                }
                else if( data[0] == "500")
                {
                   mParams.push(data);
                }
                else if( data[0] == "702" )
                {
                        mBuilding = new Building( atoi(data[3].c_str()), mScnMgr, data[2]) ;
                        mBuilding->setName(data[1]);

                        for(unsigned int iter = 0; iter < mListeners.size(); iter++ )
                            mListeners[iter]->onCreateBuilding(mBuilding);

                        mParams.push(data);
                }
        }


        bool WorkShopManager::frameRenderingQueued(const Ogre::FrameEvent &evt)
        {/*
           int coordX, coordZ;
           std::vector<std::string> params;
           Ogre::Vector3 pos;

                    if(mParams.empty())
                        return true;

                    params = mParams.front();
                    mParams.pop();

                    if( params[0] == "500"  )
                    {
                            if( params[1] == "1" && !mWorkShop)
                            {
                                mWorkShop  = new WorkShop( atoi(params[2].c_str()), mScnMgr, params[2], params[2]+params[1]);

                                coordX     = atoi(params[3].substr(0, params[3].find ('&') ).c_str());
                                coordZ     = atoi(params[3].substr(params[3].find ('&')+1 ).c_str());

                                mWorkShop->setPosition( Ogre::Vector3(coordX,0,coordZ));
                                mWorkShop->getNode()->scale(7,7,7);
                                mWorkShop->setOwner(1);

                                Game::getInstancePtr()->setWorkShop1(mWorkShop);
                            }
                            else if( params[1] == "2" && !mWorkShop2 )
                            {
                                mWorkShop2 = new WorkShop( atoi(params[2].c_str()), mScnMgr, params[2], params[2]+params[1]);

                                coordX     = atoi(params[3].substr(0, params[3].find ('&') ).c_str());
                                coordZ     = atoi(params[3].substr(params[3].find ('&')+1 ).c_str());

                                mWorkShop2->setPosition( Ogre::Vector3(coordX,0,coordZ));
                                mWorkShop2->getNode()->scale(7,7,7);
                                mWorkShop2->setOwner(2);

                                Game::getInstancePtr()->setWorkShop2(mWorkShop2);

                                pos   = Game::getInstancePtr()->getActivePlayer() == 1 ? mWorkShop->getNode()->getPosition() : mWorkShop2->getNode()->getPosition();
                                pos.y = mCamera->getPosition().y;
                                mCamera->move(  pos  );
                            }
                    }
                    if( params[0] == "702" and mBuilding != NULL)
                    {
                       int user;

                            user = mBuilding->getOwner();

                            if(user == 1)
                                mWorkShop->attachBuilding(mBuilding);
                            else
                                mWorkShop2->attachBuilding(mBuilding);
                    }*/

            return true;
        }


        void WorkShopManager::addCreationListener(CreationListener *obj)
        {
            mListeners.push_back(obj);
        }



        void WorkShopManager::requestBuildingCreation(std::string type)
        {
            SingletonContainer::getInstancePtr()->getObject<AbstractClient*>("client")->Send( "702|"+type );
        }


        void WorkShopManager::requestCreationTarget(Ogre::Vector3 target)
        {
          char locStr[100];

                sprintf(locStr,"503|%f&%f", target.x,target.z);
                SingletonContainer::getInstancePtr()->getObject<AbstractClient*>("client")->Send( locStr );
        }


WorkShopManager::~WorkShopManager()
{
   SingletonContainer::getInstancePtr()->getObject<AbstractClient*>("client")->removeListener(this);
   delete mWorkShop;
}
