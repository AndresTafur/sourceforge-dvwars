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

        RTSCameraManager(Ogre::SceneManager *mgr, Ogre::RenderWindow *wnd);

        bool frameRenderingQueued(const Ogre::FrameEvent &event);

        bool mouseMoved( const OIS::MouseEvent &e );

        bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id);

        bool processUnbufferedKeyInput(const Ogre::FrameEvent &evt, OIS::Keyboard *kb);

        bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id);


        virtual ~RTSCameraManager();

private:

    Ogre::Camera    *mCamera;
    Ogre::Viewport  *mViewPort;
    Ogre::SceneNode *mCameraNode;

    int mZoom;
    int mDispH;
    int mDispV;
};

#endif // _RTSCAMERA_H
