#ifndef _CHALLENGEVIEW_
#define _CHALLENGEVIEW_

#include <Ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include <util/Cripto.h>
#include <engine/Client.h>
#include <chat/ChatView.h>

/**
 * Manage challenge interface
 */
class ChallengeView : public ClientListener, public Ogre::FrameListener
{
public:

        ChallengeView(Ogre::SceneManager *mgr);

        void drawLine();

        void doChallenge(MyGUI::Widget* btn);

        void showChallenge(MyGUI::Widget* btn);

        void showBuddies(MyGUI::Widget* btn);


    //    void onAcceptDecline(MyGUI::MessagePtr sender, MyGUI::MessageBoxStyle result);

        void disable();

        void attend(std::vector<std::string> &data);

        bool frameEnded(const Ogre::FrameEvent& evt);

        virtual ~ChallengeView();

private:

Ogre::SceneNode         *mCameraNode;
Ogre::SceneManager      *mSceneManager;

Ogre::Camera            *mCamera;

MyGUI::VectorWidgetPtr   mLayout;
//MyGUI::MessagePtr        mWaitMsg;

MyGUI::ButtonPtr         mShowChall;
MyGUI::ButtonPtr         mShowBud;

unsigned int             mStatus;
std::vector<std::string> mParams;

ChatView                *mChatView;

};

#endif // _CHALLENGEVIEW_
