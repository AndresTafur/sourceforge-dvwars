#ifndef _ACTIONFACTORY_H_
#define _ACTIONFACTORY_H_

#include <map>

#include "Action.h"

/**
 * Handles every clonnable action.
 */
class ActionFactory
{
public:

        ActionFactory();

        /**
         * Obtains an action based on ID
         * @return New object that handles the ID.
         */
        Action* getAction(std::string id);

        /**
         * Registers a new clonable action.
         * @param obj Clonable action object.
         */
        void registerAction(Action* obj );

        virtual ~ActionFactory();

private:
std::map<std::string,Action*> mActions;
};

#endif // _COMMANDMANAGERFACTORY_H_
