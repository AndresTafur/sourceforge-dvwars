#include "BuildingManager.h"

BuildingManager::BuildingManager(Building *building)
{
   mBuilding = building;
   Client::getInstancePtr()->addListener(this);
}

        void BuildingManager::attend(std::vector<std::string> &data)
        {
                    if(data[0] == "502" and data[1] == mQueuedType)
                    {
                        for(size_t iter = 0; iter < mListeners.size(); iter++)
                            mListeners[iter]->onProgressUpdate( atoi(data[2].c_str()));
                    }
        }

        void BuildingManager::requestSquadCreation(std::string type)
        {
             mQueuedType = type;
             Client::getInstancePtr()->Send( "701|"+type  );
        }

        void BuildingManager::addCreationListener(CreationListener *obj)
        {
            mListeners.push_back(obj);
        }

BuildingManager::~BuildingManager()
{
    //dtor
}
