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

#include <Scene.h>
#include <SceneSequencer.h>



        void Scene::createCamera()
        {
           mCamera      = mSceneMgr->createCamera("Main Camera");
           mCameraNode  = mSceneMgr->createSceneNode("Camera Node");
           mViewPort    = mWindow->addViewport(mCamera);

           mCameraNode->attachObject(mCamera);
           mViewPort->setOverlaysEnabled(true);
           mViewPort->setBackgroundColour(Ogre::ColourValue(0,0,0));

           mCamera->setAspectRatio(Ogre::Real(mViewPort->getActualWidth()) / Ogre::Real(mViewPort->getActualHeight()));
           mCamera->setNearClipDistance(1);
        }


        void Scene::setSequencer(SceneSequencer *seq)
        {
            mSequencer = seq;
        }


    //QUick fix
    void Scene::endScene(short state)
    {
        mSequencer->endScene(this,state);
    }
