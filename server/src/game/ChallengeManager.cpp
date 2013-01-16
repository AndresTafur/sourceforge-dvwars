#include "ChallengeManager.h"
#include <stdio.h>


ChallengeManager::ChallengeManager()
{
    //ctor
}



   void ChallengeManager::manage(ClientAttender* attender, std::vector<std::string> &params)
   {
     Player         *player = static_cast<Player*>( attender->getClient() );
     Player         *player2;
     GameManager    *gameMgr;
     ClientAttender *otherPlayer;

                fprintf(stderr,"DATA: {%s}",params[0].c_str());

                if( params[0] == "303")
                    sendActivePlayers(player);

                else if( params[0] == "302" )
                {
                    otherPlayer = mPlayers[params[1]];
                    player2 = static_cast<Player*>( otherPlayer->getClient() );


                    gameMgr = new GameManager(attender, otherPlayer);
                    mGames.insert( std::make_pair<std::string,GameManager*>( player2->getName(),gameMgr ) );

                    mPlayers.erase( player->getName()  );
                    mPlayers.erase( player2->getName() );

                    player2->Send( "302|" + player->getName()  );
                    sendActivePlayers();

                    fprintf(stderr,"PlayerGame: %s\n", player2->getName().c_str());
                }
                else if( params[0] == "101")
                     mGames[player->getName()]->startGame();
                else if( params[0] == "100")
                {
                    gameMgr     = mGames[player->getName()];
                    otherPlayer = gameMgr->getAttender1();
                    player2     = static_cast<Player*>( otherPlayer->getClient() );


                    mPlayers.insert( std::make_pair<std::string,ClientAttender*>(player2->getName(), otherPlayer) );
                    mPlayers.insert( std::make_pair<std::string,ClientAttender*>(player->getName(), attender) );
                    mGames.erase( player->getName() );
                    player2->Send("100");

                    sendActivePlayers();
                    delete gameMgr;
                }
                else
                fprintf(stderr,"Unknown\n");
   }


   void ChallengeManager::addPlayerAttender(ClientAttender *attender)
   {
      Player *pl;

            pl = static_cast<Player*>(attender->getClient());

            attender->addRequestCtrl("101",this);    //acceptChallenge
            attender->addRequestCtrl("100",this);    //declineChallenge
            attender->addRequestCtrl("303",this);    //get player list
            attender->addRequestCtrl("302",this);    //challengePlayer

            mPlayers.insert( std::make_pair<std::string,ClientAttender*>(pl->getName(),attender) );
   }


   void ChallengeManager::sendActivePlayers()
   {
     std::map<std::string, ClientAttender*>::iterator iter;
     Client *clt;

            fprintf(stderr,"Sending active players...\n");

            for(iter = mPlayers.begin(); iter != mPlayers.end(); iter++ )
            {
                    clt = (*iter).second->getClient();
                    sendActivePlayers(clt);
            }
   }


   void ChallengeManager::sendActivePlayers(Client *clt)
   {
     std::map<std::string, ClientAttender*>::iterator iter;
     Player *pl;

                    clt->Send("300");

                    for( iter = mPlayers.begin(); iter != mPlayers.end(); iter++ )
                    {
                            pl = static_cast<Player*>((iter->second)->getClient());

                            if( pl != clt )
                                clt->Send("301|"+ pl->getName() );
                    }
   }



ChallengeManager::~ChallengeManager()
{
    //dtor
}
