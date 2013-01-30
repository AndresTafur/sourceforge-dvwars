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

#include "InputSystem.h"

InputSystem* InputSystem::smInstance = NULL;


InputSystem::InputSystem()
{
   OIS::ParamList pl;
   size_t windowHnd = 0;
   std::ostringstream windowHndStr;


                Ogre::LogManager::getSingletonPtr()->logMessage("\n\n\n=================== Initializing OIS ===================\n");

                mWindow = Ogre::Root::getSingletonPtr()->getAutoCreatedWindow();

                mWindow->getCustomAttribute("WINDOW", &windowHnd);
                windowHndStr << windowHnd;
                pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

                mInputManager = OIS::InputManager::createInputSystem( pl );

                mKeyboard     = static_cast<OIS::Keyboard*>(mInputManager->createInputObject( OIS::OISKeyboard, false ));
                mMouse        = static_cast<OIS::Mouse*>(mInputManager->createInputObject( OIS::OISMouse,true));

                Ogre::WindowEventUtilities::addWindowEventListener(mWindow, this);
                Ogre::Root::getSingletonPtr()->addFrameListener(this);
                windowResized(mWindow);

                mMouse->setEventCallback(this);
                mKeyboard->setEventCallback(this);
}


         InputSystem* InputSystem::getInstancePtr()
         {
              if( NULL == smInstance )
                  smInstance = new InputSystem();

              return smInstance;
         }


         bool InputSystem::frameRenderingQueued(const Ogre::FrameEvent& evt)
         {
            bool ret = true;

                mMouse->capture();
                mKeyboard->capture();

                if( !mKeyboard->buffered())
                    for( std::list<KeyboardListener*>::iterator iter = mKeyListeners.begin(); iter != mKeyListeners.end(); iter++ )
                                ret  &= (*iter)->processUnbufferedKeyInput(evt,mKeyboard);

                if(mKeyboard->isKeyDown(OIS::KC_I) /*&& mTimeUntilNextToggle <= 0*/)
                    mWindow->writeContentsToFile("DaVinciWars_ScreenShot.png");
                return ret;
         }


         void InputSystem::addKeyListener(KeyboardListener* obj)
         {
            mKeyListeners.push_back(obj);
         }

         void InputSystem::addMouseListener(OIS::MouseListener* obj)
         {
            mMouseListeners.push_back(obj);
         }


         void InputSystem::removeKeyListener(KeyboardListener* obj)
         {
            mKeyListeners.remove(obj);
         }

         void InputSystem::removeMouseListener(OIS::MouseListener* obj)
         {
            mMouseListeners.remove(obj);
         }


         bool InputSystem::mouseMoved( const OIS::MouseEvent &e )
         {
            bool ret = true;

                for( std::list<OIS::MouseListener*>::iterator iter = mMouseListeners.begin(); iter != mMouseListeners.end(); iter++ )
                                ret  &= (*iter)->mouseMoved(e);
                return ret;
         }

         bool InputSystem::mousePressed( const OIS::MouseEvent &e, OIS::MouseButtonID id)
         {
            bool ret = true;

                for( std::list<OIS::MouseListener*>::iterator iter = mMouseListeners.begin(); iter != mMouseListeners.end(); iter++ )
                            ret  &= (*iter)->mousePressed(e, id);
             return ret;
         }


         bool InputSystem::mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id)
         {
            bool ret = true;

                for( std::list<OIS::MouseListener*>::iterator iter = mMouseListeners.begin(); iter != mMouseListeners.end(); iter++ )
                            ret  &= (*iter)->mouseReleased(e,id);
                return ret;
         }


         bool InputSystem::keyPressed(  const OIS::KeyEvent &e)
         {
            bool ret = true;


                for( std::list<KeyboardListener*>::iterator iter = mKeyListeners .begin(); iter != mKeyListeners.end(); iter++ )
                            ret  &= (*iter)->keyPressed(e);
                return ret;
         }


         bool InputSystem::keyReleased( const OIS::KeyEvent &e)
         {
            bool ret = true;

                for( std::list<KeyboardListener*>::iterator iter = mKeyListeners .begin(); iter != mKeyListeners.end(); iter++ )
                            ret  &= (*iter)->keyReleased(e);
                return ret;
         }



         void InputSystem::windowResized(Ogre::RenderWindow* rw)
         {
              int mWidth = rw->getWidth();
              int mHeight = rw->getHeight();

                    if (mMouse)
                    {
                        const OIS::MouseState &ms = mMouse->getMouseState();
                        ms.width = (int)mWidth;
                        ms.height = (int)mHeight;
                    }
         }


         void InputSystem::windowClosed(Ogre::RenderWindow* rw)
         {
               if( NULL != rw  )
                    if( mInputManager )
                    {
                            rw->removeAllListeners();
                            rw->removeAllViewports ();

                            if( mKeyboard)
                                mInputManager->destroyInputObject( mKeyboard );

                            OIS::InputManager::destroyInputSystem(mInputManager);
                            mInputManager = 0;
                   }
        }


        void InputSystem::destroy()
        {
                if(smInstance)
                {
                    delete smInstance;
                    smInstance = NULL;
                }
        }


InputSystem::~InputSystem()
{
    		Ogre::WindowEventUtilities::removeWindowEventListener(mWindow, this);
    		windowClosed(mWindow);
}
