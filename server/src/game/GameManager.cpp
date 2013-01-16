#include "GameManager.h"

#include "MoveRequest.h"
#include "CreationRequest.h"
#include "ForestGenerator.h"
#include "BuildingCreationRequest.h"


GameManager::GameManager(ClientAttender* pl1, ClientAttender* pl2)
{
          mAttender1 = pl1;
          mAttender2 = pl2;
          mStart     = 0;
}



        void GameManager::manage(ClientAttender* attender, std::vector<std::string> &params)
        {
          GameRequest *request;


                if( params[0] == "701" )
                {
                    request = new CreationRequest(mGame);

                    request->doRequest(attender,params);
                    mPendingRequests.push( request );
                }
                else if( params[0] == "702" )
                {
                    request = new BuildingCreationRequest(mGame);
                    request->doRequest(attender,params);
                    delete request;
                }

                else if(params[0] =="503")
                {
                    Vector2 vect = Vector2::parseVector(params[1],'&');

                     static_cast<Player*>(attender->getClient())->getWorkshop()->setTarget( vect );
                     fprintf(stderr,"Target changed to: %f %f\n\n", vect.mXcoord, vect.mYcoord );
                }


                else if( params[0] == "710")
                {
                    request = new MoveRequest(mGame);

                    request->doRequest(attender,params);
                    delete request;
                }
                else if( params[0] == "501")
                {
                    mStart++;
                    if( mStart == 2 )
                    {
                        createWorkShops();
                        createNature();
                    }
                }
                else /*if( params[0] == "200")*/
                {
                    if( mPendingRequests.size() < 1 )
                        return;

                    request = mPendingRequests.front();
                    if( request->doRequest(attender,params)  )
                    {
                            mPendingRequests.pop();
                            delete request;
                    }
                }

            fprintf(stderr,"Param: %s.%i\n\n",params[0].c_str(),mPendingRequests.size());
        }


        void GameManager::startGame()
        {
                mAttender1->addRequestCtrl("200",this);
                mAttender1->addRequestCtrl("501",this);

                mAttender1->addRequestCtrl("701",this);
                mAttender1->addRequestCtrl("702",this);

                mAttender1->addRequestCtrl("710",this);
                mAttender1->addRequestCtrl("750",this);

                mAttender1->addRequestCtrl("502",this);
                mAttender1->addRequestCtrl("503",this);

                mAttender2->addRequestCtrl("200",this);
                mAttender2->addRequestCtrl("501",this);

                mAttender2->addRequestCtrl("701",this);
                mAttender2->addRequestCtrl("702",this);

                mAttender2->addRequestCtrl("710",this);
                mAttender2->addRequestCtrl("750",this);

                mAttender2->addRequestCtrl("502",this);
                mAttender2->addRequestCtrl("503",this);


                mAttender1->getClient()->Send("700|1");
                mAttender2->getClient()->Send("700|2");

                mGame = new Game();
                mGame->addPlayer( static_cast<Player*>(mAttender1->getClient()) );
                mGame->addPlayer( static_cast<Player*>(mAttender2->getClient()) );

                //TODO: Send map

        }


        void GameManager::createNature()
        {
          ForestGenerator fg;
          std::vector<Tree*>  trees;
          char buff[100];
          int x,y, dim;

                    x = y = dim = 0;

                        srand(time(NULL));
                        x   = rand()%15+1;
                        y   = rand()%15+1;
                        dim = rand()%10+1;

                        trees = fg.createForest(Vector2(x,y),dim,dim);

                        fprintf(stderr,"Sending %li trees\n", trees.size());

                        for(size_t i = 0; i < trees.size(); i ++)
                        {
                                sprintf(buff,"490|Tree.mesh|%f&%f",trees[i]->getPosition().mXcoord, trees[i]->getPosition().mYcoord);
                                mAttender1->getClient()->Send(buff);
                                mAttender2->getClient()->Send(buff);
                                sleep(0.1);
                        }
                        sprintf(buff,"490|Tree.mesh|-1&-1");
                        mAttender1->getClient()->Send(buff);
                        mAttender2->getClient()->Send(buff);
        }


        void GameManager::createWorkShops()
        {
          Vector2 pos1, pos2;
          char buff[200];

                    srand(time(NULL));

                    pos1.mXcoord = rand() % 500+100;
                    pos1.mYcoord = rand() % 500+100;
                    pos2.mXcoord = rand() % 500+900;
                    pos2.mYcoord = rand() % 500+900;

                    sprintf(buff,"500|1|WorkShop.mesh|%i&%i",(int)pos1.mXcoord,(int)pos1.mYcoord);
                    static_cast<Player*>(mAttender1->getClient())->setWorkshop( new Workshop(pos1) );
                    mAttender1->getClient()->Send(buff);
                    mAttender2->getClient()->Send(buff);

                    sprintf(buff,"500|2|WorkShop.mesh|%i&%i",(int)pos2.mXcoord,(int)pos2.mYcoord);
                    static_cast<Player*>(mAttender2->getClient())->setWorkshop( new Workshop(pos2) );
                    mAttender1->getClient()->Send(buff);
                    mAttender2->getClient()->Send(buff);

                    mAttender1->removeRequestCtrl("501");
                    mAttender2->removeRequestCtrl("501");
                    this->startThread();
        }


        void GameManager::run()
        {
          std::vector<Player*> players = mGame->getPlayers();

                while(!m_stoprequested)
                {
                    for(size_t i=0; i < players.size(); i++)
                            players[i]->setGold( players[i]->getGold() + 1 );
                    sleep(5);
                }


        }



GameManager::~GameManager()
{
    this->joinThread();
}
