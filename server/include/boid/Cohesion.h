#ifndef _COHESION_H_
#define _COHESION_H_

#include <Rule.h>

/**
 *
 *  Boids Cohesion rule to keep them together.
 *  @see Rule
 */
class Cohesion : public Rule
{
public:

        Cohesion();


        /**
         *  Apply current rule to mainBoid, based on boids positions.
         *  @param  mainBoid Boid to apply this rule.
         *  @param  boids Other boids in context.
         *  @return Vector2 "Velocity" to be added to the boid.
         */
        Vector2 apply(Boid *mainBoid, std::vector<Boid*> boids);


        virtual ~Cohesion();

private:
};

#endif // _COHESION_H_
