/*
 *  Copyright (C) 2011-2013 Jorge A. Tafur Q. (jatafurq).
 *
 *  This file is part of Da Vinci Wars project.
 *
 *  Da Vinci Wars is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  Da Vinci Wars is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with Da Vinci Wars.  If not, see <http://www.gnu.org/licenses/>.
 */


#include "MainApplication.h"

MainApplication::MainApplication()
{
    mRoot          = 0;
    mResourcePath  = "";
}



    void MainApplication::startApplication()
    {
        if (!setup())
            return;


        mSequencer =  new SceneSequencer(mSceneMgr,mWindow);
        GUI::getInstancePtr()->initialize(mWindow);

        mSequencer->start();



        Ogre::LogManager::getSingletonPtr()->logMessage("\n\n\n=================== Starting Ogre rendering system ===================\n");
        mRoot->startRendering();
        mRoot->queueEndRendering();
        delete mSequencer;
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
