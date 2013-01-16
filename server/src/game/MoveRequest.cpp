#include "MoveRequest.h"

MoveRequest::MoveRequest(Game *game) : GameRequest(game)
{

}


    bool MoveRequest::doRequest(ClientAttender *clientAttender, std::vector<std::string> &params)
    {
      Squad          *squad;
      Vector2         posCast;
      unsigned int    squadID;
      Vector2         vectorTarget;
      std::vector<Vector2> positions;

                     squadID      = atoi(params[1].c_str());
                     squad        = mGame->getSquad(squadID);
                     vectorTarget = Vector2::parseVector(params[2],'&');

                     squad->setPosition(vectorTarget);
                     return true;
    }


MoveRequest::~MoveRequest()
{

}
