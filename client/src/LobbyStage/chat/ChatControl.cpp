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

#include "ChatControl.h"
#include <engine/AbstractClient.h>

#include <util/SingletonContainer.h>

ChatControl::ChatControl(MyGUI::TabPtr noteBook, std::string tabName, std::string preData) : mPreData(preData)
{
  MyGUI::TabItemPtr  tab =  noteBook->addItem(tabName);

          mLogView = tab->createWidget<MyGUI::TextBox>("TextBox",4,6,356,234, MyGUI::Align::Default);
          mEdit    = tab->createWidget<MyGUI::EditBox>("EditBox",48,254,321,24, MyGUI::Align::Default);

          tab->createWidget<MyGUI::TextBox>("TextBox",4,254,44,18, MyGUI::Align::Default)->setCaption("Chat:");
          mEdit->setEditMultiLine(true);
          mEdit->setOverflowToTheLeft(true);

          mEdit->eventEditTextChange += MyGUI::newDelegate(this, &ChatControl::onMainTextChange);
}


        void ChatControl::onMainTextChange(MyGUI::EditBox *sender)
        {
          MyGUI::UString str =  sender->getOnlyText();
          size_t length = sender->getTextLength();


                if( length > 0 )
                    if(  str.at( sender->getTextLength()-1 ) == '\n')
                    {
                        SingletonContainer::getInstancePtr()->getObject<AbstractClient*>("client")->Send( mPreData + static_cast<std::string>( sender->getCaption() ) );
                        sender->eraseText(0, length );
                    }
        }


        void ChatControl::addMessage(std::string user, std::string message)
        {
            mLogView->setCaption( mLogView->getCaption() + user + ": "  + message + "\n" );
        }


ChatControl::~ChatControl()
{
    MyGUI::Gui::getInstance().destroyWidget(mLogView);
    MyGUI::Gui::getInstance().destroyWidget(mEdit);
}
