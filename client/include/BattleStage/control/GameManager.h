#ifndef _GAMEMANAGER_
#define _GAMEMANAGER_

#include <vector>
#include <boost/thread.hpp>

#include <entity/Squad.h>
#include <engine/Client.h>
#include <control/Action.h>
#include <control/ActionFactory.h>
#include <control/SquadManager.h>
#include <control/SelectionManager.h>



/**
 * Handles in-game Action objects, and attends them every frame
 */
class GameManager : public ClientListener, public Ogre::FrameListener
{
public:

        GameManager();


        void attend(std::vector<std::string> &data);


        bool frameEnded(const Ogre::FrameEvent &evt);


        virtual ~GameManager();

private:
ActionFactory         mFactory;
SquadManager         *mSquadMgr;
std::vector<Action*>  mQueuedAct;
bool                  mLock;
boost::mutex m_mutex;
};

#endif // _GAMEMANAGER_
