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

#include <engine/GUI.h>

GUI* GUI::sm_instance = 0;

        GUI::GUI()
        {
            mInitialized = false;

        }

        GUI& GUI::getInstance()
        {
                if( !sm_instance)
                    sm_instance = new GUI();
                return *sm_instance;
        }

        GUI* GUI::getInstancePtr()
        {
                if( !sm_instance)
                    sm_instance = new GUI();
                return sm_instance;
        }


        void GUI::initialize(Ogre::RenderTarget *wnd, Ogre::SceneManager *mgr)
        {

                if( !mInitialized )
                {
                    mRender = wnd;
                    mPlatform = new MyGUI::OgrePlatform();
                    mPlatform->initialise( static_cast<Ogre::RenderWindow*>(mRender), mgr);

                    mGUI     = new MyGUI::Gui();
                    mGUI->initialise();

                    InputSystem::getInstancePtr()->addMouseListener(this);
                    InputSystem::getInstancePtr()->addKeyListener(this);
                    mInitialized = true;
                }
                else{
                    MyGUI::OgreRenderManager::getInstancePtr()->setSceneManager(mgr);
                }




        }



        MyGUI::VectorWidgetPtr GUI::loadLayout(std::string layName)
        {
          return  MyGUI::LayoutManager::getInstance().loadLayout(layName);
        }


        void GUI::unloadLayout(MyGUI::VectorWidgetPtr layout)
        {
            MyGUI::LayoutManager::getInstancePtr()->unloadLayout(layout);
        }


          void GUI::onClose(MyGUI::Widget* btn)
        {
            Ogre::Root::getSingletonPtr()->queueEndRendering();
        }

        bool GUI::mouseMoved(const OIS::MouseEvent &evt)
        {
            MyGUI::InputManager::getInstancePtr()->injectMouseMove(evt.state.X.abs, evt.state.Y.abs, evt.state.Z.abs);
            return true;
        }

        bool GUI::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
        {
            MyGUI::InputManager::getInstancePtr()->injectMousePress(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));
            return true;
        }

        bool GUI::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
        {
            MyGUI::InputManager::getInstancePtr()->injectMouseRelease(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));
            return true;
        }

        bool GUI::keyPressed( const OIS::KeyEvent &evt )
        {

            MyGUI::InputManager::getInstancePtr()->injectKeyPress(MyGUI::KeyCode::Enum(evt.key), evt.text);
            return true;
        }

        bool GUI::keyReleased( const OIS::KeyEvent &evt )
        {
            MyGUI::InputManager::getInstancePtr()->injectKeyRelease(MyGUI::KeyCode::Enum(evt.key));
            return true;
        }


        void GUI::clean()
        {
            MyGUI::OgreRenderManager::getInstancePtr()->setSceneManager(nullptr);
        }


        void GUI::destroy()
        {
            //TODO: de-register from InputSystem
            sm_instance->clean();
            delete sm_instance;
        }


        GUI::~GUI()
        {
            mGUI->shutdown();
            delete mGUI;
            mGUI = 0;

            mPlatform->shutdown();
            delete mPlatform;
            mPlatform = 0;


            delete sm_instance;
            sm_instance = 0;
        }
