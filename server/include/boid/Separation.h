#ifndef SEPARATION_H
#define SEPARATION_H

#include <Rule.h>

/**
 *
 *  Boids Separation rule to avoid collisions.
 *  @see Rule
 */
class Separation : public Rule
{
public:

        Separation();


        /**
         *  Apply current rule to mainBoid, based on boids positions.
         *  @param  mainBoid Boid to apply this rule.
         *  @param  boids Other boids in context.
         *  @return Vector2 "Velocity" to be added to the boid.
         */
        Vector2 apply(Boid *mainBoid, std::vector<Boid*> boids);


        virtual ~Separation();

private:
};

#endif // SEPARATION_H
