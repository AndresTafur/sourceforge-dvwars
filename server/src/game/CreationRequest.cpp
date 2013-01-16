#include "CreationRequest.h"

int CreationRequest::smCurrId = 0;

CreationRequest::CreationRequest(Game *game) : GameRequest(game)
{
    mConfirmed = false;
    mId = CreationRequest::smCurrId++;
}


    bool CreationRequest::doRequest(ClientAttender *clientAttender, std::vector<std::string> &params)
    {
      bool readyFlag = false;


                if( params[0] != "502" )
                {
                    mSquadType     = params[1];
                    mRequestclient = clientAttender;
                    mTarget        = static_cast<Player*>(clientAttender->getClient())->getWorkshop()->getTarget();
                    mLocation      = static_cast<Player*>(clientAttender->getClient())->getWorkshop()->getPosition();
                    this->startThread();
                }
                else
                {
                        if(mConfirmed )
                        {
                           mCreatedSqd->setPosition(mLocation);
                           mCreatedSqd->setPosition(mTarget);
                        }

                        if( mConfirmed == false )
                            mConfirmed = true;
                        else
                           readyFlag = true;
                }

                return readyFlag;
    }


    void CreationRequest::run()
    {
      unsigned int    total;
      unsigned short  owner;
      char            buff[100];
      Squad          *squad;
      Player         *player;



                        squad = mSquadBldr.createSquad(mSquadType);
                        total = squad->getTime();

                        squad->setGame(mGame);
                        mGame->getBoidContext()->addCrowd(boost::shared_ptr<Crowd>(squad));


                        for(unsigned int time = 0; time <= total; time++ )
                        {
                            sleep(1);
                            sprintf(buff,"502|%s|%f",mSquadType.c_str(), static_cast<float>(time*100/total) );
                            mRequestclient->getClient()->Send(buff);
                        }

                        player = static_cast<Player*>(mRequestclient->getClient());

                        player->addSquad(squad);
                        owner = mGame->indexOf(player)+1;
                        mCreatedSqd = squad;

                        sprintf(buff,"%i|%i|%i|%i",squad->getID(), owner, squad->getSize(), squad->getSpeed() );
                        mGame->sendMulticast("701|" + squad->getMesh() + "|" + buff);

                        fprintf(stderr,"\nCreation command sent waiting for confirmation...");
    }

CreationRequest::~CreationRequest()
{
    //dtor
}
