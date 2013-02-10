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
    mSequencer     = NULL;
}



    void MainApplication::startApplication()
    {
        if (!setup())
            return;


 Ogre::Overlay*             overlay;
Ogre::MaterialPtr material = Ogre::MaterialManager::getSingleton().create("Background", "General");
material->getTechnique(0)->getPass(0)->createTextureUnitState("loading.png");
material->getTechnique(0)->getPass(0)->setDepthCheckEnabled(false);
material->getTechnique(0)->getPass(0)->setDepthWriteEnabled(false);
material->getTechnique(0)->getPass(0)->setLightingEnabled(false);
material->getTechnique(0)->getPass(0)->setDiffuse(0.5,0.5,0.5,0.3);
material->getTechnique(0)->getPass(0)->setSceneBlending(Ogre::SBT_TRANSPARENT_ALPHA);

Ogre::OverlayManager& overlayManager = Ogre::OverlayManager::getSingleton();
   overlay = overlayManager.create( "OverlayName" );

   // Create a panel
   Ogre::OverlayContainer* panel = static_cast<Ogre::OverlayContainer*>( overlayManager.createOverlayElement( "Panel", "PanelName" ) );
   panel->setPosition( 0.0, 0.0 );
   panel->setDimensions( 1, 1 ); // cover the entire window
   panel->setMaterialName( "Background" );
   // Add the panel to the overlay
   overlay->add2D( panel );

   // Show the overlay
   overlay->show();


        if( mSequencer != NULL )
        {
            mSequencer->setRenderTarget(mWindow);
            mSequencer->start();
        }
        else
            Ogre::LogManager::getSingletonPtr()->logMessage("\n Sequencer not available, render will be empty!\n");

        Ogre::LogManager::getSingletonPtr()->logMessage("\n\n\n=================== Starting Ogre rendering system ===================\n");
        mRoot->startRendering();
        mRoot->queueEndRendering();

    }


    bool MainApplication::setup()
    {
		Ogre::String pluginsPath;
		char   logName[100];
//		time_t currTime = time(NULL);

                #ifndef OGRE_STATIC_LIB
                    pluginsPath = mResourcePath + "plugins.cfg";
                #endif


                sprintf(logName,"DVWars.log" /*, asctime(localtime(&currTime)) */ );

                mRoot = OGRE_NEW Ogre::Root(pluginsPath, mResourcePath + "DVConfig.cfg", mResourcePath + logName );

                if (!configure())
                    return false;

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


           //     while (seci.hasMoreElements())
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
  Ogre::Root::PluginInstanceList list;


        GUI::destroy();
        InputSystem::destroy();
        if( mWindow) mRoot->detachRenderTarget(mWindow);


        mRoot->getRenderSystem()->unregisterThread();
        mRoot->setRenderSystem(NULL);

        list = mRoot->getInstalledPlugins ();


        for(unsigned int i= 0; i < list.size();i++)
            mRoot->uninstallPlugin (list[i]);

        OGRE_DELETE mRoot;

        fprintf(stderr," ================= Deleting last object, expecting segfault (OGRE issue) =================\n\n");

}
