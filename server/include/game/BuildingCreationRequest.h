#ifndef BUILDINGCREATIONREQUEST_H
#define BUILDINGCREATIONREQUEST_H

#include <GameRequest.h>
#include <util/ConfigReader.h>


/**
 * Represents a request of building creation
 */
class BuildingCreationRequest : public GameRequest, public DaVinciWars::Thread
{
public:

        BuildingCreationRequest(Game *game);

        bool doRequest(ClientAttender *clientAttender, std::vector<std::string> &params);

        virtual ~BuildingCreationRequest();

protected:

        /**
         * Called by a thread to "time" the building progress.
         */
        void run();

private:
std::string     mCommand;
std::string     mType;
unsigned int    mTime;
ClientAttender *mRequestclient;
};

#endif // BUILDINGCREATIONREQUEST_H
