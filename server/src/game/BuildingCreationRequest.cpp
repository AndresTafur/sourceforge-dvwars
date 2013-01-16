#include "BuildingCreationRequest.h"

BuildingCreationRequest::BuildingCreationRequest(Game *game) :  GameRequest(game)
{
    //ctor
}



        bool BuildingCreationRequest::doRequest(ClientAttender *clientAttender, std::vector<std::string> &params)
        {
          ConfigReader reader;
          unsigned int cost;
          std::string  owner;
          std::string  mesh;
          std::string  expr;
          char idPlayer[30];

                reader.openFile("GameObjects.xml");

                sprintf(idPlayer,"%i",mGame->indexOf( static_cast<Player*>(clientAttender->getClient()))+1);
                owner = idPlayer;

                mType = params[1];
                mRequestclient = clientAttender;

                expr  = "/descendant::building[@name='" + mType ;
                mTime = atoi(reader.getAttribute(expr+"']/child::property[@name='buildTime']").c_str());
                cost  = atoi(reader.getAttribute(expr+"']/child::property[@name='cost']").c_str());
                mesh  = reader.getAttribute(expr+"']/child::property[@name='mesh']");

                mCommand = "702|"+mType+"|"+mesh+"|"+owner;
                this->startThread();

                return true;
        }


        void BuildingCreationRequest::run()
        {
          char buff[200];
          std::vector<Player*>  players;


                for(unsigned int time = 0; time <= mTime; time++ )
                {
                            sleep(1);
                            sprintf(buff,"501|%s|%i", mType.c_str(), static_cast<int>(time*100/mTime) );
                            mRequestclient->getClient()->Send(buff);

                            fprintf(stderr,"%s progress: %f\r", mType.c_str(), static_cast<float>(time*100/mTime) );
                }

                mGame->sendMulticast(mCommand);
        }

BuildingCreationRequest::~BuildingCreationRequest()
{
    this->joinThread();
}
