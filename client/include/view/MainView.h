#ifndef _MAINVIEW_
#define _MAINVIEW_

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>

#include <view/GUI.h>
#include <view/WorkShopView.h>
#include <entity/MainScene.h>
#include <control/GameManager.h>
#include <control/LoginSceneManager.h>

/**
 * Ingame main view
 */
class MainView : public KeyboardListener
{
public:

        MainView(Ogre::SceneManager *mgr, Ogre::RenderWindow *wnd);



        bool processUnbufferedKeyInput(const Ogre::FrameEvent &evt, OIS::Keyboard *kb);


        /**
          *  Create the camera and initializes the RTS Camera manager.
          */
        void createCamera();

        void createGui();


        void onClose(MyGUI::Widget* btn);

        virtual ~MainView();

private:

Ogre::Camera        *mCamera;
Ogre::Viewport      *mViewPort;
Ogre::Camera        *mMiniCamera;

Ogre::SceneNode     *mMiniSceneNode;
Ogre::SceneNode     *mCameraNode;
wraps::RenderBox     mRenderBox;

Ogre::RenderWindow  *mWindow;
Ogre::SceneManager  *mSceneMgr;
MainScene           *mScene;
RTSCameraManager    *mCamMgr;

WorkShopView        *mWorkShop;
GameManager         *mGameMgr;
};


#endif // _MAINVIEW_
