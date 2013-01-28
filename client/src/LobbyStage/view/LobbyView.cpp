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

#include "LobbyView.h"
#include "GameObject.h"


#include <LoginStage/control/LoginSceneManager.h>

void LobbyView::create( Ogre::RenderTarget* wnd)
{
            Scene::create(wnd);

            mStatus     = 0;
//            mWaitMsg    = NULL;

}


        void LobbyView::createCamera()
        {
           Scene::createCamera();
           GameObject *obj;
           GameObject *obj2;
           Ogre::SceneNode *mTableNode, *mScrollNode;
           Ogre::Entity    *mTable, *mScroll;


                obj   = new GameObject(0, mSceneMgr, "City.mesh");
                obj2  = new GameObject(0, mSceneMgr, "Village.mesh");

                obj->setPosition(Ogre::Vector3(30,0,250) );
                obj->getEntity()->setCastShadows(false);

                obj2->setPosition(Ogre::Vector3(30,-10,247) );
                obj2->getEntity()->setCastShadows(false);

                mTable      = mSceneMgr->createEntity( "Pedestal.mesh"  );
                mTableNode  = mSceneMgr->getRootSceneNode()->createChildSceneNode();
                mTableNode->attachObject(mTable);
                mTableNode->setPosition(30,-10,250);

                mScroll     = mSceneMgr->createEntity( "Scroll.mesh"  );
                mScrollNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
                mScroll->setCastShadows(false);
                mScrollNode->attachObject(mScroll);
                mScrollNode->setPosition(34,-1,247);
        }




        void LobbyView::createGui()
        {
            MyGUI::Gui *bgy;


                    GUI::getInstancePtr()->initialize( mWindow,mSceneMgr);

                    bgy  = MyGUI::Gui::getInstancePtr();

                    mChatView  = new ChatView();
                    mLayout    = GUI::getInstance().loadLayout("Lobby.gui");


                    mShowBud   = bgy->findWidget<MyGUI::Button>("buddiesBtn");
                    mShowBud->eventMouseButtonClick += MyGUI::newDelegate(this, &LobbyView::showBuddies);


                    bgy->findWidget<MyGUI::Button>("showChallengeBtn")->eventMouseButtonClick += MyGUI::newDelegate(this, &LobbyView::showChallenge);
                    //bgy->findWidget<MyGUI::Button>("challengeBtn")->eventMouseButtonClick += MyGUI::newDelegate(this, &LobbyView::doChallenge);

                    bgy->findWidget<MyGUI::Button>("quitBtn")->eventMouseButtonClick += MyGUI::newDelegate(this, &LobbyView::onQuit);

                    //ensure created in last place
                    Client::getInstancePtr()->addListener(this);
                    Ogre::Root::getSingletonPtr()->addFrameListener(this);
                    drawLine();
        }


        std::string LobbyView::getName() {
                return "Lobby";
        }




    void LobbyView::drawLine()
    {
      Ogre::ManualObject* myManualObject  = mSceneMgr->createManualObject("manual1");
      Ogre::SceneNode* myManualObjectNode = mSceneMgr->getRootSceneNode()->createChildSceneNode("manual1_node");

            myManualObject->begin("BlueLineMaterial", Ogre::RenderOperation::OT_LINE_LIST);
            myManualObject->position(30, 0, 247);
            myManualObject->position(30, 0, 250);

            // etc
            myManualObject->end();
            myManualObjectNode->attachObject(myManualObject);
    }


    void LobbyView::doChallenge(MyGUI::Widget* btn)
    {
      std::string val;
      MyGUI::ListPtr list = MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::ListBox>("PlayersList");
      size_t selected;

            selected = list->getIndexSelected();

            if( selected == MyGUI::ITEM_NONE)
            {
//                    MyGUI::Message::createMessageBox("Message",Ogre::String("Challenge"),"You must choose a player to challenge.", MyGUI::MessageBoxStyle::IconError|MyGUI::MessageBoxStyle::Ok);
                    return;
            }

            val = list->getItemNameAt(selected);
            Client::getInstancePtr()->Send("302|"+val);
            list->removeAllItems();
          //  mWaitMsg = MyGUI::Message::createMessageBox("Message",Ogre::String("Challenge"),"Waiting for other player to accept or reject your challenge.", MyGUI::MessageBoxStyle::IconInfo);
    }



    void LobbyView::showChallenge(MyGUI::Widget* btn)
    {/*
      MyGUI::WindowPtr wnd = MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::Window>("challengeWnd");
      bool visible = !wnd->getVisible();

            wnd->setVisible(visible);
            mShowChall->setStateSelected( visible );*/
    }


    void LobbyView::showBuddies(MyGUI::Widget* btn)
    {
      MyGUI::WindowPtr wnd = MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::Window>("buddiesWnd");
      bool visible = !wnd->getVisible();

            wnd->setVisible(visible);
            mShowBud->setStateSelected( visible );
    }


    void LobbyView::onQuit(MyGUI::Widget* btn)
    {
        endScene(0);
    }


/*    void LobbyView::onAcceptDecline(MyGUI::MessagePtr sender, MyGUI::MessageBoxStyle result)
    {
            if (result == MyGUI::MessageBoxStyle::No)
                Client::getInstancePtr()->Send("100");
            else
                Client::getInstancePtr()->Send("101");
    }
*/



    void LobbyView::attend(std::vector<std::string> &data)
    {
       MyGUI::Gui *bgy =  MyGUI::Gui::getInstancePtr();
       std::string val;
       char buffer[100];
       MyGUI::ListPtr list;

            mParams = data;


            if( data[0].compare("300") == 0)
            {
                   bgy->findWidget<MyGUI::ListBox>("PlayersList")->removeAllItems();
                   bgy->findWidget<MyGUI::TextBox>("playersNum")->setCaption("Players: 0");
            }
            else if( data[0].compare("301") == 0 )
            {
                   list = MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::ListBox>("PlayersList");

                   list->addItem(data[1]);

                   sprintf(buffer,"Players: %ui", (unsigned int)list->getItemCount() );
                   bgy->findWidget<MyGUI::TextBox>("playersNum")->setCaption(buffer);
            }
            else if( data[0].compare("302") == 0 )
                   mStatus = 302;
            else if( data[0] == "100" )
                   mStatus = 100;
    }


    bool LobbyView::frameEnded(const Ogre::FrameEvent& evt)
    {
            if( mStatus == 302)
            {
              std::string val;
//              MyGUI::Message* msg;


                    val = mParams[1] + " has challenged you,\n accept challenge?";
//                    msg = MyGUI::Message::createMessageBox("Message",Ogre::String("Challenge"),val, MyGUI::MessageBoxStyle::IconInfo|MyGUI::MessageBoxStyle::Yes|MyGUI::MessageBoxStyle::No);

                    MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::ListBox>("PlayersList")->removeAllItems();
           //         msg->setMessageModal(true);
           //         msg->eventMessageBoxResult = MyGUI::newDelegate(this, &LobbyView::onAcceptDecline);

                    mStatus = 0;
            }
            else if( mStatus == 100)
            {
//                    MyGUI::Message::createMessageBox("Message",Ogre::String("Challenge"),"Your oponent has rejected the challenge.", MyGUI::MessageBoxStyle::IconInfo|MyGUI::MessageBoxStyle::Ok);
 //                   mWaitMsg->destroySmooth();
                    mStatus = 0;
            }


            if(  mCameraNode->getPosition() != Ogre::Vector3(30,8,240) )
            {
                    mCameraNode->setPosition( mCameraNode->getPosition() +(Ogre::Vector3(30,8,240) - mCameraNode->getPosition() )*evt.timeSinceLastFrame);
                    mCamera->lookAt(30,2,245);
            }


        return true;
    }


    void LobbyView::destroy()
    {
            if( mChatView )
            {
                delete mChatView;
                mChatView = NULL;
            }

            /*        if(mWaitMsg)
            {
                mWaitMsg->destroySmooth();
                mWaitMsg = NULL;
            }
            */
            Client::getInstancePtr()->removeListener(this);
            Ogre::Root::getSingletonPtr()->removeFrameListener(this);
            GUI::getInstancePtr()->unloadLayout(mLayout);
            GUI::getInstancePtr()->clean();
            //delete mLogSceneMgr;

            Scene::destroy();
    }



LobbyView::~LobbyView()
{




}
