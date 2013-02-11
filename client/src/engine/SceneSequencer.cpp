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


SceneSequencer::SceneSequencer()
{

}

        void SceneSequencer::addScene(Scene *scn)
        {
                    scn->setSequencer(this);
                    mScenes.insert( std::make_pair( scn->getName(),scn  ));
        }



        void SceneSequencer::setSceneSequence(std::string seqFile)
        {
            mSeqReader.openFile(seqFile);
        }


        void SceneSequencer::start()
        {
            std::string sceneName = mSeqReader.getAttribute("/descendant::sequence/child::scene[@initial='true']/@name");


                mCurrentScene = mScenes[sceneName];

                if(mCurrentScene != NULL)
                {
                    mCurrentScene->create(mRenderTarget);
                    mCurrentScene->createCamera();
                    mCurrentScene->createGui();
                    mCurrentScene->createSceneObjects();
                    mCurrentScene->setSequencer(this);
                }
        }



        void SceneSequencer::queueEndScene(short state)
        {
                Scene *scene;
                char   charVal[10];
                std::string sceneName;
                std::string exp = "/descendant::sequence/child::scene[@name='"+mCurrentScene->getName()+"']/child::state[@value='";


                                sprintf(charVal,"%i']",state);
                                exp += charVal;


                                sceneName = mSeqReader.getAttribute(exp);

                                if( sceneName == "Exit" )
                                {
                                    Ogre::Root::getSingletonPtr()->queueEndRendering();
                                    return;
                                }

                                scene = mScenes[sceneName];

                                if(scene != NULL)
                                {

                                    std::cerr << "Loading scene: '" << sceneName << "'." << std::endl;

                                    mCurrentScene->destroy();

                                    scene->create(mRenderTarget);
                                    scene->createCamera();
                                    scene->createGui();
                                    scene->createSceneObjects();
                                    scene->setSequencer(this);
                                    mCurrentScene = scene;

                                }
                                else
                                    std::cerr << "Scene: '" << sceneName << "' is not available." << std::endl;
        }




SceneSequencer::~SceneSequencer()
{
    //dtor
}
