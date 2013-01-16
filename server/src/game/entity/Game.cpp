#include "entity/Game.h"

Game::Game()
{
    mContext = boost::shared_ptr<BoidContext>( new BoidContext() );
}


    void Game::addPlayer(Player *player)
    {
        mPlayers.push_back(player);
    }

    void Game::addSquad(Squad *obj, unsigned int playerId)
    {
            mPlayers[playerId]->addSquad(obj);
            obj->setGame(this);
    }



    int Game::indexOf(Player *obj)
    {
          for(size_t i=0; i < mPlayers.size(); i++)
                if( mPlayers[i] == obj )
                        return i;
          return -1;
    }


    Squad* Game::getSquad(unsigned int idSquad)
    {
      Squad *resSquad = NULL;

            for(size_t i=0; i < mPlayers.size(); i++ )
            {
                    resSquad = mPlayers[i]->findSquad(idSquad);
                    if(resSquad != NULL)
                        return resSquad;
            }

        return NULL;
    }


    void Game::sendMulticast(std::string command)
    {
      size_t plyrs = mPlayers.size();

                for( size_t i=0; i < plyrs; i++ )
                    mPlayers[i]->Send(command);
    }

Game::~Game()
{

}
