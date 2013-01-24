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

#ifndef _MAINAPPLICATION_H_
#define _MAINAPPLICATION_H_


#include <Ogre.h>

#include <SceneSequencer.h>
#include <GUI.h>


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

         inline SceneSequencer* getSequencer() { return mSequencer; }


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
	SceneSequencer      *mSequencer;
};
#endif // _MAINAPPLICATION_H_
