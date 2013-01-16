#include "RTSCameraManager.h"
#include <InputSystem.h>



RTSCameraManager::RTSCameraManager(Ogre::SceneManager *mgr, Ogre::RenderWindow *wnd)
{
        mCamera     = mgr->createCamera("RTSCam");
        mCameraNode = mgr->createSceneNode("Camera Node");

        mCamera->setPosition(Ogre::Vector3(5,80,5));
        mCamera->lookAt(Ogre::Vector3(0,-30,0));
        mCamera->setNearClipDistance( 1 );
        mCamera->setFarClipDistance( 500 );
        mCamera->setDirection(-0.5,-0.7,-0.4 );

        mCameraNode->attachObject(mCamera);
        mCameraNode->setPosition(318.2,80,313 );


        mViewPort = wnd->addViewport(mCamera);

        mViewPort->setOverlaysEnabled(true);
        mViewPort->setBackgroundColour(Ogre::ColourValue(0,0,0));
        mCamera->setAspectRatio(Ogre::Real(mViewPort->getActualWidth()) / Ogre::Real(mViewPort->getActualHeight()));


        Ogre::Root::getSingletonPtr()->addFrameListener(this);
        InputSystem::getInstancePtr()->addMouseListener(this);
        InputSystem::getInstancePtr()->addKeyListener(this);
}



     bool RTSCameraManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
     {
       const OIS::MouseState &state = InputSystem::getInstancePtr()->getMouse()->getMouseState();
       Ogre::Vector3 orient = mCamera->getDirection()*2;


            if( state.Y.abs == 0)
                mCameraNode->translate( Ogre::Vector3(orient.x,0,orient.z), Ogre::SceneNode::TS_LOCAL  );

            else if( state.Y.abs == abs(Ogre::Root::getSingleton().getRenderTarget("DaVinci Wars")->getHeight()) )
                mCameraNode->translate( Ogre::Vector3(-orient.x,0,-orient.z), Ogre::SceneNode::TS_LOCAL  );


            if( state.X.abs == 0)
                mCameraNode->translate( Ogre::Vector3(-orient.x,0,-orient.z).crossProduct(Ogre::Vector3::UNIT_Y), Ogre::SceneNode::TS_LOCAL  );

            else if( state.X.abs == abs(Ogre::Root::getSingleton().getRenderTarget("DaVinci Wars")->getWidth()) )
                mCameraNode->translate( Ogre::Vector3(orient.x,0,orient.z).crossProduct(Ogre::Vector3::UNIT_Y), Ogre::SceneNode::TS_LOCAL  );


            return true;
    }



    bool RTSCameraManager::processUnbufferedKeyInput(const Ogre::FrameEvent &evt, OIS::Keyboard *kb)
    {
       Ogre::Vector3 orient = mCamera->getDirection();


                    mCamera->pitch( Ogre::Radian(-0.01)* kb->isKeyDown (OIS::KC_S)  +  Ogre::Radian(0.01 )*kb->isKeyDown(OIS::KC_W));
                    mCamera->yaw(   Ogre::Radian(0.01) * kb->isKeyDown (OIS::KC_A)  +  Ogre::Radian(-0.01)*kb->isKeyDown(OIS::KC_D));
                    mCameraNode->translate( Ogre::Vector3(orient.x,0,orient.z)*kb->isKeyDown(OIS::KC_UP) +  Ogre::Vector3(-orient.x,0,-orient.z)*kb->isKeyDown(OIS::KC_DOWN), Ogre::SceneNode::TS_LOCAL  );

                    if( kb->isKeyDown(OIS::KC_LEFT) )
                        mCameraNode->translate( Ogre::Vector3(-orient.x,0,-orient.z).crossProduct(Ogre::Vector3::UNIT_Y), Ogre::SceneNode::TS_LOCAL  );

                    if( kb->isKeyDown(OIS::KC_RIGHT) )
                        mCameraNode->translate( Ogre::Vector3(orient.x,0,orient.z).crossProduct(Ogre::Vector3::UNIT_Y), Ogre::SceneNode::TS_LOCAL  );

                    if( kb->isKeyDown(OIS::KC_ESCAPE) )
                            return false;
          return true;
    }


    bool RTSCameraManager::mouseMoved( const OIS::MouseEvent &e )
    {
        const OIS::MouseState &state = InputSystem::getInstancePtr()->getMouse()->getMouseState();
        int z = state.Z.rel;


            if( z > 0)
            {
                mCameraNode->translate( Ogre::Vector3(0,-10,0));
                mZoom = z;
            }

            if( z < 0 )
            {
                mCameraNode->translate( Ogre::Vector3(0,10,0));
                mZoom = z;
            }


          return true;
    }

    bool RTSCameraManager::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id)
    {
         return true;
    }

    bool RTSCameraManager::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id)
    {
        return true;
    }




RTSCameraManager::~RTSCameraManager()
{
           //if( mCamera) mSceneMgr->destroyAllCameras(); TODO:
}
