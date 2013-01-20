#ifndef _CHATCONTROL_H_
#define _CHATCONTROL_H_

#include <Ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

class ChatControl
{
public:

        ChatControl(MyGUI::TabPtr noteBook, std::string tabName, std::string preData);

        void onMainTextChange(MyGUI::EditPtr sender);

        void addMessage(std::string user, std::string message);

        virtual ~ChatControl();

private:

MyGUI::EditPtr          mEdit;
MyGUI::StaticTextPtr    mLogView;

std::string             mPreData;
};

#endif // _CHATCONTROL_H_
