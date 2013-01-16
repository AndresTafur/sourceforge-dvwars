#ifndef _MAINSCENE_
#define _MAINSCENE_


#include <MyGUI.h>

#include <view/GUI.h>
#include <control/SelectionManager.h>
#include <control/RTSCameraManager.h>

/**
 * Contains and creates starting game scene renderable objects.
 */
class MainScene
{
public:
        MainScene(Ogre::SceneManager *mgr, Ogre::RenderWindow *wnd);

        /**
          *  Create the camera and initializes the RTS Camera manager.
          */
        void createScene(void);

        /**
         * Create heighmap and static geometries.
         */
        void createNature();


        void destroyScene();

        virtual ~MainScene();

private:
  Ogre::Light         *mLight;
  Ogre::RenderWindow  *mWindow;
  Ogre::SceneManager  *mSceneMgr;
};

#endif // _MAINSCENE_
