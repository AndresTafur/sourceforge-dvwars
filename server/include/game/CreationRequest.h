#ifndef _CREATIONREQUEST_H_
#define _CREATIONREQUEST_H_

#include "SquadBuilder.h"
#include "GameRequest.h"
#include <util/Thread.h>

/**
 * Represents a unit/Squad creation request.
 * @see GameRequest
 */
class CreationRequest : public GameRequest, public DaVinciWars::Thread
{
public:

        CreationRequest(Game *game);

        bool doRequest(ClientAttender *clientAttender, std::vector<std::string> &params);

        virtual ~CreationRequest();

protected:

        /**
         * Time the squad building progress.
         */
        void run();

private:
SquadBuilder    mSquadBldr;
Squad          *mCreatedSqd;
bool            mConfirmed;
Vector2         mTarget;
Vector2         mLocation;

std::string     mSquadType;
ClientAttender *mRequestclient;
unsigned int    mId;
static   int    smCurrId;
};

#endif // _CREATIONREQUEST_H_
