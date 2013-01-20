#ifndef _CREATEACTION_H_
#define _CREATEACTION_H_

#include "Action.h"
#include "control/SquadManager.h"

/**
 * Handles a creation action.
 * @see Action
 */
class CreateAction : public Action
{
public:

        CreateAction(SquadManager  *squadMgr);

        /**
         * Executed every frame til ended.
         * @param evt Ogre frame event
         */
        bool execute(const Ogre::FrameEvent &evt);

        Action* clone();

        inline std::string getActionID() {  return "701";  }

        std::string getObjectId();

        void addParams(std::vector<std::string> params);

        ~CreateAction();

private:
SquadManager    *mSquadMgr;
};

#endif // _CREATESQUAD_H_
