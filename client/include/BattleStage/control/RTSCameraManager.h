#ifndef _RTSCAMERA_MANAGER_H
#define _RTSCAMERA_MANAGER_H

#include <Ogre.h>
#include <OIS/OIS.h>

#include <KeyboardListener.h>


/**
 *  Handles main camera.
 *  Handles RTS camera movement and input.
 *  @see InputSystem
 */

class RTSCameraManager : public OIS::MouseListener, public KeyboardListener, public Ogre::FrameListener
{
    public:

        RTSCameraManager(Ogre::Camera *cam, Ogre::SceneNode *camNode);

        bool frameRenderingQueued(const Ogre::FrameEvent &event);

        bool mouseMoved( const OIS::MouseEvent &e );

        bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id);

        bool processUnbufferedKeyInput(const Ogre::FrameEvent &evt, OIS::Keyboard *kb);

        bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id);


        virtual ~RTSCameraManager();

private:

    int mZoom;
    int mDispH;
    int mDispV;


    Ogre::Camera    *mCamera;
    Ogre::Viewport  *mViewPort;
    Ogre::SceneNode *mCameraNode;
    Ogre::SceneManager *mSceneMgr;
};

#endif // _RTSCAMERA_H
