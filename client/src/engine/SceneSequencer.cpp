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

#include "SceneSequencer.h"
#include "Scene.h"


SceneSequencer::SceneSequencer(Ogre::SceneManager *mgr, Ogre::RenderTarget *target) : mSceneMgr(mgr), mRenderTarget(target)
{
    //ctor
}

        void SceneSequencer::addScene(Scene *scn)
        {
                    mScenes.insert( std::make_pair( scn->getName(),scn  ));
        }


        void SceneSequencer::unloadScene(Scene *scn, bool destroy)
        {



        }


        void SceneSequencer::setSceneSequence(std::string seqFile)
        {
            mSeqReader.openFile(seqFile);
        }


        void SceneSequencer::start()
        {
                     //->create
       //  mLoginView->createCamera();
       //  mLoginView->createGui();

        }


        void SceneSequencer::endScene(Scene *scn, short state)
        {


        }




SceneSequencer::~SceneSequencer()
{
    //dtor
}
