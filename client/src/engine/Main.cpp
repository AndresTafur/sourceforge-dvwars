#include "Main.h"


MainApplication::MainApplication()
{
    mRoot          = 0;
    mLoginView     = 0;
    mResourcePath  = "";
}



    void MainApplication::startApplication()
    {
        if (!setup())
            return;


        mLoginView = new LoginView(mSceneMgr,mWindow);
        mLoginView->createCamera();


        GUI::getInstancePtr()->initialize(mWindow);
        mLoginView->createGui();

        Ogre::LogManager::getSingletonPtr()->logMessage("\n\n\n=================== Starting Ogre rendering system ===================\n");
        mRoot->startRendering();
        mRoot->queueEndRendering();
        delete mLoginView;
    }


    bool MainApplication::setup()
    {
		Ogre::String pluginsPath;
		char   logName[100];
		time_t currTime = time(NULL);

                #ifndef OGRE_STATIC_LIB
                    pluginsPath = mResourcePath + "plugins.cfg";
                #endif


                sprintf(logName,"DVWars-%s.log", asctime(localtime(&currTime)) );

                mRoot = OGRE_NEW Ogre::Root(pluginsPath, mResourcePath + "DVConfig.cfg", mResourcePath + logName );

                if (!configure())
                    return false;

                mSceneMgr  = mRoot->createSceneManager( "OctreeSceneManager", "MainManager" );

                Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);
                loadResources();


            return true;
    }


    bool MainApplication::configure()
    {
       // if(!mRoot->restoreConfig())
           if( !mRoot->showConfigDialog())
                return false;

        mWindow = mRoot->initialise(true,"DaVinci Wars");

        return true;
    }


    void MainApplication::loadResources()
    {
        Ogre::ConfigFile cf;
        cf.load(mResourcePath + "resources.cfg");
        Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
        Ogre::String secName, typeName, archName;
        Ogre::ConfigFile::SettingsMultiMap *settings;


                while (seci.hasMoreElements())
                {
                    secName  = seci.peekNextKey();
                    settings = seci.getNext();
                    Ogre::ConfigFile::SettingsMultiMap::iterator i;

                    for (i = settings->begin(); i != settings->end(); ++i)
                    {
                        typeName = i->first;
                        archName = i->second;
                        Ogre::ResourceGroupManager::getSingleton().addResourceLocation(archName, typeName, secName);
                    }
                }
            Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
    }



MainApplication::~MainApplication()
{
  std::vector<Ogre::Plugin*> list;

        mRoot->queueEndRendering();

        if( mSceneMgr) mRoot->destroySceneManager(mSceneMgr);
        if( mWindow) mRoot->detachRenderTarget(mWindow);


        mRoot->getRenderSystem()->unregisterThread();
        mRoot->setRenderSystem(NULL);

//        list = mRoot->getInstalledPlugins ();


        for(unsigned int i= 0; i < list.size();i++)
            mRoot->uninstallPlugin (list[i]);

        fprintf(stderr," ================= Deleting last object, expecting segfault (OGRE issue) =================\n\n");

}



int main(int argc, char **argv)
{
    MainApplication app;

    try
    {
        app.startApplication();
        fprintf(stderr,"All components released, expecting libboost exit");
    }
    catch( Ogre::Exception& e )
    {
            std::cerr << "An exception has occured: " << e.getFullDescription();
    }
    return 0;
}
