#ifndef _CHATVIEW_H_
#define _CHATVIEW_H_

#include <Ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include <Client.h>
#include <ChatControl.h>
#include <ClientListener.h>

class ChatView : public ClientListener
{
public:

        ChatView();


        void onMainTextChange(MyGUI::EditPtr sender);

        void onBuddyTextChange(MyGUI::EditPtr sender);


        void onHideChat(MyGUI::Widget* btn);

        void onShowChat(MyGUI::Widget* btn);

        void onPrivate(MyGUI::Widget* btn);


        void onPrivateOpen(MyGUI::Widget* btn);



        void attend(std::vector<std::string> &data);


        virtual ~ChatView();


private:
MyGUI::VectorWidgetPtr    mLayout;
MyGUI::TabPtr             mTab;
MyGUI::ButtonPtr          mHide;
MyGUI::ButtonPtr          mShow;
MyGUI::ButtonPtr          mPrivate;

ChatControl              *mMainChat;
std::map<std::string, ChatControl*> mControls;
};

#endif // _CHATVIEW_H_
