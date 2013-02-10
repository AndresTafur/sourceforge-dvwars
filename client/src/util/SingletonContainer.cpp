#include "SingletonContainer.h"


SingletonContainer* SingletonContainer::sm_instance = 0;


SingletonContainer::SingletonContainer()
{

}


        SingletonContainer* SingletonContainer::getInstancePtr()
        {
            if(!sm_instance)
                sm_instance = new SingletonContainer();

            return sm_instance;
        }

        SingletonContainer& SingletonContainer::getInstance()
        {
            if(!sm_instance)
                sm_instance = new SingletonContainer();

            return *sm_instance;
        }


        void SingletonContainer::addObject(std::string key, Storable* obj)
        {
            mObjects.insert( std::make_pair<std::string, Storable*>(key,obj)  );
        }


/*
        Storable* SingletonContainer::getObject(std::string key)
        {
            return mObjects[key];
        }

*/
SingletonContainer::~SingletonContainer()
{
    //dtor
}
