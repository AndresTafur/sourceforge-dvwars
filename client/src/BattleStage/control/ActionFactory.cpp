#include "ActionFactory.h"

ActionFactory::ActionFactory()
{
    //ctor
}


    Action* ActionFactory::getAction(std::string id)
    {
      std::map<std::string, Action*>::iterator it;

             it = mActions.find(id);

             if( it != mActions.end() )
                 return it->second->clone();

            return NULL;
    }


    void ActionFactory::registerAction(Action* obj )
    {
            mActions.insert( std::make_pair<std::string,Action*>( obj->getActionID(),obj) );
    }


ActionFactory::~ActionFactory()
{
   //TODO: Iterate and destroy action objects
}
