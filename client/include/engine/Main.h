#ifndef _MAINAPP_
#define _MAINAPP_


#include <Ogre.h>

#include <view/LoginView.h>

/**
 * Creates de main  scene.
 * Initializes frameListeners, lights and ambient.
 */

class MainApplication
{
public:
         MainApplication();
        ~MainApplication();

         /**
          * Starts render system, Must be called by main within a try-catch block.
          */
         virtual void startApplication();

protected:

        /**
         *  Initializes ogre subsystems.
         *  @return true on success false otherwise.
         */
        bool setup();

        /**
         *  Shows render config dialog if needed.
         *  @return true on success false otherwise.
         */
        bool configure();

        /**
         *  Initializes all the resource groups within defined paths.
         */
        void loadResources();


protected:

    Ogre::Root          *mRoot;
    Ogre::SceneManager  *mSceneMgr;
    Ogre::RenderWindow  *mWindow;
	Ogre::String         mResourcePath;
	LoginView           *mLoginView;
};
#endif

