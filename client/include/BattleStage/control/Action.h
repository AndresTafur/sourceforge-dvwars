#ifndef _ACTION_H_
#define _ACTION_H_

#include <string>
#include <vector>
#include <Ogre.h>

/**
 * Abstract class to provide a common interface for action manipulation
 * @see ActionFactory
 */
class Action
{
public:

        /**
         * Executes the action
         * @param evt Ogre Frame event
         */
        virtual bool execute(const Ogre::FrameEvent &evt) = 0;

        virtual std::string getActionID() = 0;

        inline virtual std::string getObjectId() { return mObjectId;}

        virtual Action* clone() = 0;

        /**
         * Sets the action params.
         * @param params Parameters to be set.
         */
        inline virtual void addParams(std::vector<std::string> params) { mParams = params; }

        virtual ~Action() { }

protected:
std::vector<std::string> mParams;
std::string              mObjectId;
};
#endif


