#include "MainScene.h"

MainScene::MainScene(Ogre::SceneManager *mgr, Ogre::RenderWindow *wnd)
{
    mWindow   = wnd;
    mSceneMgr = mgr;
}


    void MainScene::createScene(void)
    {
      Ogre::DataStreamPtr cfgFile;

            mLight = mSceneMgr->createLight("MainLight");

            mSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));
            mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
            mSceneMgr->setShadowColour(Ogre::ColourValue(0.5,0.5,0.5));
            mSceneMgr->setSkyDome(true, "CloudySky");

            mLight->setPosition(20,800,50);
            mLight->setSpecularColour(0.7,0.6,0);
            mLight->setCastShadows(true);

            cfgFile = Ogre::ResourceGroupManager::getSingleton().openResource ("basicTerrain.cfg");
            mSceneMgr->setWorldGeometry( cfgFile );
            createNature();
    }


    void MainScene::createNature()
    {
      int nodes_per_side = 0;
      int nodes_per_side_all_pagesW = 0;
      int nodes_per_side_all_pagesH = 0;

      Ogre::ConfigFile config;
      Ogre::String val;
      Ogre::Vector3 scale = Ogre::Vector3::ZERO;
      Ogre::Real worldWidth, worldHeight;


                mSceneMgr->getOption("Scale", &scale);
                mSceneMgr->getOption("PageSize", &nodes_per_side);


                if (nodes_per_side == 0)
                {
                        config.load("basicTerrain.cfg", "General", "=", true);

                        val = config.getSetting( "PageSize" );
                        assert( !val.empty() );
                        nodes_per_side = atoi( val.c_str() );

                        val = config.getSetting( "PageWorldX" );
                        assert( !val.empty() );
                        scale.x = atof( val.c_str() ) / nodes_per_side;

                        val = config.getSetting( "MaxHeight" );
                        assert( !val.empty() );
                        scale.y = atof( val.c_str() );

                        val = config.getSetting( "PageWorldZ" );
                        assert( !val.empty() );
                        scale.z = atof( val.c_str() ) / nodes_per_side;
                }

                worldWidth  = scale.x * (nodes_per_side - 1);
                worldHeight = scale.z * (nodes_per_side - 1);
                nodes_per_side_all_pagesW = nodes_per_side;
                nodes_per_side_all_pagesH = nodes_per_side;
    }

    void MainScene::destroyScene()
    {
        if( mLight)
            mSceneMgr->destroyAllLights();
        mSceneMgr->clearScene();
    }


MainScene::~MainScene()
{
    //dtor
}
