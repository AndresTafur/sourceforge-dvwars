#ifndef _WORKSHOPVIEW_
#define _WORKSHOPVIEW_

#include <Ogre.h>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>



#include <entity/Game.h>
#include <entity/Indicator.h>
#include <view/BuildingView.h>
#include <control/SquadManager.h>
#include <control/WorkShopManager.h>
#include <control/CreationListener.h>



class WorkShopView : public SelectionListener, public CreationListener
{
    public:

        WorkShopView();


        /**
         * Request building creation to server.
         * @param btn Button of the request.
         */
        void createBuilding(MyGUI::Widget* btn);


        /**
         * Do progressFill update when a building has increased its completetion
         * @param progress current progress.
         * @see CreationListener.
         */
        void onProgressUpdate(size_t progress);


        /**
         * Changes creation location.
         *
         * @param target New location where to move created units.
         * @see CreationListener.
         */
        void onChangeTarget(Ogre::Vector3 &target);


        /**
         * Called when a building has been created.
         * @param building Building to be created.
         */
        void onCreateBuilding(Building *building);


        /**
         * Handles hide/show of sub progressfills.
         * @param btn hide/show button.
         */
        void handleProgressPanel(MyGUI::Widget* btn);

       /**
        *
        *  When a mouse it's over a widget notifies to the corresponding UI.
        *
        */
        void onHover(MyGUI::Widget* btn, int x, int y);

        /**
         * Checks if the workshop has been selected.
         * @param obj Object selected
         * @param id  Button pressed.
         */
        void onSelection(Ogre::MovableObject *obj, OIS::MouseButtonID id);

        /**
         * Checks if the ground has been selected, (in order to hide the menu).
         * @param ent Tile of ground selected.
         * @param id  Button pressed.
         */
        void onWorldSelection(Ogre::SceneQuery::WorldFragment *ent,  OIS::MouseButtonID id);


       virtual ~WorkShopView();

    protected:

private:
bool                  mSelected;
WorkShopManager      *mWShopMgr;
Indicator            *mCreationLocation;

std::map<std::string, BuildingView*> mBuildingViews;
};

#endif // _WORKSHOPVIEW_
