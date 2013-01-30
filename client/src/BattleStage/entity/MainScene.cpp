#include "MainScene.h"

MainScene::MainScene(Ogre::SceneManager *mgr, Ogre::RenderTarget *wnd)
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

            createTerrain();
            createNature();
    }

    void MainScene::createTerrain()
    {
            mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_NONE);

            mTerrainGlobals = OGRE_NEW Ogre::TerrainGlobalOptions();
            mTerrainGroup   = OGRE_NEW Ogre::TerrainGroup(mSceneMgr, Ogre::Terrain::ALIGN_X_Z, 513, 1200.0f);

            mTerrainGroup->setFilenameConvention(Ogre::String("BasicTutorial3Terrain"), Ogre::String("dat"));
            mTerrainGroup->setOrigin(Ogre::Vector3(0,-50,0) );


            configureTerrainDefaults();
            defineTerrain();

            // sync load since we want everything in place when we start
            mTerrainGroup->loadAllTerrains(true);
            mTerrainGroup->freeTemporaryResources();
    }

    void MainScene::configureTerrainDefaults()
    {
        // Configure global
        mTerrainGlobals->setMaxPixelError(8);
        // testing composite map
        mTerrainGlobals->setCompositeMapDistance(5000);

        // Important to set these so that the terrain knows what to use for derived (non-realtime) data
        mTerrainGlobals->setLightMapDirection(mLight->getDerivedDirection());
        mTerrainGlobals->setCompositeMapAmbient(mSceneMgr->getAmbientLight());


        mTerrainGlobals->setCompositeMapDiffuse(mLight->getDiffuseColour());
        mTerrainGlobals->setCastsDynamicShadows(true);
        mTerrainGlobals->setSkirtSize(10);


        // Configure default import settings for if we use imported image

        Ogre::Terrain::ImportData& defaultimp = mTerrainGroup->getDefaultImportSettings();
        defaultimp.terrainSize  = 513;
        defaultimp.worldSize    = 1200;
        defaultimp.inputScale   = 40;
        defaultimp.minBatchSize = 33;
        defaultimp.maxBatchSize = 65;

        defaultimp.layerList.resize(1);
        defaultimp.layerList[0].worldSize = 1200;
        defaultimp.layerList[0].textureNames.push_back("terrain_texture.jpg");
        defaultimp.layerList[0].textureNames.push_back("terrain_detail.jpg");
        defaultimp.layerList[0].textureNames.push_back("terrain_detail.jpg");
    }


    void MainScene::defineTerrain()
    {
      Ogre::String filename = mTerrainGroup->generateFilename(0, 0);
      Ogre::Image img;

                    img.load("terrain.png", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME);
                    mTerrainGroup->defineTerrain(0, 0, &img);
    }


    void MainScene::createNature()
    {
      int nodes_per_side = 0;

      Ogre::ConfigFile config;
      Ogre::String val;
      Ogre::Vector3 scale = Ogre::Vector3::ZERO;


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
