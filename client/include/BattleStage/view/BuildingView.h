#ifndef _BUILDINGVIEW_H_
#define _BUILDINGVIEW_H_

#include <vector>
#include <string>
#include <MyGUI.h>
#include <MyGUI_OgrePlatform.h>


#include <BattleStage/control/CreationListener.h>
#include <BattleStage/control/BuildingManager.h>


/**
 *
 * Manages workshop building butons.
 */

class BuildingView : public CreationListener
{
public:

        BuildingView(Building *building);


        /**
         * Request server squad creation.
         * @param btn Action button.
         */
        void createSquad(MyGUI::Widget* btn);



        void onProgressUpdate(size_t val);

        void onCreateSquad(Squad *squad);



        void showView();

        void hideView();



        virtual ~BuildingView();

private:
MyGUI::ProgressPtr        mProgress;
MyGUI::StaticTextPtr      mStatic;
BuildingManager          *mBuildMgr;
std::vector<std::string>  mOptions;
static unsigned short     mViews;
};

#endif // _BUILDINGVIEW_H_
