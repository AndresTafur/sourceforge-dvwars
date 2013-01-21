#ifndef _BUILDINGMANAGER_H_
#define _BUILDINGMANAGER_H_


#include <GameObject.h>
#include <CreationListener.h>

#include <engine/Client.h>
#include <util/Cripto.h>

/**
 * Manage building unit creation and requests.
 **/
class BuildingManager : public ClientListener
{
public:

        BuildingManager(Building *building);



        void attend(std::vector<std::string> &data);

        /**
         *  Creates a new squad.
         *
         *  @param type Type of squad to be created
         *  @see SquadBuilder
         */
        void requestSquadCreation(std::string type);


        void addCreationListener(CreationListener *obj);


        inline Building* getBuilding() { return mBuilding; }

        virtual ~BuildingManager();


private:
Building    *mBuilding;
std::string  mQueuedType;
std::vector<CreationListener*> mListeners;
};

#endif // _BUILDINGMANAGER_H_
