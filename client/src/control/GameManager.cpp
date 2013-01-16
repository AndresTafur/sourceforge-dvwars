#include "GameManager.h"
#include "GameSound.h"


#include "CreateAction.h"
#include "MoveAction.h"
#include "NatureAction.h"
#include "GoldAction.h"


GameManager::GameManager()
{
  GameSound *sound = new GameSound();

    mSquadMgr = new SquadManager();
    mLock     = false;

    Client::getInstancePtr()->addListener(this);
    Ogre::Root::getSingletonPtr()->addFrameListener(this);



    mFactory.registerAction( new CreateAction(mSquadMgr)  );
    mFactory.registerAction( new MoveAction(mSquadMgr)  );
    mFactory.registerAction( new NatureAction()  );
    mFactory.registerAction( new GoldAction()  );

    sound->open("birds.ogg");
    sound->setLoop(true);
    sound->play();

}


        void GameManager::attend(std::vector<std::string> &data)
        {
          Action *obj;

                obj = mFactory.getAction(data[0]);

                if( obj )
                {
                    obj->addParams(data);

                    m_mutex.lock();
                    for(unsigned int iter=0; iter < mQueuedAct.size(); iter++ )
                    {
                                if( mQueuedAct[iter]->getObjectId() == obj->getObjectId())
                                {
                                    fprintf(stderr,"Action already registered, adding new params\n\n");
                                    mQueuedAct[iter]->addParams(data);
                                    delete obj;
                                    return;
                                }
                    }
                    mQueuedAct.push_back(obj);
                    m_mutex.unlock();
                    fprintf(stderr,"Action %s created.\n ",obj->getObjectId().c_str());
                }
        }


        bool GameManager::frameEnded(const Ogre::FrameEvent &evt)
        {
            std::vector<Action*>::iterator iter;
            Action *actionPtr;

                //    m_mutex.lock();
                    for(unsigned int i = 0; i < mQueuedAct.size(); i++ )
                    {
                        actionPtr = mQueuedAct[i];

                        if( actionPtr->execute(evt) )
                        {
                            mQueuedAct.erase(mQueuedAct.begin()+i);
                            delete actionPtr;
                            i--;
                        }

                    }
                //    m_mutex.unlock();


                return true;
        }


GameManager::~GameManager()
{
Action *actionPtr;

        for(unsigned int i = 0; i < mQueuedAct.size(); i++ )
        {
            actionPtr = mQueuedAct[i];
            mQueuedAct.erase(mQueuedAct.begin()+i);
            delete actionPtr;
            i--;
        }
}
