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

#include "BattleView.h"

void BattleView::create(Ogre::RenderWindow *wnd)
{
     Scene::create(wnd);


}

        std::string BattleView::getName(){
                return "Battle";
        }


        void BattleView::createGui()
        {
                GUI::getInstancePtr()->initialize( mWindow,mSceneMgr);

     //     MyGUI::WidgetPtr cameraWnd;
      //    MyGUI::CanvasPtr canvas;

            //    mMiniCamera    = Ogre::Root::getSingleton().getSceneManager("MainManager")->createCamera("MiniMapCamera");
             //   mMiniSceneNode = Ogre::Root::getSingleton().getSceneManager("MainManager")->getRootSceneNode()->createChildSceneNode("MiniMapCameraNode");

                mLayout = GUI::getInstancePtr()->loadLayout("GameInterface.gui");
//

               //TODO: Change minimap
               /*
                cameraWnd  = MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("MiniMap");
                canvas     = cameraWnd->createWidget<MyGUI::Canvas>("Canvas", MyGUI::IntCoord(3, 3, cameraWnd->getClientCoord().width-8, cameraWnd->getClientCoord().height-8), MyGUI::Align::Stretch);

                mMiniCamera->setPosition(0,0,0);
                mMiniCamera->setDirection(-0.01,-0.7,0.01);

                mMiniCamera->setNearClipDistance( 1 );
                mMiniCamera->setFarClipDistance( 500 );
                mMiniSceneNode->attachObject(mMiniCamera);
                mMiniSceneNode->setPosition(Ogre::Vector3(470,1300,470));

                mRenderBox.setCanvas(canvas);
                mRenderBox.setViewport(mMiniCamera);
                mRenderBox.setBackgroundColour(MyGUI::Colour::Black );               */
          //      mWorkShop = new WorkShopView();


                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("menuBtn")->eventMouseButtonClick += MyGUI::newDelegate(this, &BattleView::onClose);

        }


        void BattleView::createSceneObjects()
        {
            mScene    = new MainScene(mSceneMgr,mWindow);
           // mGameMgr  = new GameManager();

            mScene->createScene();
            InputSystem::getInstancePtr()->getKeyboard()->setBuffered(false);
            InputSystem::getInstancePtr()->addKeyListener(this);
        }


        bool BattleView::processUnbufferedKeyInput(const Ogre::FrameEvent &evt, OIS::Keyboard *kb)
        {
            Ogre::Vector3 orient;

                    orient = Ogre::Vector3( kb->isKeyDown(OIS::KC_DELETE)*10+kb->isKeyDown(OIS::KC_PGDOWN)*-10,
                                            kb->isKeyDown(OIS::KC_ADD)*-20 + kb->isKeyDown(OIS::KC_MINUS)*20,
                                            kb->isKeyDown(OIS::KC_HOME)*10 + kb->isKeyDown(OIS::KC_END)*-10
                                         );
                    if( mMiniCamera)
                    {
                        if( orient.length() == 0 and mMiniSceneNode->getPosition().y != 2003 )
                            orient =  Ogre::Vector3(0,(2003-mMiniSceneNode->getPosition().y)*evt.timeSinceLastFrame,0);

                        if( mMiniSceneNode->getPosition().y+orient.y < 70  )
                                orient.y = 0;
                        mMiniSceneNode->setPosition( mMiniSceneNode->getPosition() + orient);


                    }
          return true;
        }


        void BattleView::createCamera()
        {
            mCamera      = mSceneMgr->createCamera("Main Camera");
            mCameraNode  = mSceneMgr->createSceneNode("Camera Node");
            mViewPort    = mWindow->addViewport(mCamera);

            mCameraNode->attachObject(mCamera);
            mViewPort->setOverlaysEnabled(true);
            mViewPort->setBackgroundColour(Ogre::ColourValue(0,0,0));

            mCamera->setAspectRatio(Ogre::Real(mViewPort->getActualWidth()) / Ogre::Real(mViewPort->getActualHeight()));
            mCamera->setNearClipDistance(1);

            mCamera->setPosition(Ogre::Vector3(5,80,5));
            mCamera->lookAt(Ogre::Vector3(0,-30,0));
            mCamera->setNearClipDistance( 1 );
            mCamera->setFarClipDistance( 1500 );
            mCamera->setDirection(-0.5,-0.7,-0.4 );
            mCameraNode->setPosition(318.2,80,313 );

            mCamMgr = new RTSCameraManager(mCamera, mCameraNode);
        }


        void BattleView::destroy()
        {
            if(mCamMgr)
            {
                delete mCamMgr;
            }

            InputSystem::getInstancePtr()->removeKeyListener(this);
            GUI::getInstancePtr()->unloadLayout(mLayout);
            GUI::getInstancePtr()->clean();

            Scene::destroy();
        }


        void BattleView::onClose(MyGUI::Widget* btn)
        {
                endScene(0);
        }





BattleView::~BattleView()
{
    //dtor
}
