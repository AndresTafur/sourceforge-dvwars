#ifndef _LOGINVIEW_
#define _LOGINVIEW_

#include <Ogre.h>


#include <engine/GUI.h>
#include <BattleStage/view/BattleView.h> //Needed to be changed for an independent secuencer
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

        void create(Ogre::RenderTarget* wnd);

        std::string getName();

        /*
         *  Create the camera and initializes the RTS Camera manager.
         */

        void createGui();

        void createSceneObjects();

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


        void setMessage(std::string message);

        void setErrorMessage(std::string error);



        bool frameEnded(const Ogre::FrameEvent& evt);


        void unloadLayout();


        void destroy();

        virtual ~LoginView();

private:
LoginSceneManager  *mLogSceneMgr;
MyGUI::VectorWidgetPtr mLayout;

};

#endif // _LOGINVIEW_
