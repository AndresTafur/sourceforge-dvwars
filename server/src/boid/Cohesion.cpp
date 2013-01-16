#include "Cohesion.h"

#include <stdio.h>

Cohesion::Cohesion()
{
    //ctor
}


        Vector2 Cohesion::apply(Boid *mainBoid, std::vector<Boid*> boids)
        {
/*            Vector2 pcJ;


                pcJ = 0;

                for(size_t iter = 0; iter < boids.size(); iter++)
                {
                        if( mainBoid != boids[iter] )
                            pcJ = pcJ + mainBoid->getPosition();
                }

                pcJ = pcJ / (boids.size()-1);
               return (pcJ - mainBoid->getPosition())/100;*/
       }


Cohesion::~Cohesion()
{
    //dtor
}
