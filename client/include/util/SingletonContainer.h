#ifndef _SINGLETONCONTAINER_H
#define _SINGLETONCONTAINER_H

#include <map>
#include <string>

#include "Storable.h"

class SingletonContainer
{
private:
        /** Default constructor */
        SingletonContainer();

public:

        static SingletonContainer *getInstancePtr();

        static SingletonContainer &getInstance();

        void addObject(std::string key,Storable* obj);


        template<class Type>
        Type getObject(std::string key) {  return static_cast<Type>(mObjects[key]); }


        virtual ~SingletonContainer();

private:
std::map<std::string,Storable*> mObjects;
static SingletonContainer*  sm_instance;

};

#endif // _SINGLETONCONTAINER_H
