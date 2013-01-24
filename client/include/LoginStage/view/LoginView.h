#ifndef _LOGINVIEW_
#define _LOGINVIEW_

#include <Ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include <engine/GUI.h>
#include <BattleStage/view/MainView.h> //Needed to be changed for an independent secuencer
#include <LobbyStage/view/LobbyView.h>

#include <util/Cripto.h>


//#include <entity/Game.h>
#include <LoginStage/control/LoginSceneManager.h>
#include <Scene.h>

/**
 * Login interface
 */
class LoginView : public Ogre::FrameListener, public Scene
{
public:

        void create(Ogre::SceneManager *mgr, Ogre::RenderTarget* wnd);

        std::string getName();




         /*
          *  Create the camera and initializes the RTS Camera manager.
          */

        void createCamera();

        void createGui();


        /*
         *  Handles GUI events.
         */
        void onConnect(MyGUI::Widget* btn);

        void onExit(MyGUI::Widget* btn);

        void regCancel(MyGUI::Widget* btn);


        /**
         *  Shows registration window.
         * @param btn Action button
         */
        void showRegister(MyGUI::Widget* btn);

        void doRegister(MyGUI::Widget* btn);


        /**
         * Handles network data.
         * @param data formatted network data.
         */

        void attend(std::vector<std::string> data);

        bool frameEnded(const Ogre::FrameEvent& evt);



        void destroy();

        virtual ~LoginView();

private:
LoginSceneManager  *mLogSceneMgr;
MainView           *mMainView;

};

#endif // _LOGINVIEW_
