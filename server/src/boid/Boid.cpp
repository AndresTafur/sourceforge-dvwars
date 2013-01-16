#include "Boid.h"
#include "BoidContext.h"
#include "Crowd.h"

#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include <boid/Separation.h>

Boid::Boid()
{

    for(int i = 0; i < MAX_PATHS; i++)
    {
        mMyPath[i][0] = -1;
        mMyPath[i][1] = -1;
    }

    mPathCounter = 0;
    mTendency    = INITIAL_TENDENCY;

    for(int i = 0; i < VENTANA_MAX_X/PATH; i++)
        for(int j = 0; j < VENTANA_MAX_Y/PATH; j++)
        {
            mPathMatrix[i][j][0] = -1;
            mPathMatrix[i][j][1] = -1;
        }
}


        void Boid::setCaptain(boost::shared_ptr<Boid> cap)
        {
            mCapitan = cap;
        }


        void Boid::setContext(BoidContext *cont)
        {
                    mContext = cont;
        }


        void Boid::move(Vector2 target)
        {
            mTendency = INITIAL_TENDENCY; // The Tendency is inversely proportional to entropy

            while( pathFinder(target) == 1 && mTendency > 2)
            {
                mTendency = mTendency/2;
                std::cout << "Tendencia: " << mTendency<<"\n";
            }

        }


        void Boid::makePath()
        {
          std::vector< boost::shared_ptr<Boid> > array;
          size_t size;


                    if(mMyPath[mPathCounter][0] != -1 && mPathCounter < MAX_PATHS)
                    {
                                if(mCapitan.get() == this)
                                {
                                        array = mBelongCrowd->getBoids();
                                        size  = array.size();

                                        for(size_t i = 1; i < size; i++)
                                                if(array[i]->mMyPath[0][0] == -1)
                                                     array[i]->move(Vector2(mMyPath[mPathCounter][0], mMyPath[mPathCounter][1]) );

                                        if(mPathCounter < MAX_PATHS-1 && mMyPath[mPathCounter+1][0] == -1)
                                                for(size_t i = 1; i < array.size(); i++)
                                                    array[i]->move( Vector2(mMyPath[mPathCounter][0], mMyPath[mPathCounter][1]) );
                                }

                                this->setPosition( Vector2( mMyPath[mPathCounter][0], mMyPath[mPathCounter][1] ));
                                mPathCounter++;
                     }
                     else
                     {
                                mMyPath[0][0] = -1;
                                mMyPath[0][1] = -1;
                                mPathCounter = 0;
                     }

        }




        int Boid::pathFinder(Vector2 target)
        {
          int probOctantes[8], dy, dx, sum, maxProb, decision, X, Y;
          int Counter = 0, cycles = 0;
          int x1, y1, x2, y2;

                            x1 = mPos.mXcoord;
                            y1 = mPos.mYcoord;

                            x2 = target.mXcoord;
                            y2 = target.mYcoord;


                            for(int i = 0; i < 1500/PATH; i++)
                                    for(int j = 0; j < 1500/PATH; j++)
                                    {
                                            mPathMatrix[i][j][0] = -1;	// UnitID
                                            mPathMatrix[i][j][1] = -1;	// Counter when unit passed
                                    }

                            X = x1;
                            Y = y1;

                            mMyPath[mPathCounter][0] = -1;	// Stop actual path
                            mMyPath[mPathCounter][1] = -1;
                            mMyPath[0][0] = -1;
                            mMyPath[0][1] = -1;
                            mPathCounter = 0;

                            Counter = 0;
                            sum = 11;

                            for(int i = 0; i < 8; i++)
                                    probOctantes[i] = 1;

                            while(sum > 2 && cycles < MAX_PATHS)
                            {
                                    cycles++;
                                    dx  = abs(x2 - X);
                                    dy  = abs(y2 - Y);
                                    sum = dx+dy;

                                    if(mContext->mDomainMatrix[X+1][Y] < 0)
                                    {
                                            probOctantes[0] = 1;
                                            probOctantes[3]= probOctantes[3]+(mTendency/2);
                                            probOctantes[4]= probOctantes[4]+mTendency;
                                            probOctantes[5]= probOctantes[5]+(mTendency/2);
                                    }

                                    if(mContext->mDomainMatrix[X+1][Y+1] < 0)
                                    {
                                            probOctantes[1] = 1;
                                            probOctantes[4]= probOctantes[4]+(mTendency/2);
                                            probOctantes[5]= probOctantes[5]+mTendency;
                                            probOctantes[3]= probOctantes[3]+(mTendency/2);
                                    }

                                    if(mContext->mDomainMatrix[X][Y+1] < 0)
                                    {
                                            probOctantes[2] = 1;
                                            probOctantes[5]= probOctantes[5]+(mTendency/2);
                                            probOctantes[6]= probOctantes[6]+mTendency;
                                            probOctantes[7]= probOctantes[7]+(mTendency/2);
                                    }
                                    if(mContext->mDomainMatrix[X-1][Y+1] < 0)
                                    {
                                            probOctantes[3] = 1;
                                            probOctantes[6]= probOctantes[6]+(mTendency/2);
                                            probOctantes[7]= probOctantes[7]+mTendency;
                                            probOctantes[0]= probOctantes[0]+(mTendency/2);
                                    }
                                    if(mContext->mDomainMatrix[X-1][Y] < 0)
                                    {
                                            probOctantes[4] = 1;
                                            probOctantes[7]= probOctantes[7]+(mTendency/2);
                                            probOctantes[0]= probOctantes[0]+mTendency;
                                            probOctantes[1]= probOctantes[1]+(mTendency/2);
                                    }
                                    if(mContext->mDomainMatrix[X-1][Y-1] < 0)
                                    {
                                            probOctantes[5] = 1;
                                            probOctantes[0]= probOctantes[0]+(mTendency/2);
                                            probOctantes[1]= probOctantes[1]+mTendency;
                                            probOctantes[2]= probOctantes[2]+(mTendency/2);
                                    }
                                    if(mContext->mDomainMatrix[X][Y-1] < 0)
                                    {
                                            probOctantes[6] = 1;
                                            probOctantes[1]= probOctantes[1]+(mTendency/2);
                                            probOctantes[2]= probOctantes[2]+mTendency;
                                            probOctantes[3]= probOctantes[3]+(mTendency/2);
                                    }
                                    if(mContext->mDomainMatrix[X+1][Y-1] < 0)
                                    {
                                            probOctantes[7] = 1;
                                            probOctantes[2]= probOctantes[2]+(mTendency/2);
                                            probOctantes[3]= probOctantes[3]+mTendency;
                                            probOctantes[4]= probOctantes[4]+(mTendency/2);
                                    }

                                    if(x2>X)
                                    {
                                            probOctantes[7]= probOctantes[7]+(mTendency/2);
                                            probOctantes[0]= probOctantes[0]+mTendency;
                                            probOctantes[1]= probOctantes[1]+(mTendency/2);
                                    }
                                    else if(x2<X)
                                    {
                                            probOctantes[5]= probOctantes[5]+(mTendency/2);
                                            probOctantes[4]= probOctantes[4]+mTendency;
                                            probOctantes[3]= probOctantes[3]+(mTendency/2);
                                    }
                                    if(y2>Y)
                                    {
                                            probOctantes[1]= probOctantes[1]+(mTendency/2);
                                            probOctantes[2]= probOctantes[2]+mTendency;
                                            probOctantes[3]= probOctantes[3]+(mTendency/2);
                                    }
                                    else if(y2<Y)
                                    {
                                            probOctantes[5]= probOctantes[5]+(mTendency/2);
                                            probOctantes[6]= probOctantes[6]+mTendency;
                                            probOctantes[7]= probOctantes[7]+(mTendency/2);
                                    }

                                    maxProb  = probOctantes[0]+probOctantes[1]+probOctantes[2]+probOctantes[3]+probOctantes[4]+probOctantes[5]+probOctantes[6]+probOctantes[7];
                                    decision = mContext->randomInteger()%maxProb;

                                    if(decision < probOctantes[0])
                                    {
                                            if(mContext->mDomainMatrix[X+1][Y] != -1)
                                                            X++;

                                    }
                                    else if(decision < probOctantes[0]+probOctantes[1])
                                    {
                                                if(mContext->mDomainMatrix[X+1][Y+1] != -1){
                                                                        X++;
                                                                        Y++;
                                                }
                                    }
                                    else if(decision < probOctantes[0]+probOctantes[1]+probOctantes[2])
                                    {
                                            if(mContext->mDomainMatrix[X][Y+1] != -1)
                                                    Y++;

                                    }
                                    else if(decision < probOctantes[0]+probOctantes[1]+probOctantes[2]+probOctantes[3])
                                    {
                                            if(mContext->mDomainMatrix[X-1][Y+1] != -1){
                                                    X--;
                                                    Y++;
                                            }
                                    }
                                    else if(decision < probOctantes[0]+probOctantes[1]+probOctantes[2]+probOctantes[3]+probOctantes[4])
                                    {
                                                if(mContext->mDomainMatrix[X-1][Y] != -1)
                                                        X--;

                                    }
                                    else if(decision < probOctantes[0]+probOctantes[1]+probOctantes[2]+probOctantes[3]+probOctantes[4]+probOctantes[5])
                                    {
                                            if(mContext->mDomainMatrix[X-1][Y-1] != -1){
                                                    X--;
                                                    Y--;
                                            }
                                    }
                                    else if(decision < probOctantes[0]+probOctantes[1]+probOctantes[2]+probOctantes[3]+probOctantes[4]+probOctantes[5]+probOctantes[6])
                                    {
                                            if(mContext->mDomainMatrix[X][Y-1] != -1)
                                                            Y--;

                                    }
                                    else if(decision < probOctantes[0]+probOctantes[1]+probOctantes[2]+probOctantes[3]+probOctantes[4]+probOctantes[5]+probOctantes[6]+probOctantes[7])
                                    {
                                                if(mContext->mDomainMatrix[X+1][Y-1] != -1){
                                                            X++;
                                                            Y--;
                                                }
                                    }

                                    if(mPathMatrix[X][Y][0] == 10)
                                    {
                                                for(int i = mPathMatrix[X][Y][1]; i < Counter; i++)
                                                    mPathMatrix[mMyPath[i][0]][mMyPath[i][1]][0] = -1;
                                                Counter = mPathMatrix[X][Y][1];
                                    }
                                    else
                                    {
                                            mPathMatrix[X][Y][0] = 10;
                                            mPathMatrix[X][Y][1] = Counter;
                                    }

                                    mMyPath[Counter][0] = X;
                                    mMyPath[Counter][1] = Y;
                                    Counter++;

                                    for(int i = 0; i < 8; i++)
                                    {
                                        if(probOctantes[i] > 2000)
                                            for(int i = 0; i < 8; i++)
                                                probOctantes[i] = 1;
                                    }
                    }

                    mMyPath[Counter][0] = -1;
                    mMyPath[Counter][1] = -1;

                    if(cycles >= MAX_PATHS)
                    {
                            std::cout<<"\nPath not found in "<<MAX_PATHS<<" cycles.\n";
                            mMyPath[0][0] = -1;
                            mMyPath[0][1] = -1;
                            return(1);
                    }
                    else
                    {
                        mTendency = INITIAL_TENDENCY;
                        std::cout<<"\nPath found in "<<Counter<<" paths, in "<<cycles<<" cycles.\n";
                    }


                return(0);
        }
