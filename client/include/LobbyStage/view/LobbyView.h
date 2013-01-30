#ifndef _CHALLENGEVIEW_
#define _CHALLENGEVIEW_

#include <Ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include <util/Cripto.h>
#include <engine/Client.h>
#include <engine/Scene.h>

#include <LobbyStage/chat/ChatView.h>


/**
 * Manage challenge interface
 */
class LobbyView : public ClientListener, public Ogre::FrameListener, public Scene
{
public:

        void create(Ogre::RenderTarget* wnd);

        void createGui();

        void createCamera();

        void createSceneObjects();


        std::string getName();


        void drawLine();

        void doChallenge(MyGUI::Widget* btn);

        void showChallenge(MyGUI::Widget* btn);

        void showBuddies(MyGUI::Widget* btn);

        void onQuit(MyGUI::Widget* btn);


    //    void onAcceptDecline(MyGUI::MessagePtr sender, MyGUI::MessageBoxStyle result);

        void attend(std::vector<std::string> &data);

        bool frameRenderingQueued(const Ogre::FrameEvent& evt);


        void destroy();

        virtual ~LobbyView();

private:

MyGUI::VectorWidgetPtr   mLayout;
//MyGUI::MessagePtr        mWaitMsg;

MyGUI::ButtonPtr         mShowChall;
MyGUI::ButtonPtr         mShowBud;

unsigned int             mStatus;
std::vector<std::string> mParams;

ChatView                *mChatView;
Ogre::Light             *mLight;


};

#endif // _CHALLENGEVIEW_
