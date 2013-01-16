#ifndef MOVEREQUEST_H
#define MOVEREQUEST_H

#include <GameRequest.h>

#include <boid/Cohesion.h>
#include <boid/Separation.h>
#include <boid/AligmentRule.h>
#include <boid/BoidContext.h>

/**
 * Hanldes a movement request. it use a boid context to calculate positions.
 * @see GameRequest
 */
class MoveRequest : public GameRequest
{
public:

        MoveRequest(Game *game);


        bool doRequest(ClientAttender *clientAttender, std::vector<std::string> &params);


        virtual ~MoveRequest();

};

#endif // MOVEREQUEST_H
