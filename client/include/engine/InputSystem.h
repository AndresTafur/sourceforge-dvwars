#ifndef _INPUTSYSTEM_H
#define _INPUTSYSTEM_H

#include <list>
#include <Ogre.h>
#include <OIS/OIS.h>

#include <KeyboardListener.h>


/**
 *  handles mouse and keyboard devices.
 */
class InputSystem : protected Ogre::WindowEventListener, protected Ogre::FrameListener, protected OIS::MouseListener, protected OIS::KeyListener
{
private:

         InputSystem();
public:


         static InputSystem*   getInstancePtr();

         inline OIS::Mouse*    getMouse() { return mMouse; }

         inline OIS::Keyboard* getKeyboard() { return mKeyboard;}


         /**
          *  Process unbuffered input while GPU is working.
          *  This method is called automatically by Ogre3d.
          *  @param evt Current frame event.
          *  @return true on success, false otherwise.
          */
         bool frameRenderingQueued(const Ogre::FrameEvent& evt);



         /**
          * Adds a new keyboadListener.
          * This object has to implement the KeyboardListener interface.
          */
         void addKeyListener(KeyboardListener* obj);

         /**
          * Adds a new MouseListener.
          * This object has to implement the OIS MouseListener interface.
          */
         void addMouseListener(OIS::MouseListener* obj);


         /**
          * Removes a keyboadListener.
          * This object has to implement the KeyboardListener interface.
          */
         void removeKeyListener(KeyboardListener* obj);

         /**
          * Removes a MouseListener.
          * This object has to implement the OIS MouseListener interface.
          */
         void removeMouseListener(OIS::MouseListener* obj);


         static void destroy();


        ~InputSystem();

protected:

         bool mouseMoved( const OIS::MouseEvent &e );
         bool mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id);
         bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id);

         bool keyPressed(  const OIS::KeyEvent &e);
         bool keyReleased( const OIS::KeyEvent &e);

         void windowResized(Ogre::RenderWindow* rw);
         void windowClosed(Ogre::RenderWindow* rw);

private:
 static InputSystem  *smInstance;

 Ogre::RenderWindow  *mWindow;

 OIS::Mouse          *mMouse;
 OIS::Keyboard       *mKeyboard;
 OIS::InputManager   *mInputManager;

 std::list<KeyboardListener*>   mKeyListeners;
 std::list<OIS::MouseListener*> mMouseListeners;

};

#endif // _INPUTMANAGER_H
