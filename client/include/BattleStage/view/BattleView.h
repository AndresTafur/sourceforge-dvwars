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

#ifndef _MAINVIEW_
#define _MAINVIEW_

#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>


#include <GUI.h>
#include <Scene.h>
#include <BattleStage/view/WorkShopView.h>
#include <BattleStage/control/MainScene.h>
#include <BattleStage/control/GameManager.h>


/**
 * Ingame main view
 */
class BattleView : public Scene, public KeyboardListener
{
public:

        void create(Ogre::RenderWindow *wnd);

        void createGui();

        void createCamera();

        void createSceneObjects();

        std::string getName();



        bool processUnbufferedKeyInput(const Ogre::FrameEvent &evt, OIS::Keyboard *kb);


        void destroy();

        void onClose(MyGUI::Widget* btn);

        virtual ~BattleView();

private:

Ogre::Camera        *mCamera;
Ogre::Viewport      *mViewPort;
Ogre::Camera        *mMiniCamera;

Ogre::SceneNode     *mMiniSceneNode;
Ogre::SceneNode     *mCameraNode;
wraps::RenderBox     mRenderBox;

MainScene           *mScene;
RTSCameraManager    *mCamMgr;

WorkShopView        *mWorkShop;
GameManager         *mGameMgr;

MyGUI::VectorWidgetPtr   mLayout;
};


#endif // _MAINVIEW_
