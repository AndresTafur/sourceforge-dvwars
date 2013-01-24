#include "ChatControl.h"
#include <Client.h>

ChatControl::ChatControl(MyGUI::TabPtr noteBook, std::string tabName, std::string preData) : mPreData(preData)
{
  MyGUI::TabItemPtr  tab =  noteBook->addItem(tabName);

          mLogView =  tab->createWidget<MyGUI::TextBox>("TextBox",4,6,356,234, MyGUI::Align::Default);
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
                        Client::getInstancePtr()->Send( mPreData + static_cast<std::string>( sender->getCaption() ) );
                        sender->eraseText(0, length );
                    }
        }


        void ChatControl::addMessage(std::string user, std::string message)
        {
            mLogView->setCaption( mLogView->getCaption() + user + ": "  + message + "\n" );
        }


ChatControl::~ChatControl()
{
    //dtor
}
