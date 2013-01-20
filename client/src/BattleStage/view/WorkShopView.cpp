#include "WorkShopView.h"

#include "util/ConfigReader.h"

WorkShopView::WorkShopView()
{
  ConfigReader reader;
  std::vector<std::string> options;
  MyGUI::WidgetPtr mainPanel;
  MyGUI::ButtonPtr btn;


                reader.openFile("requests.xml");

                mWShopMgr  = new WorkShopManager();
                mSelected  = false;

                options    = reader.getAttributes("/descendant::option[@name='workshop']/child::property[@name='building']");
                mainPanel  = MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("CreationPanel");

                MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("hideProgressPanel")->eventMouseButtonClick  += MyGUI::newDelegate(this, &WorkShopView::handleProgressPanel);
                MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("showProgressPanel")->eventMouseButtonClick  += MyGUI::newDelegate(this, &WorkShopView::handleProgressPanel);

                for(unsigned int i=0; i < options.size();i++)
                {
                        btn =  mainPanel->createWidget<MyGUI::Button>("Button", MyGUI::IntCoord(110+100*i,10,88,24), MyGUI::Align::Default, options[i] );
                        btn->setInheritsAlpha (false);
                        btn->setCaption(options[i]);
                        btn->eventMouseButtonClick  += MyGUI::newDelegate(this, &WorkShopView::createBuilding);
                        btn->eventMouseMove  += MyGUI::newDelegate(this, &WorkShopView::onHover);
                }


                mCreationLocation = new Indicator("CreationMark");
                mCreationLocation->setVisible(true);

                mWShopMgr->addCreationListener(this);
                SelectionManager::getInstance()->addSelectionListener(this);
}



        void WorkShopView::createBuilding(MyGUI::Widget* btn)
        {
            mWShopMgr->requestBuildingCreation( static_cast<MyGUI::ButtonPtr>(btn)->getCaption());
        }



        void WorkShopView::onProgressUpdate(size_t progress)
        {
              MyGUI::Gui::getInstance().findWidget<MyGUI::Progress>("Progress_main")->setProgressPosition(progress);
        }


        void WorkShopView::onCreateBuilding(Building *building)
        {
          BuildingView  *buildView;

                    if(building->getOwner() == Game::getInstancePtr()->getActivePlayer() )
                    {
                            buildView = new BuildingView(building);
                            mBuildingViews[building->getName()] = buildView;
                            MyGUI::Gui::getInstance().findWidget<MyGUI::Progress>("Progress_main")->setProgressPosition(0);
                    }
        }


        void WorkShopView::handleProgressPanel(MyGUI::Widget* btn)
        {
           MyGUI::WidgetPtr panel = MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("ProgressPanel");

                    if( btn == MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("hideProgressPanel")  )
                    {
                      panel->setVisible(false);
                      MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("showProgressPanel")->setVisible(true);
                    }
                    else
                    {
                      panel->setVisible(true);
                      MyGUI::Gui::getInstance().findWidget<MyGUI::Button>("showProgressPanel")->setVisible(false);
                    }
        }


        void WorkShopView::onHover(MyGUI::Widget* btn, int x, int y)
        {
           std::map<std::string,BuildingView*>::iterator iter;
           MyGUI::ButtonPtr  button = static_cast<MyGUI::ButtonPtr>(btn);

                for(iter = mBuildingViews.begin(); iter != mBuildingViews.end(); iter++ )
                        (*iter).second->hideView();

                if( mBuildingViews.find(button->getCaption()) != mBuildingViews.end() )
                    mBuildingViews[button->getCaption()]->showView();
        }

        void WorkShopView::onSelection(Ogre::MovableObject *ent,  OIS::MouseButtonID id)
        {
          GameObject *obj;

             if( ent->getQueryFlags() == TYPE_BUILDING )
             {
                 obj       =  Ogre::any_cast<Building*>(ent->getUserAny());
                 mSelected = (id == OIS::MB_Left and obj->getOwner() == Game::getInstancePtr()->getActivePlayer() );
                 MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("CreationPanel")->setVisible(mSelected);
             }
             else if( ent->getQueryFlags() == TYPE_WORKSHOP )
             {
                 obj       =  Ogre::any_cast<WorkShop*>(ent->getUserAny());
                 mSelected = (id == OIS::MB_Left and obj->getOwner() == Game::getInstancePtr()->getActivePlayer() );
                 MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("CreationPanel")->setVisible(mSelected);
             }
        }

        void WorkShopView::onWorldSelection(Ogre::SceneQuery::WorldFragment *ent,  OIS::MouseButtonID id)
        {
          Ogre::Vector3 pos( ent->singleIntersection.x,0,ent->singleIntersection.z);

                if( id == OIS::MB_Right && mSelected && mCreationLocation )
                {
                    mCreationLocation->setPosition(pos);
                    mWShopMgr->requestCreationTarget(pos);
                    mCreationLocation->setVisible(true);
                }
                else
                {
                    MyGUI::Gui::getInstance().findWidget<MyGUI::Widget>("CreationPanel")->setVisible(false);
                    mSelected = false;
                }
        }


WorkShopView::~WorkShopView()
{
    //dtor
}
