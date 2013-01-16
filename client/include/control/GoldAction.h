#ifndef _GOLDACTION_H_
#define _GOLDACTION_H_

#include <MyGUI.h>
#include <Action.h>
#include <MyGUI_OgrePlatform.h>


class GoldAction : public Action
{
public:

        GoldAction();

        bool execute(const Ogre::FrameEvent &evt);

        Action* clone();

        inline std::string getActionID() {  return "410";  }

        std::string getObjectId();

        void addParams(std::vector<std::string> params);

        ~GoldAction();

private:
unsigned long mValue;
};

#endif // _GOLDACTION_H_
