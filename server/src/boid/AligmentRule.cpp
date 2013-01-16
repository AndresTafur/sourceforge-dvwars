#include "AligmentRule.h"

AligmentRule::AligmentRule()
{
    //ctor
}


        Vector2 AligmentRule::apply(Boid *mainBoid, std::vector<Boid*> boids)
        {/*
            Vector2 pcJ;


                pcJ = 0;

                for(size_t iter = 0; iter < boids.size(); iter++)
                {
                        if( mainBoid != boids[iter] )
                            pcJ = pcJ + mainBoid->getVelocity();
                }

                pcJ = pcJ / (boids.size()-1);
                return (pcJ - mainBoid->getVelocity())/8;*/
       }



AligmentRule::~AligmentRule()
{
    //dtor
}
