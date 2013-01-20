#ifndef _GUI_H_
#define _GUI_H_

#include <Ogre.h>
#include <OIS/OIS.h>
#include <InputSystem.h>



#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>


#include <engine/RenderBox.h>




/**
 *  Handles gui related behaviour.
 */
class GUI : public OIS::MouseListener, public KeyboardListener
{
 private:

           explicit GUI();

public:
            static GUI& getInstance();

            static GUI* getInstancePtr();


            /**
             * Starts the overlay system for widget drawing.
             * @param wnd Current render target.
             */
            void initialize(Ogre::RenderWindow *wnd);


            /**
             *  Loads a new xml Layout.
             *
             *  @param layName layout to be loaded.
             */
            MyGUI::VectorWidgetPtr loadLayout(std::string layName);

            /**
             *  unloads a previously loaded xml Layout.
             *
             *  @param layName layout to be loaded.
             */
            void unloadLayout(MyGUI::VectorWidgetPtr layName);


            //TODO: Separate this from the GUI define a game UI.
            void onClose(MyGUI::Widget* btn);


            bool mouseMoved(const OIS::MouseEvent &evt);
            bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
            bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
            bool keyPressed( const OIS::KeyEvent &arg );
            bool keyReleased( const OIS::KeyEvent &arg );


            static void destroy();

            ~GUI();

protected:
            void clean();

private:
static GUI  *sm_instance;

MyGUI::Gui            *mGUI;
MyGUI::OgrePlatform   *mPlatform;
MyGUI::PointerManager *mPmgr;
OIS::Mouse            *mMouse;

};
#endif
