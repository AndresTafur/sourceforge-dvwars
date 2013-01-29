#include "MainView.h"

MainView::MainView(Ogre::SceneManager *mgr, Ogre::RenderWindow *wnd)
{
    mSceneMgr = mgr;
    mWindow   = wnd;
/*
    mScene    = new MainScene(mgr,wnd);
    mGameMgr  = new GameManager();

    mScene->createScene();
    InputSystem::getInstancePtr()->getKeyboard()->setBuffered(false);
    InputSystem::getInstancePtr()->addKeyListener(this);*/
}

        void MainView::createGui()
        {
     //     GUI *guiMgr =  GUI::getInstancePtr();
     //     MyGUI::WidgetPtr cameraWnd;
      //    MyGUI::CanvasPtr canvas;

            //    mMiniCamera    = Ogre::Root::getSingleton().getSceneManager("MainManager")->createCamera("MiniMapCamera");
             //   mMiniSceneNode = Ogre::Root::getSingleton().getSceneManager("MainManager")->getRootSceneNode()->createChildSceneNode("MiniMapCameraNode");

//                guiMgr->loadLayout("GameInterface.gui");
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
                mRenderBox.setBackgroundColour(MyGUI::Colour::Black );
                mWorkShop = new WorkShopView();


                MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("Close")->eventMouseButtonClick += MyGUI::newDelegate(this, &MainView::onClose);
                */
        }


        bool MainView::processUnbufferedKeyInput(const Ogre::FrameEvent &evt, OIS::Keyboard *kb)
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


      /*  void MainView::createCamera(void)
        {
           Scene::createCamera();
           mCamMgr   = new RTSCameraManager(mSceneMgr, mWindow);

        }*/


        void MainView::destroy()
        {



        }


        void MainView::onClose(MyGUI::Widget* btn)
        {
                //Ogre::Root::getSingletonPtr()->queueEndRendering();
        }





MainView::~MainView()
{
    //dtor
}
