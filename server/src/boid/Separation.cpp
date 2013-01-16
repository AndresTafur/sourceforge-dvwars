#include "Separation.h"

Separation::Separation()
{
    //ctor
}

        Vector2 Separation::apply(Boid *mainBoid, std::vector<Boid*> boids)
        {/*
            Vector2 c, mainPos, pos;


                c = 0;

                for(size_t iter = 0; iter < boids.size(); iter++)
                        if( mainBoid != boids[iter] )
                        {
                                mainPos = mainBoid->getPosition();
                                pos     = boids[iter]->getPosition();

                                if( (mainPos - pos).length() < 200 )
                                        c = c - mainPos + pos;
                        }

                return c;*/
       }

Separation::~Separation()
{
    //dtor
}
