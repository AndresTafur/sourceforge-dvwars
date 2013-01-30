#ifndef _MAINSCENE_
#define _MAINSCENE_


#include <MyGUI.h>
#include <Terrain/OgreTerrain.h>
#include <Terrain/OgreTerrainGroup.h>

#include <engine/GUI.h>
#include <BattleStage/control/SelectionManager.h>
#include <BattleStage/control/RTSCameraManager.h>

/**
 * Contains and creates starting game scene renderable objects.
 */
class MainScene
{
public:
        MainScene(Ogre::SceneManager *mgr, Ogre::RenderTarget *wnd);

        /**
          *  Create the camera and initializes the RTS Camera manager.
          */
        void createScene(void);

        void createTerrain();

        void configureTerrainDefaults();

        void defineTerrain();


        /**
         * Create heighmap and static geometries.
         */
        void createNature();


        void destroyScene();

        virtual ~MainScene();

private:
  Ogre::TerrainGlobalOptions *mTerrainGlobals;
  Ogre::TerrainGroup *mTerrainGroup;

  Ogre::Light         *mLight;
  Ogre::RenderTarget  *mWindow;
  Ogre::SceneManager  *mSceneMgr;
};

#endif // _MAINSCENE_
