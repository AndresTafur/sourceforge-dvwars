#include "CreateAction.h"

CreateAction::CreateAction(SquadManager  *squadMgr)
{
    mSquadMgr = squadMgr;
}


        bool CreateAction::execute(const Ogre::FrameEvent &evt)
        {
          unsigned int   batchId;
          unsigned int   size;
          unsigned int   speed;
          unsigned short owner;


                batchId = atoi(mParams[2].c_str());
                owner   = atoi(mParams[3].c_str());
                size    = atoi(mParams[4].c_str());
                speed   = atoi(mParams[5].c_str());

                mSquadMgr->createSquad(mParams[1], batchId, owner, size, speed);
                Client::getInstancePtr()->Send( "502"   );
            return true;
        }


        void CreateAction::addParams(std::vector<std::string> params)
        {
            mParams   = params;
            mObjectId = mParams[2];
        }

        Action* CreateAction::clone()
        {
            return new CreateAction(mSquadMgr);
        }

        std::string CreateAction::getObjectId()
        {
            return mObjectId;
        }


CreateAction::~CreateAction()
{
    //dtor
}
