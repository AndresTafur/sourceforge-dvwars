#ifndef _LOGINVIEW_
#define _LOGINVIEW_

#include <Ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include <view/GUI.h>
#include <view/MainView.h>
#include <view/ChallengeView.h>

#include <util/Cripto.h>


#include <entity/Game.h>
#include <control/LoginSceneManager.h>



/**
 * Login interface
 */
class LoginView : public Ogre::FrameListener
{
public:

        LoginView(Ogre::SceneManager *mgr, Ogre::RenderWindow *wnd);


        /**
          *  Create the camera and initializes the RTS Camera manager.
          */
        void createCamera();

        void createGui();


        void onConnect(MyGUI::Widget* btn);

        void onClose(MyGUI::Widget* btn);

        void regCancel(MyGUI::Widget* btn);


        void showMain(MyGUI::Widget* btn);

        void showLogin(MyGUI::Widget* btn);


        void doLogIn(MyGUI::Widget* btn);



        /**
         *  Shows registration window.
         * @param btn Action button
         */
        void showRegister(MyGUI::Widget* btn);

        void doRegister(MyGUI::Widget* btn);



        void attend(std::vector<std::string> data);

        bool frameEnded(const Ogre::FrameEvent& evt);


        virtual ~LoginView();

private:

Ogre::Camera       *mCamera;
Ogre::Viewport     *mViewPort;
Ogre::SceneNode    *mCameraNode;

Ogre::RenderWindow *mWindow;
Ogre::SceneManager *mSceneMgr;
LoginSceneManager  *mLogSceneMgr;
MainView           *mMainView;

boost::shared_ptr<ChallengeView> mChallengeView;

};

#endif // _LOGINVIEW_
