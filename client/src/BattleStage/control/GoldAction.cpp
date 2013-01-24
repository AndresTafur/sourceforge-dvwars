#include "GoldAction.h"

GoldAction::GoldAction()
{
    //ctor
}

        bool GoldAction::execute(const Ogre::FrameEvent &evt)
        {
            MyGUI::Gui::getInstance().findWidget<MyGUI::TextBox>("Gold")->setCaption("Gold:"+mParams[1]);
            return true;
        }



        void GoldAction::addParams(std::vector<std::string> params)
        {
                mObjectId = params[0]+params[1];
                mParams   = params;
       }


        std::string GoldAction::getObjectId()
        {
            return mObjectId;
        }


        Action* GoldAction::clone()
        {
            return new GoldAction();
        }



GoldAction::~GoldAction()
{
        fprintf(stderr,"Action %s Finished, destroying\n",mObjectId.c_str());
}
