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

#include "ChatView.h"

ChatView::ChatView()
{
   MyGUI::Gui *bgy = MyGUI::Gui::getInstancePtr();


            mLayout   = GUI::getInstancePtr()->loadLayout("Chat.gui");
            mTab      = bgy->findWidget<MyGUI::Tab>("chatNB");
            mHide     = bgy->findWidget<MyGUI::Button>("chatHide");
            mShow     = bgy->findWidget<MyGUI::Button>("chatShow");
            mPrivate  = bgy->findWidget<MyGUI::Button>("privateChat");
            mMainChat = new ChatControl( mTab, "Main chat", "800|" );

            mHide->eventMouseButtonClick     += MyGUI::newDelegate(this, &ChatView::onHideChat);
            mShow->eventMouseButtonClick     += MyGUI::newDelegate(this, &ChatView::onShowChat);
            mPrivate->eventMouseButtonClick  += MyGUI::newDelegate(this, &ChatView::onPrivate);

            bgy->findWidget<MyGUI::Button>("privateOpen")->eventMouseButtonClick   +=  MyGUI::newDelegate(this, &ChatView::onPrivateOpen);
            bgy->findWidget<MyGUI::Button>("privateCancel")->eventMouseButtonClick +=  MyGUI::newDelegate(this, &ChatView::onPrivate);


            Client::getInstancePtr()->addListener(this);
}


    void ChatView::onHideChat(MyGUI::Widget* btn)
    {
            mHide->setVisible(false);
            mShow->setVisible(true);
            mTab->setVisible(false);
            mPrivate->setVisible(false);
    }


    void ChatView::onShowChat(MyGUI::Widget* btn)
    {
            mShow->setVisible(false);
            mHide->setVisible(true);
            mTab->setVisible(true);
            mPrivate->setVisible(true);
    }


    void ChatView::onPrivate(MyGUI::Widget* btn)
    {
        MyGUI::Gui *bgy = MyGUI::Gui::getInstancePtr();
        MyGUI::WindowPtr wnd = bgy->findWidget<MyGUI::Window>("privateChatDlg");
        bool visible = !wnd->getVisible();

                    wnd->setVisible( visible );
                    mPrivate->setStateSelected( visible );
    }


    void ChatView::onPrivateOpen(MyGUI::Widget* btn)
    {
      std::string tabName =  MyGUI::Gui::getInstancePtr()->findWidget<MyGUI::EditBox>("privateEditDlg")->getCaption();

                        mControls.insert( std::make_pair<std::string,ChatControl*>( tabName, new ChatControl( mTab, tabName, "810|" + tabName + "|" )) );
                        Client::getInstancePtr()->Send("810|"+tabName+"|Starting conversation...\n");
                        onPrivate(NULL);
    }



    void ChatView::attend(std::vector<std::string> &data)
    {
            if( data[0] == "800" )
                mMainChat->addMessage(data[1], data[2]);

            else if( data[0] == "810")
            {
                if(  mControls.find( data[1] ) == mControls.end() )
                    mControls.insert( std::make_pair<std::string,ChatControl*>( data[1], new ChatControl( mTab, data[1], "810|"+data[1]+"|" ) ) );

                mControls[data[1]]->addMessage(data[1],data[2]);
            }
            else if( data[0] == "811" && mControls.find( data[1] ) != mControls.end())
                mControls[data[1]]->addMessage(data[2],data[3]);
    }


ChatView::~ChatView()
{
     if(mMainChat != nullptr)
     {
        delete mMainChat;
        mMainChat = nullptr;
     }

     Client::getInstancePtr()->removeListener(this);
     GUI::getInstancePtr()->unloadLayout(mLayout);
     delete mMainChat;
}
