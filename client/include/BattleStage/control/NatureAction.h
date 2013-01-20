#ifndef _NATUREACTION_H
#define _NATUREACTION_H

#include <Action.h>
#include <Ogre.h>

class NatureAction : public Action
{
public:

        NatureAction();

        bool execute(const Ogre::FrameEvent &evt);

        Action* clone();

        inline std::string getActionID() {  return "490";  }

        std::string getObjectId();

        void addParams(std::vector<std::string> params);

        virtual ~NatureAction();

private:
std::string    mObjectId;
std::string    mMesh;
Ogre::Vector3  mPos;
bool           mFinalize;
};

#endif // _NATUREACTION_H
