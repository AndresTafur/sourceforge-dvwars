#include "ChatManager.h"

ChatManager::ChatManager()
{
    //ctor
}

        void ChatManager::manage(ClientAttender* attender, std::vector<std::string> &params)
        {
            //TODO: Make blacklists for users
            if( params[0] == "800" )
                sendToHall( static_cast<Player*>(attender->getClient()), params[1]);

            else if( params[0] == "810" )
                sendToUser( static_cast<Player*>(attender->getClient()), params[1], params[2]  );
        }


        void ChatManager::addPlayerAttender(ClientAttender *attender)
        {
          Player *pl;

            pl = static_cast<Player*>(attender->getClient());

            attender->addRequestCtrl("101",this);    //acceptChallenge
            attender->addRequestCtrl("800",this);    //Send to Hall
            attender->addRequestCtrl("810",this);    //Send to user

            mPlayers.insert( std::make_pair<std::string,ClientAttender*>(pl->getName(),attender) );
        }


        void ChatManager::sendToHall(Player *sender, std::string msg)
        {
            std::map<std::string, ClientAttender*>::iterator iter;
            Player *pl;


                    for( iter = mPlayers.begin(); iter != mPlayers.end(); iter++ )
                    {
                            pl = static_cast<Player*>((iter->second)->getClient());
                            pl->Send("800|"+ sender->getName()+"|"+ msg );
                    }
        }


        void ChatManager::sendToUser(Player *sender, std::string user, std::string msg)
        {

              if(  mPlayers.find(user) != mPlayers.end())
              {
                            mPlayers[user]->getClient()->Send("810|" + sender->getName() + "|" + msg);
                            sender->Send("811|" + user + "|"+ sender->getName()+ "|" + msg);
              }
              else
                 sender->Send("810|"+user+"|User is not online.");

        }


ChatManager::~ChatManager()
{
    //dtor
}
