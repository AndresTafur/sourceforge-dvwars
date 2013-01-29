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

#ifndef SCENE_H
#define SCENE_H


#include <Ogre.h>

class SceneSequencer;

class Scene
{
public:

        virtual void create(Ogre::RenderTarget* wnd);

        virtual void createCamera();

        virtual void createGui() = 0;



        virtual std::string getName() = 0;


        void setSequencer(SceneSequencer *seq);

        void endScene(short state);


        virtual void destroy();

        virtual ~Scene() {}

protected:
SceneSequencer     *mSequencer;

Ogre::SceneManager *mSceneMgr;
Ogre::SceneNode    *mCameraNode;
Ogre::Camera       *mCamera;
Ogre::Viewport     *mViewPort;
Ogre::RenderTarget *mWindow;


};

#endif // SCENE_H
