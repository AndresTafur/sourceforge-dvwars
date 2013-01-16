#ifndef KEYBOARD_LISTENER_H
#define KEYBOARD_LISTENER_H

#include <Ogre.h>
#include <OIS/OIS.h>


/**
 *  Observer interface for KeyBoard input.
 *  @see InputSystem
 */
class KeyboardListener : public OIS::KeyListener
{
public:


         inline virtual bool keyPressed(const OIS::KeyEvent &evt) {return true;}

         inline virtual bool keyReleased(const OIS::KeyEvent &evt) {return true;}


         /**
          *  Abstract method called by the rendering when a frame has queued.
          */
         inline virtual bool processUnbufferedKeyInput(const Ogre::FrameEvent &evt, OIS::Keyboard *kb) {return true;}

};



#endif
