#include "BuildingView.h"

#include <util/ConfigReader.h>


unsigned short BuildingView::mViews = 0;


BuildingView::BuildingView(Building *building)
{
   ConfigReader reader;
   MyGUI::ButtonPtr  btn;
   MyGUI::WidgetPtr  panel;


                reader.openFile("requests.xml");

                mBuildMgr  = new BuildingManager(building);
                mOptions   = reader.getAttributes("/descendant::building[@name='"+ building->getName() +"']/child::property[@name='unitType']");
                panel      = MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("CreationPanel");


                for(unsigned int i=0; i < mOptions.size();i++)
                {

                    btn = panel->createWidget<MyGUI::Button>("Button", MyGUI::IntCoord(10+200*i,50,150,24), MyGUI::Align::Default, mOptions[i] );
                    btn->setInheritsAlpha (false);
                    btn->setCaption(mOptions[i]);
                    btn->eventMouseButtonClick  += MyGUI::newDelegate(this, &BuildingView::createSquad);
                }

                panel     = MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("ProgressPanel");
                mStatic   = panel->createWidget<MyGUI::TextBox>("StaticText", MyGUI::IntCoord(8,32+16*mViews,160,16), MyGUI::Align::Default);
                mProgress = static_cast<MyGUI::ProgressPtr>(panel->createWidgetT("Progress","ProgressFill", MyGUI::IntCoord(180,32+16*mViews,190,16), MyGUI::Align::Default));

                mStatic->setCaption(building->getName() +" inactive.");
                mProgress->setProgressRange(100);

                mBuildMgr->addCreationListener(this);
                mViews++;
}


        void BuildingView::createSquad(MyGUI::Widget* btn)
        {
            MyGUI::ButtonPtr button = static_cast<MyGUI::ButtonPtr>(btn);

                mBuildMgr->requestSquadCreation(  button->getCaption() );
                mStatic->setCaption(button->getCaption() + ".");
        }


        void BuildingView::onProgressUpdate(size_t val)
        {
                if( val == 100 )
                {
                        mStatic->setCaption(mBuildMgr->getBuilding()->getName() + " inactive.");
                        mProgress->setProgressPosition(0);
                        return;
                }
                mProgress->setProgressPosition(val);
        }


        void BuildingView::onCreateSquad(Squad *squad)
        {
                mProgress->setProgressPosition(0);
        }


        void BuildingView::showView()
        {
                for(size_t iter = 0; iter < mOptions.size(); iter++)
                   MyGUI::Gui::getInstance().findWidget<MyGUI::Button>( mOptions[iter]  )->setVisible(true);
        }

        void BuildingView::hideView()
        {
                for(size_t iter = 0; iter < mOptions.size(); iter++)
                   MyGUI::Gui::getInstance().findWidget<MyGUI::Button>( mOptions[iter]  )->setVisible(false);
        }




BuildingView::~BuildingView()
{
    //dtor
}
