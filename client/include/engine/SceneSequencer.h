/*
 * Copyright (C) 2012-2013 Da Vinci wars.
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 3
 * of the License, or (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef SCENESEQUENCER_H
#define SCENESEQUENCER_H

#include <Ogre.h>

#include <ConfigReader.h>

class Scene;

class SceneSequencer
{
public:

        SceneSequencer();

        void addScene(Scene *scn);

        void unloadScene(Scene *scn, bool destroy = false);

        void endScene(Scene *oldScene, short state);


        inline void setSceneManager(Ogre::SceneManager *mgr) { mSceneMgr = mgr; }

        inline void setRenderTarget(Ogre::RenderTarget *target) { mRenderTarget = target; }


        void setSceneSequence(std::string seqFile);

        void start();


        ~SceneSequencer();

private:
 Ogre::SceneManager *mSceneMgr;
 Ogre::RenderTarget *mRenderTarget;

 std::map<std::string, Scene*> mScenes;
 ConfigReader  mSeqReader;

};

#endif // SCENESEQUENCER_H
