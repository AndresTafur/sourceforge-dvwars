#include "NatureAction.h"
#include <Game.h>

NatureAction::NatureAction()
{
    mObjectId = "";
}


        bool NatureAction::execute(const Ogre::FrameEvent &evt)
        {
          Ogre::SceneManager    *mgr   = Ogre::Root::getSingletonPtr()->getSceneManager("MainManager");
          Ogre::RaySceneQueryResult::iterator it;
          Ogre::Entity *ent;

                    if( mFinalize )
                        Game::getInstancePtr()->getObjectBatch( mMesh+"_batch").getStaticGeometry()->build();
                    else
                    {
                            ent       = mgr->createEntity( mMesh  );
                            mPos.y    = 10;
                            Game::getInstancePtr()->getObjectBatch( mMesh+"_batch").getStaticGeometry()->addEntity(ent, mPos );
                     }


            return true;
        }

        Action* NatureAction::clone()
        {
            return new NatureAction();
        }

        std::string NatureAction::getObjectId()
        {
            return mObjectId;
        }

        void NatureAction::addParams(std::vector<std::string> params)
        {
           float coordX, coordZ;

                if(  !mObjectId.empty() )
                        return;

                coordX  = atoi(params[2].substr(0, params[2].find ('&') ).c_str());
                coordZ  = atoi(params[2].substr(params[2].find ('&')+1 ).c_str());
                mMesh   = params[1];
                mPos    = Ogre::Vector3(coordX,0,coordZ);

                mObjectId = params[2];
                mFinalize = coordX < 0 || coordZ < 0;
        }


NatureAction::~NatureAction()
{
    //dtor
}
