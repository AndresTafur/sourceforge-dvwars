#include "MoveAction.h"

MoveAction::MoveAction(SquadManager  *squadMgr)
{
    mSquadMgr = squadMgr;
    mDisp = 0;
    mAnim = NULL;

}


        bool MoveAction::execute(const Ogre::FrameEvent &evt)
        {
          Ogre::Vector3 prev, cur, final;


                    final = mFinalPos.front();
                    prev  = mUnit->getPosition();

                    if( mDisp.length() == 0)
                    {
                        mDisp   = final - prev;
                        mDisp.y = 0;
                        mDisp.normalise();
                    }

                    cur   = prev + mDisp * (mUnit->getSpeed()*evt.timeSinceLastFrame);


                    mUnit->orientate(final);
                    mUnit->setPosition(cur);

                    if( mAnim )
                        mAnim->addTime(evt.timeSinceLastFrame);


                    prev   = final - cur;
                    prev.y = 0;

                    if( prev.length() <= 5)
                    {
                        mFinalPos.pop();
                        mDisp = 0;

                        if( mFinalPos.empty() )
                            return true;

                    }
            return false;
        }



        void MoveAction::addParams(std::vector<std::string> params)
        {
          Squad *squad;
          float coordX, coordZ;
          Ogre::Vector3 dest;
          unsigned int  idUnit, idSquad;


                mParams   = params;
                mObjectId = mParams[1]+mParams[2];

                idUnit    = atoi( mParams[2].c_str() );
                idSquad   = atoi( mParams[1].c_str() );

                coordX    = atoi(mParams[3].substr(0, mParams[3].find ('&') ).c_str());
                coordZ    = atoi(mParams[3].substr(mParams[3].find ('&')+1).c_str());

                squad     = mSquadMgr->getSquad(idSquad);
                mUnit     = squad->getUnit(idUnit);

                dest      = Ogre::Vector3(coordX,0,coordZ);

                if( mFinalPos.size() > 0 && mFinalPos.back() == dest )
                {
                    fprintf(stderr,"action exists, aborting.\n");
                    return;
                }

                try
                {
                        mAnim =  mUnit->getAnimation("Walk");
                        mAnim->setLoop(true);
                        mAnim->setEnabled(true);


                }
                catch(Ogre::ItemIdentityException ex)
                {
                    std::cerr << "No Caminar animation found"<<std::endl;
                }
                mFinalPos.push(dest);
        }


        std::string MoveAction::getObjectId()
        {
            return mObjectId;
        }


        Action* MoveAction::clone()
        {
            return new MoveAction(mSquadMgr);
        }



MoveAction::~MoveAction()
{
        fprintf(stderr,"Action %s Finished, destroying\n",mObjectId.c_str());
}
