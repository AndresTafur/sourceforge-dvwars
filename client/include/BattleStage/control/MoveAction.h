#ifndef _MOVEACTION_H_
#define _MOVEACTION_H_

#include <Ogre.h>
#include <Action.h>
#include "SquadManager.h"


/**
 * Starts moving an object each frame.
 * @see ActionFactory.
 */
class MoveAction : public Action
{
public:

        MoveAction(SquadManager  *squadMgr);

        bool execute(const Ogre::FrameEvent &evt);

        Action* clone();

        inline std::string getActionID() {  return "710";  }

        std::string getObjectId();

        void addParams(std::vector<std::string> params);

        ~MoveAction();

private:
SquadManager         *mSquadMgr;
Unit                 *mUnit;
Ogre::Vector3         mDisp;
Ogre::AnimationState *mAnim;
std::queue<Ogre::Vector3>  mFinalPos;
std::string           mObjectId;
};

#endif // MOVEACTION_H
