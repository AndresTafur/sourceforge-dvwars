#ifndef _GAMEREQUEST_H_
#define _GAMEREQUEST_H_

#include "networking/ClientAttender.h"
#include "entity/Game.h"

/**
 * Interface to abstract GameRequest operations.
 */
class GameRequest
{
public:

        GameRequest(Game *game) { mGame = game; }

        //TODO: hacer el registro de actions como en el cliente
        virtual bool doRequest(ClientAttender *clientAttender, std::vector<std::string> &params) = 0;

protected:
Game *mGame;
};

#endif // _REQUEST_H_
