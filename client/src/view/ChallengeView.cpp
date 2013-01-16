#include "ChallengeView.h"
#include "GameObject.h"

ChallengeView::ChallengeView(Ogre::SceneManager *mgr) : mSceneManager(mgr), mCamera( mgr->getCamera("Login Camera") )
{
  MyGUI::Gui *bgy = MyGUI::Gui::getInstancePtr();
  GameObject    *obj  = new GameObject(0, mgr, "City.mesh");
  GameObject    *obj2 = new GameObject(0, mgr, "Village.mesh");

            bgy->findWidget<MyGUI::Widget>("userLbl")->setVisible(false);
            bgy->findWidget<MyGUI::Widget>("passLbl")->setVisible(false);
            bgy->findWidget<MyGUI::Widget>("user")->setVisible(false);
            bgy->findWidget<MyGUI::Widget>("pass")->setVisible(false);
            bgy->findWidget<MyGUI::Widget>("Login")->setVisible(false);
            bgy->findWidget<MyGUI::Widget>("Close")->setVisible(false);
            bgy->findWidget<MyGUI::Widget>("Back")->setVisible(false);

            mLayout    = MyGUI::LayoutManager::getInstance().load("Challenge.gui");
            mShowChall = bgy->findWidget<MyGUI::Button>("challengeDlg");
            mShowBud   = bgy->findWidget<MyGUI::Button>("buddiesDlg");

            mShowChall->eventMouseButtonClick = MyGUI::newDelegate(this, &ChallengeView::showChallenge);
            mShowBud->eventMouseButtonClick = MyGUI::newDelegate(this, &ChallengeView::showBuddies);

            bgy->findWidget<MyGUI::Button>("challengeBtn")->eventMouseButtonClick = MyGUI::newDelegate(this, &ChallengeView::doChallenge);
            bgy->findWidget<MyGUI::Button>("chllgCncl")->eventMouseButtonClick = MyGUI::newDelegate(this, &ChallengeView::showChallenge);
            MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::List>("PlayersList")->setVisible(false);

            mStatus     = 0;
            mWaitMsg    = NULL;
            mCameraNode = mgr->getSceneNode("Camera Node");

            Client::getInstancePtr()->addListener(this);
            Ogre::Root::getSingletonPtr()->addFrameListener(this);
            drawLine();


            obj->setPosition(Ogre::Vector3(30,0,250) );
            obj->getEntity()->setCastShadows(false);

            obj2->setPosition(Ogre::Vector3(30,-10,247) );
            obj2->getEntity()->setCastShadows(false);


            mChatView = new ChatView();
}


    void ChallengeView::drawLine()
    {
      Ogre::ManualObject* myManualObject  =  mSceneManager->createManualObject("manual1");
      Ogre::SceneNode* myManualObjectNode = mSceneManager->getRootSceneNode()->createChildSceneNode("manual1_node");

            myManualObject->begin("BlueLineMaterial", Ogre::RenderOperation::OT_LINE_LIST);
            myManualObject->position(30, 0, 247);
            myManualObject->position(30, 0, 250);

            // etc
            myManualObject->end();
            myManualObjectNode->attachObject(myManualObject);
    }


    void ChallengeView::doChallenge(MyGUI::Widget* btn)
    {
      std::string val;
      MyGUI::ListPtr list = MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::List>("PlayersList");
      size_t selected;

            selected = list->getIndexSelected();

            if( selected == MyGUI::ITEM_NONE)
            {
                    MyGUI::Message::createMessageBox("Message",Ogre::String("Challenge"),"You must choose a player to challenge.", MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                    return;
            }

            val = list->getItemNameAt(selected);
            Client::getInstancePtr()->Send("302|"+val);
            list->removeAllItems();
            mWaitMsg = MyGUI::Message::createMessageBox("Message",Ogre::String("Challenge"),"Waiting for other player to accept or reject your challenge.", MyGUI::MessageBoxStyle::IconInfo);
    }



    void ChallengeView::showChallenge(MyGUI::Widget* btn)
    {
      MyGUI::WindowPtr wnd = MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::Window>("PlayersWND");
      bool visible = !wnd->isVisible();

            wnd->setVisible(visible);
            mShowChall->setButtonPressed( visible );

            MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::List>("PlayersList")->setVisible(visible);

            if(visible)
                Client::getInstancePtr()->Send("303");
    }


    void ChallengeView::showBuddies(MyGUI::Widget* btn)
    {
      MyGUI::WindowPtr wnd = MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::Window>("BuddieWND");
      bool visible = !wnd->isVisible();

            wnd->setVisible(visible);
            mShowBud->setButtonPressed( visible );
    }



    void ChallengeView::onAcceptDecline(MyGUI::MessagePtr sender, MyGUI::MessageBoxStyle result)
    {
            if (result == MyGUI::MessageBoxStyle::No)
                Client::getInstancePtr()->Send("100");
            else
                Client::getInstancePtr()->Send("101");
    }



    void ChallengeView::disable()
    {
        MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mLayout);
        Ogre::Root::getSingletonPtr()->removeFrameListener(this);


                Client::getInstancePtr()->removeListener(this);

                if(mWaitMsg)
                {
                    mWaitMsg->destroySmooth();
                    mWaitMsg = NULL;
                }
    }


    void ChallengeView::attend(std::vector<std::string> &data)
    {
       MyGUI::Gui *bgy =  MyGUI::Gui::getInstancePtr();
       std::string val;
       char buffer[100];
       MyGUI::ListPtr list;

            mParams = data;


            if( data[0].compare("300") == 0)
            {
                   bgy->findWidget<MyGUI::List>("PlayersList")->removeAllItems();
                   bgy->findWidget<MyGUI::StaticText>("playersNum")->setCaption("Players: 0");
            }
            else if( data[0].compare("301") == 0 )
            {
                   list = MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::List>("PlayersList");

                   list->addItem(data[1]);

                   sprintf(buffer,"Players: %ui", (unsigned int)list->getItemCount() );
                   bgy->findWidget<MyGUI::StaticText>("playersNum")->setCaption(buffer);
            }
            else if( data[0].compare("302") == 0 )
                   mStatus = 302;
            else if( data[0] == "100" )
                   mStatus = 100;
    }


    bool ChallengeView::frameEnded(const Ogre::FrameEvent& evt)
    {
            if( mStatus == 302)
            {
              std::string val;
              MyGUI::Message* msg;


                    val = mParams[1] + " has challenged you,\n accept challenge?";
                    msg = MyGUI::Message::createMessageBox("Message",Ogre::String("Challenge"),val, MyGUI::MessageBoxStyle::IconInfo|MyGUI::MessageBoxStyle::Yes|MyGUI::MessageBoxStyle::No);

                    MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::List>("PlayersList")->removeAllItems();
                    msg->setMessageModal(true);
                    msg->eventMessageBoxResult = MyGUI::newDelegate(this, &ChallengeView::onAcceptDecline);

                    mStatus = 0;
            }
            else if( mStatus == 100)
            {
                    MyGUI::Message::createMessageBox("Message",Ogre::String("Challenge"),"Your oponent has rejected the challenge.", MyGUI::MessageBoxStyle::IconInfo|MyGUI::MessageBoxStyle::Ok);
                    mWaitMsg->destroySmooth();
                    mStatus = 0;
            }


            if(  mCameraNode->getPosition() != Ogre::Vector3(30,8,240) )
            {
                    mCameraNode->setPosition( mCameraNode->getPosition() +(Ogre::Vector3(30,8,240) - mCameraNode->getPosition() )*evt.timeSinceLastFrame);
                    mCamera->lookAt(30,2,245);
            }


        return true;
    }


ChallengeView::~ChallengeView()
{

        MyGUI::LayoutManager::getInstancePtr()->unloadLayout(mLayout);
        Ogre::Root::getSingletonPtr()->removeFrameListener(this);

        if(mWaitMsg)
        {
            mWaitMsg->destroySmooth();
            mWaitMsg = NULL;
        }


        if( mChatView )
        {
            delete mChatView;
            mChatView = NULL;
        }
}
