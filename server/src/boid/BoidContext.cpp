#include "BoidContext.h"

#include <stdlib.h>
#include <stdio.h>

BoidContext::BoidContext()
{
    for(int i = 0; i < VENTANA_MAX_X; i++)
        for(int j = 0; j < VENTANA_MAX_Y; j++)
            mDomainMatrix[i][j] = 0;

    for(int i = 0; i < VENTANA_MAX_X; i++)  mDomainMatrix[i][0] = -1;
    for(int i = 0; i < VENTANA_MAX_X; i++)  mDomainMatrix[i][(VENTANA_MAX_Y)-1] = -1;
    for(int i = 0; i < VENTANA_MAX_Y; i++)  mDomainMatrix[0][i] = -1;
    for(int i = 0; i < VENTANA_MAX_Y; i++)  mDomainMatrix[(VENTANA_MAX_X)-1][i] = -1;




    srand (time(NULL));
    for(int i = 0; i < CHAOS_SIZE; i++)
        chaos[i] = rand();

    mChaosCounter = 0;
}



    void BoidContext::addCrowd(boost::shared_ptr<Crowd> crd)
    {
        if( crd != NULL)
        {
            mCrowds.push_back(crd);
            crd->setBoidContext( this );
        }
    }


    void BoidContext::addObstacle(BoidObstacle *obj)
    {
      int x = int(obj->getPosition().mXcoord);
      int y = int(obj->getPosition().mYcoord);

                mDomainMatrix[x][y] = -1;
    }


    void BoidContext::addRule(boost::shared_ptr<Rule> rule)
    {
        if( rule != NULL)
        {
            mRules.push_back(rule);
        }
    }

    void BoidContext::run()
    {
      std::vector< boost::shared_ptr<Boid> > boids;
      size_t bsize;

                //while(!m_stoprequested)
                for(size_t i=0; i < 100;i++)
                {
                    for(size_t i = 0; i < mCrowds.size(); i++ )
                    {

                          boids = mCrowds[i]->getBoids();
                          bsize = boids.size();


                          for(size_t j = 0; j < bsize; j++ )
                                boids[j]->makePath();
                    }
                    sleep(0.001);
                }
    }


BoidContext::~BoidContext()
{
    this->stopThread();
}
