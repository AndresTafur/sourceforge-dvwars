#ifndef _SELECTIONMANAGER_
#define _SELECTIONMANAGER_

#include <Ogre.h>
#include <OIS/OIS.h>
#include <InputSystem.h>
#include <SelectionListener.h>


/**
 * Handles user selection inputs.
 */
class SelectionManager : public OIS::MouseListener
{
protected:

        SelectionManager();

public:

        static SelectionManager* getInstance();

        bool mouseMoved  (  const OIS::MouseEvent &e );

        bool mousePressed(  const OIS::MouseEvent &e, OIS::MouseButtonID id);

        bool mouseReleased( const OIS::MouseEvent &e, OIS::MouseButtonID id);


        /**
         * Adds a new selection listener.
         * Called when a 3d object has been selected.
         *
         * @param obj  New selection listener to be notified.
         */
        inline void addSelectionListener(SelectionListener *obj) { mObservers.push_back(obj); }

        virtual ~SelectionManager();

protected:

private:
Ogre::SceneManager  *mScnMgr;
Ogre::Camera        *mCamera;
std::list<SelectionListener*> mObservers;

static SelectionManager *smInstance;
};

#endif // _SELECTIONMANAGER_
