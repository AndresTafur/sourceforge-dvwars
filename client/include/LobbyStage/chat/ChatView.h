#ifndef _CHATVIEW_H_
#define _CHATVIEW_H_

#include <Ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>


#include <ChatControl.h>

#include <engine/AbstractClient.h>
#include <util/SingletonContainer.h>

#include <GUI.h>

class ChatView : public ClientListener
{
public:

        ChatView();


        void onMainTextChange(MyGUI::EditBox *sender);

        void onBuddyTextChange(MyGUI::EditBox *sender);


        void onHideChat(MyGUI::Widget* btn);

        void onShowChat(MyGUI::Widget* btn);

        void onPrivate(MyGUI::Widget* btn);


        void onPrivateOpen(MyGUI::Widget* btn);



        void attend(std::vector<std::string> &data);


        virtual ~ChatView();


private:
MyGUI::TabPtr             mTab;
MyGUI::ButtonPtr          mHide;
MyGUI::ButtonPtr          mShow;
MyGUI::ButtonPtr          mPrivate;
MyGUI::VectorWidgetPtr    mLayout;

ChatControl              *mMainChat;
std::map<std::string, ChatControl*> mControls;
};

#endif // _CHATVIEW_H_
