#include <view/GUI.h>

GUI* GUI::sm_instance = 0;

        GUI::GUI()
        {


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

        void GUI::initialize(Ogre::RenderWindow *wnd)
        {
                mPlatform = new MyGUI::OgrePlatform();
                mPlatform->initialise(wnd, Ogre::Root::getSingleton().getSceneManager("MainManager"));

                mGUI      = new MyGUI::Gui();
                mGUI->initialise();

                InputSystem::getInstancePtr()->addMouseListener(this);
                InputSystem::getInstancePtr()->addKeyListener(this);
        }


        void GUI::loadLayout(std::string layName)
        {
            mGUI->load(layName);
        }


          void GUI::onClose(MyGUI::Widget* btn)
        {
            Ogre::Root::getSingletonPtr()->queueEndRendering();
        }

        bool GUI::mouseMoved(const OIS::MouseEvent &evt)
        {
            mGUI->injectMouseMove(evt.state.X.abs, evt.state.Y.abs, evt.state.Z.abs);
            return true;
        }

        bool GUI::mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
        {
            mGUI->injectMousePress(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));
            return true;
        }

        bool GUI::mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id)
        {
            mGUI->injectMouseRelease(evt.state.X.abs, evt.state.Y.abs, MyGUI::MouseButton::Enum(id));
            return true;
        }

        bool GUI::keyPressed( const OIS::KeyEvent &evt )
        {

            mGUI->injectKeyPress(MyGUI::KeyCode::Enum(evt.key), evt.text);
            return true;
        }

        bool GUI::keyReleased( const OIS::KeyEvent &evt )
        {
            mGUI->injectKeyRelease(MyGUI::KeyCode::Enum(evt.key));
            return true;
        }


        void GUI::clean()
        {
            mGUI->shutdown();
            delete mGUI;
            mGUI = 0;

            mPlatform->shutdown();
            delete mPlatform;
            mPlatform = 0;
        }


        void GUI::destroy()
        {
            sm_instance->clean();
            delete sm_instance;
            sm_instance = 0;
        }

        GUI::~GUI()
        {


        }
